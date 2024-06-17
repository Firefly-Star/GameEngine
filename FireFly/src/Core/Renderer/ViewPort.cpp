#include "ffpch.h"

#include "ViewPort.h"

namespace FireFly
{
	float ViewPort::s_Ratio = 0.0f;
	bool ViewPort::s_IsLockRatio = true;
	unsigned int ViewPort::s_Width = 0;
	unsigned int ViewPort::s_Height = 0;

	void ViewPort::OnEvent(WindowResizeEvent& e)
	{
		unsigned int width = e.GetWidth();
		unsigned int height = e.GetHeight();

		if (s_IsLockRatio)
		{
			if ((float)width / (float)height >= s_Ratio)
			{
				s_Width = (unsigned int)(height * s_Ratio);
				s_Height = height;
				unsigned int x = (width - (unsigned int)(height * s_Ratio)) / 2;
				Renderer::SetViewPort(x, 0, s_Width, height);
			}
			else
			{
				s_Width = width;
				s_Height = (unsigned int)(width / s_Ratio);
				unsigned int y = (height - (unsigned int)(width / s_Ratio)) / 2;
				Renderer::SetViewPort(0, y, width, s_Height);
			}
		}
		else
		{
			Renderer::SetViewPort(0, 0, width, height);
			s_Width = width;
			s_Height = height;
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

	void ViewPort::SetSize(unsigned int width, unsigned int height)
	{
		s_Width = width;
		s_Height = height;
	}
}