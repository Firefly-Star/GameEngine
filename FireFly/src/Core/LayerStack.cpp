#include "ffpch.h"

#include "LayerStack.h"

namespace FireFly
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{

	}

	void LayerStack::PushLayer(Ref<Layer> layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PushOverLayer(Ref<Layer> layer)
	{
		m_OverLayers.emplace_back(layer);
	}

	bool LayerStack::EraseLayer(Ref<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			return true;
		}
		return false;
	}

	bool LayerStack::EraseOverLayer(Ref<Layer> layer)
	{
		auto it = std::find(m_OverLayers.begin(), m_OverLayers.end(), layer);
		if (it != m_OverLayers.end())
		{
			m_OverLayers.erase(it);
			return true;
		}
		return false;
	}

	bool LayerStack::OnEvent(Event& e)
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin() && !e.IsHandled();)
		{
			(*--it)->OnEvent(e);
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin() && !e.IsHandled();)
		{
			(*--it)->OnEvent(e);
		}
		return e.IsHandled();
	}

	void LayerStack::OnUpdate()
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin();)
		{
			(*--it)->OnUpdate();
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			(*--it)->OnUpdate();
		}
	}

	void LayerStack::OnImGuiRender()
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin();)
		{
			(*--it)->OnImGuiRender();
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			(*--it)->OnImGuiRender();
		}
	}
}