#include "jlhepch.h"
#include "EntitySystem.h"

namespace JLHE {

	EntitySystem::EntitySystem() {
		m_Entities.reserve(s_MaxEntities);
	}

	void EntitySystem::OnUpdate(Timestep& ts) {
		for (auto& entity : m_Entities) {
			entity.OnUpdate(ts);
		}
	}

	void EntitySystem::OnEvent(Event& e) {
		for (auto& entity : m_Entities) {
			entity.OnEvent(e);
		}
	}

	void EntitySystem::OnRender() {
		for (auto& entity : m_Entities) {
			entity.OnRender();
		}
	}

	bool EntitySystem::AddEntity(Entity& entity) {
		if (m_Entities.size() < s_MaxEntities) {
			m_Entities.push_back(entity);
			return true;
		}
		return false;
	}
}