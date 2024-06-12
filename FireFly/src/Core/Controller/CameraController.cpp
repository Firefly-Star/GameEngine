#include "ffpch.h"

#include "CameraController.h"
#include "Core/TimeStep.h"
#include "Core/KeyCode.h"
#include "Core/Controller/MouseController.h"


#include <glm/gtc/matrix_transform.hpp>

namespace FireFly
{
	//--------OrthoCameraController--------

	OrthoCameraController::OrthoCameraController(float pasr, float tasr, bool enableRotation, float zoomLevel)
		:m_ZoomLevel(zoomLevel), m_EnableRotation(enableRotation), m_Tasr(tasr), m_Pasr(pasr),
		m_Camera({-pasr * zoomLevel, pasr * zoomLevel, -zoomLevel, zoomLevel})
	{
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.EventDispatch<MouseScrolledEvent>(FF_BIND_EVENT_FN(OrthoCameraController::OnMouseScrollEvent));
		dispatcher.EventDispatch<WindowResizeEvent>(FF_BIND_EVENT_FN(OrthoCameraController::OnWindowResizeEvent));
	}

	void OrthoCameraController::OnUpdate(Ref<Input> input)
	{
		float deltaTime = TimeStep::GetDeltaTime();

		if (input->IsKeyPressed(FF_KEY_W))
		{
			cameraPosition.y += CameraMoveSpeed * deltaTime;
		}
		else if (input->IsKeyPressed(FF_KEY_S))
		{
			cameraPosition.y -= CameraMoveSpeed * deltaTime;
		}
		if (input->IsKeyPressed(FF_KEY_A))
		{
			cameraPosition.x -= CameraMoveSpeed * deltaTime;
		}
		else if (input->IsKeyPressed(FF_KEY_D))
		{
			cameraPosition.x += CameraMoveSpeed * deltaTime;
		}

		if (m_EnableRotation)
		{
			if (input->IsKeyPressed(FF_KEY_Q))
			{
				cameraRotation -= CameraRotateSpeed * deltaTime;
			}
			else if (input->IsKeyPressed(FF_KEY_E))
			{
				cameraRotation += CameraRotateSpeed * deltaTime;
			}
		}
		m_Camera.SetPosition(cameraPosition);
		m_Camera.SetRotation(cameraRotation);
	}

	bool OrthoCameraController::OnMouseScrollEvent(MouseScrolledEvent& e)
	{
		float yOffset = e.GetY();
		m_ZoomLevel -= m_CameraZoomSpeed * yOffset;
		m_ZoomLevel = m_ZoomLevel > 0.2f ? m_ZoomLevel : 0.2f;
		m_Camera.SetOrthoParameters({ -m_Pasr * m_ZoomLevel, m_Pasr * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel });
		return false;
	}

