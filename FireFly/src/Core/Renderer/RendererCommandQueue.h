#pragma once


namespace FireFly
{
	class RendererCommandQueue
	{
	public:
#define FF_COMMAND_BUFFER_SIZE 10 * 1024 * 1024
		typedef void(*RenderCommandFn)(void*);

		RendererCommandQueue();
		~RendererCommandQueue();

		void* Allocate(RenderCommandFn func, unsigned int size, unsigned int alignment);

		void Execute();
	private:
		unsigned char* m_OriginCommandBuffer;
		unsigned char* m_CommandBuffer;
		unsigned char* m_CommandBufferWorkPtr;
		unsigned int m_CommandCount = 0;
	};
}