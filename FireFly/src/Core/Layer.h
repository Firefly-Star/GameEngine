#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Input.h"

// Ŀǰ����ʽ�¼�ϵͳ����ѯϵͳ�ı߽粻�Ǻ����������߶���������Ϊ�㼶���µ���Ϣ��Դ

namespace FireFly
{
	class Layer
	{
	public:
		Layer(const char* name = "layer") :m_Name(name) {}
		virtual ~Layer(){}

		virtual void OnAttach(){}
		virtual void OnDettach(){}
		virtual void OnUpdate(Ref<Input> input){}//		ÿһ֡������õĺ�����������Input�ࣨ��ѯϵͳ������������
		virtual void OnImGuiRender() {}//	Ŀǰ��ImGuiר�õ���Ⱦ��������������ÿһ���Դ���GUI
		virtual bool OnEvent(Event& e) { return e.IsHandled(); }//	���¼�����Ӧ����Event������������Ӧ
	protected:
		const char* m_Name;
	};
}