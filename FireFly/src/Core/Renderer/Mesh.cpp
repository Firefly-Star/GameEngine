#include "ffpch.h"

#include "Mesh.h"
#include "Renderer.h"

namespace FireFly
{
	//-------------------Mesh-------------------------
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<TextureInfo>& textures)
	{
		FF_CORE_TRACE("Creating mesh with {} vertices.", vertices.size());
		m_Vertices = vertices;
		m_Indices = indices;
		m_Texture = textures;

		m_VBO = VertexBuffer::Create();
		m_VBO->SetData((void*)&(vertices[0]), sizeof(Vertex) * vertices.size());

		m_IBO = IndexBuffer::Create();
		m_IBO->SetData((void*)&(indices[0]), sizeof(Index) * indices.size());
		m_Layout = BufferLayout::Create();
		m_Layout->Push({ "Position", LayoutElementType::Float3 });
		m_Layout->Push({ "Normal", LayoutElementType::Float3 });
		m_Layout->Push({ "Tangent", LayoutElementType::Float3 });
		m_Layout->Push({ "Binormal", LayoutElementType::Float3 });
		m_Layout->Push({ "TexCoord", LayoutElementType::Float2 });
	}

	void Mesh::Render(Ref<Shader> shader)
	{
		shader->Bind();
		m_VBO->Bind();
		m_IBO->Bind();
		m_Layout->UploadLayout();
		int diffusei = 0;
		int speculari = 0;
		int normali = 0;
		int total = 0;
		std::string diffuseName = "texture_diffuse";
		std::string normalName = "texture_normal";
		std::string specularName = "texture_specular";
		for (auto& it : m_Texture)
		{
			switch (it.Type)
			{
			case TextureType::DeffuseTexture:
				it.texture->Bind(total);
				diffusei++;
				shader->UploadUniform(total, diffuseName + std::to_string(diffusei));
				total++;
				break;
			case TextureType::NormalTexture:
				it.texture->Bind(total);
				normali++;
				//shader->UploadUniform(total, normalName + std::to_string(normali));
				total++;
				break;
			case TextureType::SpecularTexture:
				it.texture->Bind(total);
				speculari++;
				shader->UploadUniform(total, specularName + std::to_string(speculari));
				total++;
				break;
			}
		}
		Renderer::DrawIndexed(m_IBO->GetCount());
	}
}