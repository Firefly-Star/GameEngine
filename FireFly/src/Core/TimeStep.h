#pragma once

namespace FireFly
{
	class TimeStep
	{
	public:
		TimeStep() = default;
		virtual ~TimeStep() = default;

		static void Init();
		static void OnUpdate();
		static float GetDeltaTime();
		static float GetTime();
	private:
		virtual void InitImpl() = 0;
		virtual void OnUpdateImpl() = 0;
		virtual float GetDeltaTimeImpl() = 0;
		virtual float GetTimeImpl() = 0;
	private:
		static Ref<TimeStep> s_Instance;
	};
}