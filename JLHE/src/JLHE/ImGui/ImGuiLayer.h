#pragma once

#include "JLHE/Core/Layer.h"

#include "JLHE/Events/ApplicatonEvent.h"
#include "JLHE/Events/KeyEvent.h"
#include "JLHE/Events/MouseEvent.h"

namespace JLHE {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

		virtual void OnEvent(Event& e) override;
		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}