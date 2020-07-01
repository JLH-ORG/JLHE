#include "jlhepch.h"
#include "Entity.h"

namespace JLHE {

	Entity::Entity(Ref<SubTexture2D>& subTexture, glm::vec3 position, glm::vec2 size, float rotation)
		: m_SubTexture(subTexture), m_Position(position), m_Size(size), m_Rotation(rotation), m_Visible(true) {}

	Entity::Entity(glm::vec3 position, glm::vec2 size, float rotation)
		: m_Position(position), m_Size(size), m_Rotation(rotation), m_Visible(true) {}

	void Entity::OnUpdate(Timestep& ts) {

	}

	// TODO: Should Every Entity have its own event dispatcher
	void Entity::OnEvent(Event& e) {
		JLHE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
	}

	void Entity::OnRender() {
		if(m_Visible)
			Renderer2D::DrawRotatedQuad(m_Position, m_Size, m_Rotation, m_SubTexture);
	}
}