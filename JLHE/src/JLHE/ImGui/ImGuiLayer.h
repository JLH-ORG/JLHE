#pragma once

#include "JLHE/Layer.h"

#include "JLHE/events/ApplicatonEvent.h"
#include "JLHE/events/KeyEvent.h"
#include "JLHE/events/MouseEvent.h"

namespace JLHE {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}