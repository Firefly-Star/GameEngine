#pragma once

#include "glm/glm.hpp"

namespace FireFly
{

	//--------Shader--------
	class Shader
	{
	public:
		enum class ShaderType
		{
			None = 0,
			VertexShaderSRC = 1, FragmentShaderSRC = 2
		};
		
		virtual ~Shader() {};

		static Ref<Shader> Create(const std::string& vertexSRC, const std::string& fragmentSRC);
		static Ref<Shader> Create(const std::string& filepath);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniform(const glm::mat4& mat, const std::string& name) = 0;
		virtual void UploadUniform(const glm::mat3& mat, const std::string& name) = 0;
		virtual void UploadUniform(int i, const std::string& name) = 0;
		virtual void UploadUniform(float x1, float x2, float x3, float x4, const std::string& name) = 0;
		virtual void UploadUniform(float x1, float x2, float x3, const std::string& name) = 0;
		virtual void UploadUniform(float x, const std::string& name) = 0;
	protected:
		std::unordered_map<ShaderType, std::string> ParseFile(const std::string& filepath);
	};

	//--------ShaderLibrary--------
	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}