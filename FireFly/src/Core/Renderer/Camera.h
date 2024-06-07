#pragma once
/*
GLM�ľ��������ȵģ�����ζ��mat[i][j]�д洢���ǵ�j�е�i�е�Ԫ�أ�������ǵ�ϰ������㣵ġ�ͬʱ��glm::value_ptr(mat)�����ָ��Ҳ�����ȵģ�Ҳ����˵���ȴ�
�����´洢��һ�е�Ԫ�أ��ٴ������´洢�ڶ��е�Ԫ�أ��Դ����ơ�opengl����Ⱦ������Ĭ�ϵľ���Ҳ�����ȵ�
opengl�е�����Ĭ��Ϊ������
*/


/*
opengl�еļ�����Ҫ����ϵ��
1.�ֲ�����ϵ/��������ϵ/ģ������ϵ/��������ϵ����Ϊ�����һ�����屾�������ϵ���ֲ��ռ������Ǵ���Ķ����������ڵĿռ䡣һ������£����ǿ��԰�Ҫ��Ⱦ�ĳ�����
��Ϊ����С�������ЩС���ͨ����һ��ģ�ͣ������˴����Ķ��㡣����ģʱ������һ�㲻�ῼ��ģ���ڳ����еľ������꣬������ǻ���Ϊָ��һ������ϵ���������ϵ����
�ֲ��ռ䣬����ȡֵ��ģ�����ڵ�λ�����޹صġ�

2.ȫ������ϵ/��������ϵ/��������ϵ����Ϊ���������ڵ�����ϵ�����е����������������λ������ռ����������Ⱦ�����Ŀռ䡣ÿ��ģ��������ռ䶼�и��Ե�λ�ã����
������Ҫ�Ѿֲ��ռ�������ƶ�������λ�ã��Ա���������ꡣ

3.�۲�����ϵ/��ͼ����ϵ/�������ϵ����Ϊ����ӽ��µ�����ϵ�����һ�㿴��z��ĸ����򡣴�ó�����ͨ�����λ�õı任����������ͼ�ı任����ʵ�ϣ�������������
��������ģ�ʵ�ʵĲ���������ͨ������任ȫ������ϵ����ɵġ�

3.5.�ü�����ϵ���ǹ۲�����ϵ��NDC���м�̬���ǹ۲�����ϵͨ��͸��ͶӰ����任���پ����ü���õ�������ϵ����ʱ�Ѿ��ܽӽ�NDC����ϵ�ˡ�

4.NDC/����豸����ϵ���ǲü�����ϵͨ��͸�ӳ�����������ά�Ĳü������һ����ά��[-1, 1]^3����ά���꣩��õ�������ϵ��

5.��Ļ����ϵ����NDC�����ӿڱ任����[-1, 1]^3��ά��[left, left + width] * [bottom, bottom + height]�ı任��z������Ϊ�����Ϣ��������Ⱦ�ͻ�ϣ��õ�����
��ϵ��
*/


/*
opengl�еļ�����Ҫ����
1.ģ�;����ǴӾֲ�����ϵ��ȫ������ϵ�ı任����һ��Ҫ����һϵ�з���任�����������������ţ���ת��ƽ�ƣ����У��ԳƵȵȡ�˳��ͬ�ϡ�

2.��ͼ�����Ǵ�ȫ������ϵ���۲�����ϵ�ı任���󣬼�������ԭ���ƶ������������λ�ã�Ȼ���ٽ�����ת��

3.ͶӰ�����Ǵӹ۲�����ϵ���ü�����ϵ�ı任����һ���Ϊ����ͶӰ��͸��ͶӰ���֡�����ͶӰ�Ǵӳ����嵽������ı任��һ������2D��ͼ��͸��ͶӰ�Ǵ���׶�嵽����
��ı任��һ������3D��ͼ��

�Ӳü�����ϵ��NDC�ı任��͸�ӳ��������вü�������opengl��Ⱦ�����еĹ̶�����һ�㲻��Ҫ�����ֶ��ٿء�

��NDC����Ļ����ϵ�ı任���ӿڱ任��Ҳ��opengl��Ⱦ�����еĹ̶�����Ҳ����Ҫ�����ֶ��ٿأ�����һ����������Ҫ����ͨ��glViewPort()���ֶ�ָ���ӿڵĴ�С(��Ⱥ�
�߶�)��λ�ã����½ǵ����꣩�������򴰿ڱ����ı任��������Ⱦʧ�档
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