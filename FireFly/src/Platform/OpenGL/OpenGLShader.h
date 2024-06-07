#pragma once
#include "Core/Renderer/Shader.h"

namespace FireFly
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSRC, const std::string& fragmentSRC);
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void UploadUniform(const glm::mat4& mat, const std::string& name) override;
		virtual void UploadUniform(const glm::mat3& mat, const std::string& name) override;
		virtual void UploadUniform(int i, const std::string& name) override;
		virtual void UploadUniform(float x1, float x2, float x3, float x4, const std::string& name) override;
		virtual void UploadUniform(float x1, float x2, float x3, const std::string& name) override;
		virtual void UploadUniform(float x, const std::string& name) override;
	private:
		unsigned int ShaderTypeToOpenGLenum(ShaderType type);
		std::unordered_map<ShaderType, unsigned int> Compile(std::unordered_map<ShaderType, std::string>& sourceFile);
		void Attach(std::unordered_map<ShaderType, unsigned int>& shaderIDs);
		int GetLocation(const std::string& name);
	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationMap;
	};
}