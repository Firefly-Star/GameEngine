#pragma once

namespace FireFly
{
	//-------------FrameBuffer--------------
	enum class FrameBufferFormat
	{
		None = 0,
		RGB8 = 1,
		RGBA16F = 2
	};

	class FrameBuffer
	{
	public:
		static FrameBuffer* Create(unsigned int width, unsigned int height, FrameBufferFormat format);

		virtual ~FrameBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void BindTexture(unsigned int slot = 0) const = 0;

		virtual unsigned int GetRendererID() const = 0;
		virtual unsigned int GetColorAttachmentRendererID() const = 0;
		virtual unsigned int GetDepthAttachmentRendererID() const = 0;
	};

	//-------------FrameBufferPool--------------
	class FrameBufferPool final
	{
	public:
		FrameBufferPool(unsigned int maxFBs = 32);
		~FrameBufferPool() = default;

		std::weak_ptr<FrameBuffer> AllocateBuffer();
		void Add(Ref<FrameBuffer> frameBuffer);

		inline const std::vector<Ref<FrameBuffer>>& GetAll() const { return m_Pool; }

		inline static Ref<FrameBufferPool> GetGlobal() { return s_Instance; }
	private:
		std::vector<Ref<FrameBuffer>> m_Pool;
		static Ref<FrameBufferPool> s_Instance;
	};
}