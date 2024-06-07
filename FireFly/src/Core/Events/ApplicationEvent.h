#pragma once

#include "Event.h"

namespace FireFly
{
	class AppTickEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventApplication)
		EVENT_TYPE_FUNCTION(AppTick)
	};

	class AppUpdateEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventApplication)
		EVENT_TYPE_FUNCTION(AppUpdate)
	};

	class AppRenderEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventApplication)
		EVENT_TYPE_FUNCTION(AppRender)
	};
}