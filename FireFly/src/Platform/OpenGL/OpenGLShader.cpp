#include "ffpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace FireFly
{
	OpenGLShader::OpenGLShader(const std::string& vertexSRC, const std::string& fragmentSRC)
		:m_RendererID(0)
	{
		m_RendererID = glCreateProgram();
		std::unordered_map<FireFly::Shader::ShaderType, std::string> shaderSources =
		{ {FireFly::Shader::ShaderType::VertexShaderSRC, vertexSRC},{FireFly::Shader::ShaderType::FragmentShaderSRC, fragmentSRC} };
		auto shaderIDs = Compile(shaderSources);
		Attach(shaderIDs);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		:m_RendererID(0)
	{
		m_RendererID = glCreateProgram();
		auto shaderSources = ParseFile(filepath);
		auto shaderIDs = Compile(shaderSources);
		Attach(shaderIDs);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(const glm::mat4& mat, const std::string& name)
	{
		int location = GetLocation(name);

		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
		}
	}

	void OpenGLShader::UploadUniform(const glm::mat3& mat, const std::string& name)
	{
		int location = GetLocation(name);

		if (location != -1)
		{
			glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
		}
	}

	void OpenGLShader::UploadUniform(int i, const std::string& name)
	{
		int location = GetLocation(name);

		if (location != -1)
		{
			glUniform1i(location, i);
		}
	}

	void OpenGLShader::UploadUniform(float x1, float x2, float x3, float x4, const std::string& name)
	{
		int location = GetLocation(name);

		if (location != -1)
		{
			glUniform4f(location, x1, x2, x3, x4);
		}
	}

	void OpenGLShader::UploadUniform(float x1, float x2, float x3, const std::string& name)
	{
		int location = GetLocation(name);

		if (location != -1)
		{
			glUniform3f(location, x1, x2, x3);
		}
	}

	void OpenGLShader::UploadUniform(float x, const std::string& name)
	{
		int location = GetLocation(name);

		if (location != -1)
		{
			glUniform1f(location, x);
		}
	}

	//--------HelperFunc---------


	GLenum OpenGLShader::ShaderTypeToOpenGLenum(ShaderType type)
	{
		switch (type)
		{
		case ShaderType::VertexShaderSRC:		return GL_VERTEX_SHADER;
		case ShaderType::FragmentShaderSRC:		return GL_FRAGMENT_SHADER;
		}
		FF_CORE_ASSERT("false", "Unknown Shader type!");
		return 0;
	}

	std::unordered_map<Shader::ShaderType, unsigned int> OpenGLShader::Compile(std::unordered_map<ShaderType, std::string>& sourceFile)
	{
		std::unordered_map<ShaderType, unsigned int> shaderIDs;
		//Create Shaders
		for (const auto pair : sourceFile)
		{
			unsigned int shader;
			GLenum type = ShaderTypeToOpenGLenum(pair.first);
			shader = glCreateShader(type);
			shaderIDs[pair.first] = shader;
			const char* src = (const char*)pair.second.c_str();

			glShaderSource(shader, 1, &src, nullptr);

			int status = 0;

			//Compile the shader
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (status != GL_TRUE)
			{
				int length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				char* log = new char[length];
				glGetShaderInfoLog(shader, length, &length, log);

				FF_CORE_ERROR("Failed to Compile the shader:{}{}", "\n", log);
				FF_CORE_ASSERT(false, "");
				glDeleteShader(shader);
				delete[]log;
				return shaderIDs;
			}
		}
		return shaderIDs;
	}

	void OpenGLShader::Attach(std::unordered_map<ShaderType, unsigned int>& shaderIDs)
	{
		for (auto pair : shaderIDs)
		{
			glAttachShader(m_RendererID, pair.second);
		}
		glLinkProgram(m_RendererID);
		int status = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			int length;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length];
			glGetProgramInfoLog(m_RendererID, length, &length, log);
			FF_CORE_ERROR("Failed to Link the Program: {}", log);

			glDeleteProgram(m_RendererID);
			delete[]log;
		}
		for (auto pair : shaderIDs)
		{
			glDeleteShader(pair.second);
		}
		return;
	}

	int OpenGLShader::GetLocation(const std::string& name)
	{
		int location;
		auto it = m_UniformLocationMap.find(name);

		if (it != m_UniformLocationMap.end())
		{
			location = it->second;
		}
		else
		{
			location = glGetUniformLocation(m_RendererID, name.c_str());
			if (location == -1)
			{
				//FF_CORE_WARN("Failed to locate the Uniform \"{0}\"!", name);
				return -1;
			}
			m_UniformLocationMap[name] = location;
		}
		return location;
	}
}