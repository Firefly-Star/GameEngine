#include "ffpch.h"
#include <assimp/postprocess.h>
#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/Importer.hpp>

#include "Model.h"

namespace FireFly
{
	namespace
	{
		const unsigned int ImportConfig =
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_SortByPType |
			aiProcess_PreTransformVertices |
			aiProcess_Debone |
			aiProcess_GenNormals |
			aiProcess_GenUVCoords |
			aiProcess_ValidateDataStructure |
			aiProcess_OptimizeMeshes;
	}
	struct LogStream : public Assimp::LogStream
	{
		static void Init()
		{
			if (Assimp::DefaultLogger::isNullLogger())
			{
				Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
				Assimp::DefaultLogger::get()->attachStream(new LogStream, Assimp::Logger::Err | Assimp::Logger::Warn);
			}
		}

		void write(const char* message) override
		{
			FF_CORE_ERROR("Assimp: {0}", message);
		}
	};

	//----------------Model------------------
	void Model::InitAssimpLogger()
	{
		LogStream::Init();
	}

	Model::Model(const std::string& filepath, const std::string& directory)
		:m_Filepath(filepath), m_Directory(directory), m_TextureCache()
	{
		LoadModel(filepath);
	}

	void Model::LoadModel(const std::string& filepath)
	{
		Assimp::Importer importer;
		FF_CORE_TRACE("Loading the model: {}", filepath);
		const aiScene* scene = importer.ReadFile(filepath, ImportConfig);
		bool status = scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode;
		FF_CORE_ASSERT(status, "Failed to load model: {}", filepath);
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		FF_CORE_TRACE("{} meshes", node->mNumMeshes);
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Mesh::Vertex> vertices;
        std::vector<Mesh::Index> indices;
        std::vector<Mesh::TextureInfo> textures;


        vertices.reserve(mesh->mNumVertices);
        indices.reserve(mesh->mNumFaces);
		FF_CORE_TRACE("Loading Mesh: {}", mesh->mName.C_Str());
		FF_CORE_TRACE("{} vertices", mesh->mNumVertices);

        FF_CORE_ASSERT(mesh->HasPositions(), "Mesh should have positions!");
        FF_CORE_ASSERT(mesh->HasNormals(), "Mesh should have normals!");

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Mesh::Vertex vertex;
            vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

            if (mesh->HasTangentsAndBitangents())
            {
                vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                vertex.Binormal = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
            }
			else
			{
				vertex.Tangent = { 0.0f, 0.0f, 0.0f };
				vertex.Binormal = { 0.0f, 0.0f, 0.0f };
			}
            if (mesh->HasTextureCoords(0))
            {
                // TODO: Handle models which possess more than 1 texture coords.
                vertex.Texcoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            }
            else
                vertex.Texcoords = { 0.0f, 0.0f };

            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
			FF_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "The primitive should be traingle with 3 indices!");
			indices.push_back({ mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] });
        }

        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Mesh::TextureInfo> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DeffuseTexture);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Mesh::TextureInfo> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SpecularTexture);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<Mesh::TextureInfo> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::NormalTexture);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<Mesh::TextureInfo> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::AmbientOcclusionTexture);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        return Mesh(vertices, indices, textures);
    }

	std::vector<Mesh::TextureInfo> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName)
	{
		std::vector<Mesh::TextureInfo> textures;
		aiTextureMapMode mapModeU, mapModeV;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			auto it = m_TextureCache.find(str.C_Str());
			if (false)
			{
				textures.push_back(it->second);
			}
			else
			{
				Mesh::TextureInfo texture;
				mat->Get(AI_MATKEY_MAPPINGMODE_U(type, i), mapModeU);
				{
					// 根据mapModeU设置OpenGL纹理环绕方式
					switch (mapModeU)
					{
					case aiTextureMapMode_Wrap:
						FF_CORE_TRACE("GL_REPEAT");
						break;
					case aiTextureMapMode_Clamp:
					case aiTextureMapMode_Decal:
						FF_CORE_TRACE("GL_CLAMP_TO_EDGE");
						break;
					case aiTextureMapMode_Mirror:
						FF_CORE_TRACE("GL_MIRRORED_REPEAT");
						break;
					}
				}

				std::string filepath = m_Directory + str.C_Str();
				texture.texture = Texture2D::Create(filepath);
				texture.Type = typeName;
				textures.push_back(texture);
				m_TextureCache[str.C_Str()] = texture;
			}
		}
		return textures;
	}

	void Model::Render(Ref<Shader> shader)
	{
		for (auto& it : m_Meshes)
		{
			it.Render(shader);
		}
	}
}
