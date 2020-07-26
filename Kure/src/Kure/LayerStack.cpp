#include "krpch.h"
#include "LayerStack.h"

namespace Kure {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	//Layers are pushed into front half of vector
	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	//Overlays are pushed into back half of vector
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		std::vector<Layer*>::iterator iter = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (iter != m_Layers.begin() + m_LayerInsertIndex) {
			layer->OnDetach();
			m_Layers.erase(iter);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		std::vector<Layer*>::iterator iter = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (iter != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(iter);
		}
	}

}
