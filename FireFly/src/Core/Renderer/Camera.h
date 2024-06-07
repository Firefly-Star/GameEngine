#pragma once
/*
GLM的矩阵是列先的，这意味着mat[i][j]中存储的是第j行第i列的元素，这和我们的习惯是相悖的。同时，glm::value_ptr(mat)输出的指针也是列先的，也就是说是先从
上至下存储第一列的元素，再从上往下存储第二列的元素，以此类推。opengl的渲染管线中默认的矩阵也是列先的
opengl中的向量默认为列向量
*/


/*
opengl中的几个重要坐标系：
1.局部坐标系/物体坐标系/模型坐标系/本地坐标系。即为相对于一个物体本身的坐标系。局部空间是我们传入的顶点坐标所在的空间。一般情况下，我们可以把要渲染的场景拆
分为若干小物件。这些小物件通常是一个模型，包含了大量的顶点。而建模时，我们一般不会考虑模型在场景中的绝对坐标，因此我们会人为指定一个坐标系。这个坐标系就是
局部空间，它的取值和模型所在的位置是无关的。

2.全局坐标系/世界坐标系/绝对坐标系。即为整个场景内的坐标系，其中的坐标描述了物体的位置世界空间就是我们渲染场景的空间。每个模型在世界空间都有各自的位置，因此
我们需要把局部空间的坐标移动至它的位置，以变成世界坐标。

3.观察坐标系/视图坐标系/相机坐标系。即为相机视角下的坐标系。相机一般看向z轴的负方向。搭好场景后，通过相机位置的变换，来产生视图的变换。事实上，“相机”这个概
念是虚拟的，实际的操作过程是通过反向变换全局坐标系来完成的。

3.5.裁剪坐标系。是观察坐标系到NDC的中间态，是观察坐标系通过透视投影矩阵变换，再经过裁剪后得到的坐标系，此时已经很接近NDC坐标系了。

4.NDC/规格化设备坐标系，是裁剪坐标系通过透视除法（即将四维的裁剪坐标归一化降维成[-1, 1]^3的三维坐标）后得到的坐标系。

5.屏幕坐标系。由NDC经过视口变换（从[-1, 1]^3降维成[left, left + width] * [bottom, bottom + height]的变换，z坐标作为深度信息，用于渲染和混合）得到的坐
标系。
*/


/*
opengl中的几个重要矩阵：
1.模型矩阵。是从局部坐标系到全局坐标系的变换矩阵，一般要经历一系列仿射变换，包括但不限于缩放，旋转，平移，剪切，对称等等。顺序同上。

2.视图矩阵，是从全局坐标系到观察坐标系的变换矩阵，即将坐标原点移动至“相机”的位置，然后再进行旋转。

3.投影矩阵，是从观察坐标系到裁剪坐标系的变换矩阵，一般分为正视投影和透视投影两种。正视投影是从长方体到立方体的变换，一般用于2D绘图。透视投影是从视锥体到立方
体的变换，一般用于3D绘图。

从裁剪坐标系到NDC的变换（透视除法）还有裁剪过程是opengl渲染管线中的固定程序，一般不需要我们手动操控。

从NDC到屏幕坐标系的变换（视口变换）也是opengl渲染管线中的固定程序，也不需要我们手动操控，但是一般来讲，需要我们通过glViewPort()来手动指定视口的大小(宽度和
高度)和位置（左下角的坐标），避免因窗口比例的变换而导致渲染失真。
*/

#include <glm/glm.hpp>

namespace FireFly
{
	//------------OrthoCamera------------------
	class OrthoCamera
	{
	public:
		OrthoCamera();
		OrthoCamera(const glm::vec4& ortho_parameters);

		void SetOrthoParameters(const glm::vec4& ortho_parameters);
		void SetPosition(const glm::vec3& position);
		void SetRotation(float rotation);
		const glm::mat4& GetPVmatrix();
	private:
		void ReCalMatrix();
	private:
		glm::vec3 m_Position;
		float m_Rotation;	//rotation surround z-axis

		glm::mat4 m_PerspectiveMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_PVmatrix;
	};

	//----------PerspectiveCamera------------
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera();
		PerspectiveCamera(const glm::vec4& perspective_parameters);

		void SetPerspectiveParameters(const glm::vec4& perspective_parameters);
		void SetPosition(const glm::vec3& position);
		void SetOrientation(const glm::vec3& orientation);
		void SetUp(const glm::vec3& up);
		const glm::mat4& GetPVmatrix();
		inline const glm::vec3 GetPosition() { return m_Position; }
	private:
		void ReCalMatrix();
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Orientation;
		glm::vec3 m_Up;

		glm::mat4 m_PerspectiveMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_PVmatrix;
	};

}