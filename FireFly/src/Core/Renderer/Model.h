#pragma once

#include "Mesh.h"
#include <string>

#include <assimp/scene.h>


namespace FireFly
{
	class Model
	{
	public:
		Model(const std::string & filepath, const std::string& directory);
		static void InitAssimpLogger();
		void Render(Ref<Shader> shader);
		inline std::vector<Mesh> GetMeshes() { return m_Meshes; }
	private:
		void LoadModel(const std::string& filepath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Mesh::TextureInfo> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);
	private:
		std::vector<Mesh> m_Meshes;
		const std::string& m_Filepath, m_Directory;
		std::unordered_map<const char*, Mesh::TextureInfo> m_TextureCache;
	};

}
