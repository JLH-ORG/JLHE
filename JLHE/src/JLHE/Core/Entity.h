#pragma once

#include "JLHE/Renderer/SubTexture2D.h"
#include "JLHE/Renderer/Renderer2D.h"
#include "JLHE/Core/Timestep.h"
#include "JLHE/Events/Event.h"
#include "glm/glm.hpp"

namespace JLHE {

	class Entity {
	public:
		Entity(glm::vec3 position, glm::vec2 size, float rotation);
		Entity(Ref<SubTexture2D>& subTexture, glm::vec3 position, glm::vec2 size, float rotation);
		virtual ~Entity() = default;

		void OnUpdate(Timestep& ts);
		void OnEvent(Event& e);
		void OnRender();

		void SetSubTexture(const Ref<SubTexture2D>& subTexture) { m_SubTexture = subTexture; }

		Ref<SubTexture2D> GetSubTexture() const { return m_SubTexture; }
		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec2 GetSize() const { return m_Size; }
		float GetRotation() const { return m_Rotation; }
		bool isVisible() const { return m_Visible; }

		void Show() { m_Visible = true; }
		void Hide() { m_Visible = false; }

	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		float m_Rotation;
	private:
		Ref<SubTexture2D> m_SubTexture;
		bool m_Visible;
	};
}