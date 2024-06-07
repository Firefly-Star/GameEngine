#pragma once

#include "RendererCommandQueue.h"
#include "RendererAPI.h"

namespace FireFly
{

	class Renderer
	{
	public:
		typedef void(*RenderCommandFn)(void*);

		// Commands
		static void Clear();
		static void SetClearColor(float r, float g, float b, float a);

		static void DrawIndexed(unsigned int count, bool depthTest = true);
		static void SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

		static void Init();

		static void Execute();
	private:
		static RendererCommandQueue s_CommandQueue;
	};

}

#define FF_RENDER(code) \
    struct FF_UNIQUE(FFRenderCommand) \
    {\
        static void Execute(void*)\
        {\
            code\
        }\
    };\
	{\
		auto mem = ::FireFly::Renderer::Submit(FF_UNIQUE(FFRenderCommand)::Execute, sizeof(FF_UNIQUE(FFRenderCommand)));\
		new (mem) FF_UNIQUE(FFRenderCommand)();\
	}\

#define FF_RENDER_1(arg0, code) \
	do {\
    struct FF_UNIQUE(FFRenderCommand) \
    {\
		FF_UNIQUE(FFRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0) \
		: arg0(arg0) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg0;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
    };\
	{\
		auto mem = ::FireFly::Renderer::Submit(FF_UNIQUE(FFRenderCommand)::Execute, sizeof(FF_UNIQUE(FFRenderCommand)));\
		new (mem) FF_UNIQUE(FFRenderCommand)(arg0);\
	} } while(0)

#define FF_RENDER_2(arg0, arg1, code) \
    struct FF_UNIQUE(FFRenderCommand) \
    {\
		FF_UNIQUE(FFRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1) \
		: arg0(arg0), arg1(arg1) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg1;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
    };\
	{\
		auto mem = ::FireFly::Renderer::Submit(FF_UNIQUE(FFRenderCommand)::Execute, sizeof(FF_UNIQUE(FFRenderCommand)));\
		new (mem) FF_UNIQUE(FFRenderCommand)(arg0, arg1);\
	}\

#define FF_RENDER_3(arg0, arg1, arg2, code) \
    struct FF_UNIQUE(FFRenderCommand) \
    {\
		FF_UNIQUE(FFRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2) \
		: arg0(arg0), arg1(arg1), arg2(arg2) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg2;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
    };\
	{\
		auto mem = ::FireFly::Renderer::Submit(FF_UNIQUE(FFRenderCommand)::Execute, sizeof(FF_UNIQUE(FFRenderCommand)));\
		new (mem) FF_UNIQUE(FFRenderCommand)(arg0, arg1, arg2);\
	}\

#define FF_RENDER_4(arg0, arg1, arg2, arg3, code) \
    struct FF_UNIQUE(FFRenderCommand) \
    {\
		FF_UNIQUE(FFRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3)\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg2;\
			auto& arg3 = ((FF_UNIQUE(FFRenderCommand)*)argBuffer)->arg3;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3;\
    };\
	{\
		auto mem = Renderer::Submit(FF_UNIQUE(FFRenderCommand)::Execute, sizeof(FF_UNIQUE(FFRenderCommand)));\
		new (mem) FF_UNIQUE(FFRenderCommand)(arg0, arg1, arg2, arg3);\
	}

#define FF_RENDER_S(code) auto self = this;\
	FF_RENDER_1(self, code)

#define FF_RENDER_S1(arg0, code) auto self = this;\
	FF_RENDER_2(self, arg0, code)

#define FF_RENDER_S2(arg0, arg1, code) auto self = this;\
	FF_RENDER_3(self, arg0, arg1, code)

#define FF_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
	FF_RENDER_4(self, arg0, arg1, arg2, code)