	bool OrthoCameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		float wasr = (float)e.GetWidth() / (float)e.GetHeight();
		m_Pasr = wasr / m_Tasr;
		m_Camera.SetOrthoParameters({ -m_Pasr * m_ZoomLevel, m_Pasr * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel });
		return false;
	}	

	//---------------PerspectiveCemeraController----------------
	PerspectiveCameraController::PerspectiveCameraController()
		:m_Camera(), m_PanSpeed(1.0f), m_RotationSpeed(1.0f), m_MousePosX(-1.0f), m_MousePosY(-1.0f), m_IsMouseHidden(false), 
		m_Orientation({0.0f, 0.0f, -1.0f}), m_Up({0.0f, 1.0f, 0.0f}), m_Position({0.0f, 0.0f, 0.0f}), m_IsEnableVRotation()
	{
	}


	PerspectiveCameraController::PerspectiveCameraController(const glm::vec4& persparams)
		:m_Camera(persparams), m_PanSpeed(1.0f), m_RotationSpeed(1.0f), m_MousePosX(-1.0f), m_MousePosY(-1.0f), m_IsMouseHidden(false), 
		m_Orientation({ 0.0f, 0.0f, -1.0f }), m_Up({0.0f, 1.0f, 0.0f}), m_Position({0.0f, 0.0f, 0.0f}), m_IsEnableVRotation(false)
	{
	}

	void PerspectiveCameraController::OnUpdate(Ref<Input> input)
	{
		float deltatime = TimeStep::GetDeltaTime();
		glm::vec3 right = glm::cross(m_Orientation, m_Up);
		if (input->IsKeyPressed(FF_KEY_W))
		{
			m_Position += m_Orientation * m_PanSpeed * deltatime;
		}
		else if (input->IsKeyPressed(FF_KEY_S))
		{
			m_Position -= m_Orientation * m_PanSpeed * deltatime;
		}
		if (input->IsKeyPressed(FF_KEY_A))
		{
			m_Position -= right * m_PanSpeed * deltatime;
		}
		else if (input->IsKeyPressed(FF_KEY_D))
		{
			m_Position += right * m_PanSpeed * deltatime;
		}
		if (input->IsKeyPressed(FF_KEY_SPACE))
		{
			m_Position += m_Up * deltatime;
		}
		else if (input->IsKeyPressed(FF_KEY_LEFT_SHIFT))
		{
			m_Position -= m_Up * deltatime;
		}

		m_Camera.SetPosition(m_Position);
		
	}

	bool PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.EventDispatch<MouseMovedEvent>(FF_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoveEvent));
		dispatcher.EventDispatch<KeyPressedEvent>(FF_BIND_EVENT_FN(PerspectiveCameraController::OnKeyPressEvent));
		return false;
	}

	bool PerspectiveCameraController::OnMouseMoveEvent(MouseMovedEvent& e)
	{
		if (m_IsMouseHidden)
		{
			float mouseX = e.GetX();
			float mouseY = e.GetY();

			float deltatime = TimeStep::GetDeltaTime();

			if (m_MousePosX == -1.0f)
			{
				m_MousePosX = mouseX, m_MousePosY = mouseY;
			}
			else
			{
				float deltaX = mouseX - m_MousePosX;
				float deltaY = mouseY - m_MousePosY;
				m_MousePosX = mouseX;
				m_MousePosY = mouseY;
				if (deltaX > 0)
				{
					m_Orientation = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(-m_RotationSpeed * deltatime), m_Up) * glm::vec4(m_Orientation, 1.0f));
				}
				else if (deltaX < 0)
				{
					m_Orientation = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(+m_RotationSpeed * deltatime), m_Up) * glm::vec4(m_Orientation, 1.0f));
				}
				if (m_IsEnableVRotation)
				{
					glm::vec right = glm::cross(m_Orientation, m_Up);
					if (deltaY > 0)
					{
						m_Orientation = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(-m_RotationSpeed * deltatime), right) * glm::vec4(m_Orientation, 1.0f));
						m_Up = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(-m_RotationSpeed * deltatime), right) * glm::vec4(m_Up, 1.0f));
					}
					else if (deltaY < 0)
					{
						m_Orientation = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationSpeed * deltatime), right) * glm::vec4(m_Orientation, 1.0f));
						m_Up = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationSpeed * deltatime), right) * glm::vec4(m_Up, 1.0f));
					}
				}
			}
			m_Camera.SetOrientation(m_Orientation);
			m_Camera.SetUp(m_Up);
		}
		return false;
	}

	bool PerspectiveCameraController::OnKeyPressEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == FF_KEY_ESCAPE)
		{
			m_IsMouseHidden = !m_IsMouseHidden;
			if (m_IsMouseHidden)
			{
				MouseController::Hide();
			}
			else
			{
				MouseController::Display();
			}
		}
		return false;
	}

	
	PerspectiveCamera& PerspectiveCameraController::GetCamera()
	{
		return m_Camera;
	}

	void PerspectiveCameraController::SetPanSpeed(float panspeed)
	{
		m_PanSpeed = panspeed;
	}

	void PerspectiveCameraController::SetRotationSpeed(float rotationspeed)
	{
		m_RotationSpeed = rotationspeed;
	}

	void PerspectiveCameraController::SetIsEnableVRotation(bool isEnable)
	{
		m_IsEnableVRotation = isEnable;
	}

}