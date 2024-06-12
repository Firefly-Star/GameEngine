#include "ffpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FireFly
{

	//---------BufferLayout---------
	std::pair<unsigned int, unsigned char> LayoutElementType_OpenGLBaseType(LayoutElementType type)//  .first: type  .second: normalized
	{
		switch (type)
		{
		case LayoutElementType::Float:     return std::make_pair(GL_FLOAT, GL_FALSE);       break;
		case LayoutElementType::Float2:    return std::make_pair(GL_FLOAT, GL_FALSE);	    break;
		case LayoutElementType::Float3:    return std::make_pair(GL_FLOAT, GL_FALSE);		break;
		case LayoutElementType::Float4:    return std::make_pair(GL_FLOAT, GL_FALSE);		break;
		case LayoutElementType::Mat3:      return std::make_pair(GL_FLOAT, GL_FALSE);	    break;
		case LayoutElementType::Mat4:      return std::make_pair(GL_FLOAT, GL_FALSE);	    break;
		case LayoutElementType::Int:       return std::make_pair(GL_INT, GL_FALSE);			break;
		case LayoutElementType::Int2:      return std::make_pair(GL_INT, GL_FALSE);		    break;
		case LayoutElementType::Int3:      return std::make_pair(GL_INT, GL_FALSE);		    break;
		case LayoutElementType::Int4:      return std::make_pair(GL_INT, GL_FALSE);		    break;
		}

		FF_CORE_ASSERT(false, "Unknown Type!");
		return std::make_pair(0, 0);
	}

	void OpenGLBufferLayout::UploadLayout() const
	{
		unsigned int offset = 0;
		unsigned int index = 0;

		for (auto element : m_Elements)
		{
			glEnableVertexAttribArray(index);
			auto [offsetplus, size] = LayoutElementType_Size(element.type);
			auto [type, normalized] = LayoutElementType_OpenGLBaseType(element.type);
			//FF_CORE_INFO("name: {}, offsetplus:{}, size:{}, type:{}, normalized:{}, offset: {}", element.name, offsetplus, size, type, normalized, offset);
			glVertexAttribPointer(index, size, type, normalized, m_Stride, (void*)offset);
			index++;
			offset += offsetplus;
		}
	}

	//--------VertexBuffer-----------
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
		:m_RendererID(0)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer()
		:m_RendererID(0)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(void* buffer, unsigned int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	}

	//----------IndexBuffer----------
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int size)
		:m_RendererID(0), m_Count(size / sizeof(unsigned int))
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer()
		:m_RendererID(0), m_Count(0)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(void* buffer, unsigned int size)
	{
		m_Count = size / sizeof(unsigned int);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	}

}