#pragma once

#include "JLHE/Layer.h"

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
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}