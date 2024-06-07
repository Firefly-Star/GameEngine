#pragma once
#include "Core/Renderer/Buffer.h"


namespace FireFly
{

	//---------BufferLayout---------
	static std::pair<unsigned int, unsigned char> LayoutElementType_OpenGLBaseType(LayoutElementType type);

	class OpenGLBufferLayout : public BufferLayout
	{
	public:
		OpenGLBufferLayout() : BufferLayout() {}
		virtual void UploadLayout() const override;
	};

	//--------VertexBuffer-----------
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		unsigned int m_RendererID;
	};

	//----------IndexBuffer----------
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual unsigned int GetCount() const override { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};


}