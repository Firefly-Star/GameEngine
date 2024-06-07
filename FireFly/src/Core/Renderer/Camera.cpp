#include "ffpch.h"

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FireFly
{
	//	TEMP
	std::string print(glm::mat4 mat)
	{
		std::stringstream ss;
		ss << "\n";
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 0; j <= 3; j++)
			{
				ss << mat[j][i] << "\t";
			}
			ss << "\n";
		}
		return ss.str();
	}
	//	TEMP

	//--------OrthoCamera--------
	OrthoCamera::OrthoCamera()
		:m_Position({0.0f, 0.0f, 0.0f}), m_Rotation(0.0f), 
		m_PerspectiveMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)),
		m_ViewMatrix(1.0f)
	{
		ReCalMatrix();
	}

	OrthoCamera::OrthoCamera(const glm::vec4& ortho_parameters)
		:m_Position({ 0.0f, 0.0f, 0.0f }), m_Rotation(0.0f),
		m_PerspectiveMatrix(glm::ortho(ortho_parameters[0], ortho_parameters[1], ortho_parameters[2], ortho_parameters[3], -1.0f, 1.0f)),
		m_ViewMatrix(1.0f)
	{
		ReCalMatrix();
	}

	void OrthoCamera::SetOrthoParameters(const glm::vec4& ortho_parameters)
	{
		m_PerspectiveMatrix = glm::ortho(ortho_parameters[0], ortho_parameters[1], ortho_parameters[2], ortho_parameters[3], -1.0f, 1.0f);
	}

	void OrthoCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void OrthoCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	const glm::mat4& OrthoCamera::GetPVmatrix()
	{
		ReCalMatrix();
		return m_PVmatrix;
	}

	void OrthoCamera::ReCalMatrix() 
	{
		glm::mat4 transformation =
			glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(transformation);
		m_PVmatrix = m_PerspectiveMatrix * m_ViewMatrix;
	}

	//-----------PerspectiveCamera-------------

	PerspectiveCamera::PerspectiveCamera()
		:m_Position({0.0f, 0.0f, 0.0f}), m_Orientation({0.0f, 0.0f, -1.0f}), m_Up({0.0f, 1.0f, 0.0f})
	{
		m_PerspectiveMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_PVmatrix = m_PerspectiveMatrix;
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec4& perspective_parameters)
		:m_Position({ 0.0f, 0.0f, 0.0f }), m_Orientation({ 0.0f, 0.0f, -1.0f }), m_Up({ 0.0f, 1.0f, 0.0f })
	{
		m_PerspectiveMatrix = glm::perspective(glm::radians(perspective_parameters.r), perspective_parameters.g, perspective_parameters.b, perspective_parameters.a);
		m_ViewMatrix = glm::mat4(1.0f);
		m_PVmatrix = m_PerspectiveMatrix;
	}

	void PerspectiveCamera::SetPerspectiveParameters(const glm::vec4& perspective_parameters)
	{
		m_PerspectiveMatrix = glm::perspective(perspective_parameters.r, perspective_parameters.g, perspective_parameters.b, perspective_parameters.a);
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void PerspectiveCamera::SetOrientation(const glm::vec3& orientation)
	{
		m_Orientation = orientation;
	}

	void PerspectiveCamera::SetUp(const glm::vec3& up)
	{
		m_Up = up;
	}

	const glm::mat4& PerspectiveCamera::GetPVmatrix()
	{
		ReCalMatrix();
		return m_PVmatrix;
	}

	void PerspectiveCamera::ReCalMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Orientation + m_Position, m_Up);
		m_PVmatrix = m_PerspectiveMatrix * m_ViewMatrix;
	}
}