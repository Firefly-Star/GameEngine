#pragma once

namespace FireFly
{
	//---------BufferLayout---------
	enum class LayoutElementType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4, 
		Int, Int2, Int3, Int4,
	};

	std::pair<int, int> LayoutElementType_Size(LayoutElementType type);

	struct LayoutElement
	{
		std::string name;
		LayoutElementType type;
	};

	class BufferLayout
	{
	public:
		BufferLayout() : m_Stride(0) {}
		virtual ~BufferLayout(){}

		static Ref<BufferLayout> Create();

		void Push(LayoutElement element);
		void Pop(const std::string& name);

		virtual void UploadLayout() const = 0;

		inline const std::vector<LayoutElement>& GetElements() const { return m_Elements; }
	protected:
		std::vector<LayoutElement> m_Elements;
		int m_Stride;
	};

	//--------VertexBuffer-----------
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer(){}

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};

	//----------IndexBuffer----------
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer(){}

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int size);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual unsigned int GetCount() const = 0;
 	};
}