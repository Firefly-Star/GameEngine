#include "ffpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace FireFly
{
	//--------Shader--------
	Ref<Shader> Shader::Create(const std::string& vertexSRC, const std::string& fragmentSRC)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSRC, fragmentSRC);
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	//--------HelperFunc of Shader--------
	std::unordered_map<Shader::ShaderType, std::string> Shader::ParseFile(const std::string& filepath)
	{
		std::fstream file(filepath);
		std::unordered_map<Shader::ShaderType, std::stringstream> ss;
		std::unordered_map<Shader::ShaderType, std::string> result;

		std::string line;
		ShaderType type = ShaderType::None;

		if (!file.is_open())
		{
			FF_CORE_ERROR("Failed to open the file from {}", filepath);
		}

		while (std::getline(file, line))
		{
			if (line.find("#type") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VertexShaderSRC;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FragmentShaderSRC;
				}
				else
				{
					FF_CORE_WARN("Unknown Shader type: {0}!", line);
				}
			}
			else
			{
				ss[type] << line << "\n";
			}
		}
		for (auto it = ss.begin(); it != ss.end(); it++)
		{
			if (it->first != Shader::ShaderType::None)
			{
				result[it->first] = ss[it->first].str();
			}
		}

		FF_CORE_ASSERT(!result.empty(), "Shader type not found: {}", filepath);
		file.close();
		return result;
	}


	//--------ShaderLibrary--------
	void ShaderLibrary::Add(const std::string& name, const std::string& filepath)
	{
		FF_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "This name already exists!");
		m_Shaders[name] = Shader::Create(filepath);
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		FF_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "This name not found!");
		return m_Shaders[name];
	}
	
}