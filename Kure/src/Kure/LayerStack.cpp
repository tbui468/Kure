#include "krpch.h"
#include "LayerStack.h"

namespace Kure {

	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	//Layers are pushed into front half of vector
	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_LayerInsert, layer);
		m_LayerInsert++;
	}

	//Overlays are pushed into back half of vector
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		std::vector<Layer*>::iterator iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end()) {
			m_Layers.erase(iter);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		std::vector<Layer*>::iterator iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (iter != m_Layers.end()) {
			m_Layers.erase(iter);
		}
	}

}
