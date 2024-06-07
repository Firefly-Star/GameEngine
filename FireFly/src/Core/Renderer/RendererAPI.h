#pragma once

namespace FireFly
{
	class RendererAPI	// Bottom API, to EXECUTE instructions from RendererCommand with SPECIFIC API such as Opengl or DirectX
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,//TO DO: DirectX, Vulcan ,e.t.c.
		};
	public:
		virtual ~RendererAPI() = default;

		static Scope<RendererAPI> Create();
		static void SwitchToOtherAPI(API api);

		static void SetClearColor(float r, float g, float b, float a = 1.0f);
		static void Clear();
		static void Init();
		static void SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		static void DrawIndexed(unsigned int count, bool isEnableDepthTest = true);
		inline static API GetAPI() { return s_API; }
	private:
		virtual void SetClearColorImpl(float r, float g, float b, float a = 1.0f) = 0;
		virtual void ClearImpl() = 0;
		virtual void InitImpl() = 0;
		virtual void SetViewPortImpl(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

		virtual void DrawIndexedImpl(unsigned int count, bool isEnableDepthTest) = 0;

	private:
		static API s_API;
		static Scope<RendererAPI> s_Instance;
	};
}