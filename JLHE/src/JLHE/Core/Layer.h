#pragma once
#include "JLHE/Core/Core.h"
#include "JLHE/Events/Event.h"
#include "JLHE/Core/Timestep.h"

//TEMP
#include <string>

namespace JLHE {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}