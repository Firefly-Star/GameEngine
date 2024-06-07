#include "ffpch.h"

#include "ViewPort.h"

namespace FireFly
{
	float ViewPort::s_Ratio = 0.0f;
	bool ViewPort::s_IsLockRatio = true;

	void ViewPort::OnEvent(WindowResizeEvent& e)
	{
		unsigned int width = e.GetWidth();
		unsigned int height = e.GetHeight();

		if (s_IsLockRatio)
		{
			if ((float)width / (float)height >= s_Ratio)
			{
				unsigned int x = (width - (unsigned int)(height * s_Ratio)) / 2;
				Renderer::SetViewPort(x, 0, (unsigned int)(height * s_Ratio), height);
			}
			else
			{
				unsigned int y = (height - (unsigned int)(width / s_Ratio)) / 2;
				Renderer::SetViewPort(0, y, width, (unsigned int)(width / s_Ratio));
			}
		}
		else
		{
			Renderer::SetViewPort(0, 0, width, height);
		}
	}

	void ViewPort::SetIsLockRatio(bool isLockRatio)
	{
		s_IsLockRatio = isLockRatio;
	}

	void ViewPort::SetRatio(float ratio)
	{
		s_Ratio = ratio;
	}

}