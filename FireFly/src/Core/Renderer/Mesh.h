#pragma once

#include "Buffer.h"
#include "Texture.h"
#include "Shader.h"	

#include <glm/glm.hpp>
#include <assimp/scene.h>


namespace FireFly
{
	//-------------Mesh-------------
	class Mesh
	{
	public:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec3 Tangent;
			glm::vec3 Binormal;
			glm::vec2 Texcoords;
		};

		struct Index
		{
			unsigned int v1, v2, v3;
		};

		struct TextureInfo
		{
			Ref<Texture> texture;
			TextureType Type;
		};

		Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<TextureInfo>& textures);
		~Mesh() = default;
		void Render(Ref<Shader> shader);
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;
		std::vector<TextureInfo> m_Texture;

		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_IBO;
		Ref<BufferLayout> m_Layout;
	};

}