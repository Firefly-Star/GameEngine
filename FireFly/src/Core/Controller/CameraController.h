#pragma once

#include "Core/Renderer/Camera.h"
#include "Core/Events/Event.h"
#include "Core/Input.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/WindowEvent.h"

#include <glm/glm.hpp>

namespace FireFly
{
	//--------OrthoCameraController-------------------
	class OrthoCameraController
	{
	public:
		OrthoCameraController(float wasr, float tasr, bool enableRotation = false, float zoomLevel = 1.0f);

		void OnEvent(Event& e);
		void OnUpdate();

		inline OrthoCamera& GetCamera() { return m_Camera; }
	private:
		bool OnMouseScrollEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		OrthoCamera m_Camera;
		float m_ZoomLevel;
		float m_Pasr, m_Tasr;// m_Pasr: 投影矩阵的长宽比, m_Tasr：目标长宽比
		bool m_EnableRotation;

		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraZoomSpeed = 0.25f;
		float cameraRotation = 0.0f;
		float CameraMoveSpeed = 0.5f;
		float CameraRotateSpeed = 30.0f;
	};

	//-----------PerspectivecameraController-------------
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController();
		PerspectiveCameraController(const glm::vec4& persparams);
		void OnUpdate();
		bool OnEvent(Event& e);

		inline PerspectiveCamera& GetCamera() { return m_Camera; }
		inline void SetPanSpeed(float panspeed) { m_PanSpeed = panspeed; }
		inline void SetRotationSpeed(float rotationspeed) { m_RotationSpeed = rotationspeed; }
		inline void SetIsEnableVRotation(bool isEnable) { m_IsEnableVRotation = isEnable; }
		void SetIsEnableRoar(bool isEnable) { m_IsEnableRoar = isEnable; }
	private:
		bool OnMouseMoveEvent(MouseMovedEvent& e);
		bool OnKeyPressEvent(KeyPressedEvent& e);
	private:
		PerspectiveCamera m_Camera;
		float m_MousePosX, m_MousePosY;
		float m_PanSpeed, m_RotationSpeed;
		glm::vec3 m_Position;
		glm::vec3 m_Orientation;
		glm::vec3 m_Up;
		bool m_IsEnableVRotation;
		bool m_IsMouseHidden;
		bool m_IsEnableRoar;
		float m_RotationX;
		float m_RotationY;
	};
}