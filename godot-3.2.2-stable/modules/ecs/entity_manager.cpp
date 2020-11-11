/* entity_manager.cpp */

#include "entity_manager.h"
#include <scene/main/viewport.h> //used to get mouse position in _process(float)
#include <core/os/os.h>
#include <tgmath.h>

void ECS_EntityManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("addEntity"), &ECS_EntityManager::addEntity);
	ClassDB::bind_method(D_METHOD("removeEntity", "id"), &ECS_EntityManager::removeEntity);
	ClassDB::bind_method(D_METHOD("setEntitySprite", "id", "texture"), &ECS_EntityManager::setEntitySprite);
	ClassDB::bind_method(D_METHOD("setEntityPosition", "id", "position"), &ECS_EntityManager::setEntityPosition);
	ClassDB::bind_method(D_METHOD("setEntitySineMoveIntensity", "id", "intensity"), &ECS_EntityManager::setEntitySineMoveIntensity);
	ClassDB::bind_method(D_METHOD("setEntitySineMoveSeed", "id", "seed"), &ECS_EntityManager::setEntitySineMoveSeed);
	ClassDB::bind_method(D_METHOD("setEntitySineMoveSpeed", "id", "speed"), &ECS_EntityManager::setEntitySineMoveSpeed);
	ClassDB::bind_method(D_METHOD("addTransformComponent", "id"), &ECS_EntityManager::addTransformComponent);
	ClassDB::bind_method(D_METHOD("addSineMoverComponent", "id"), &ECS_EntityManager::addSineMoverComponent);
	ClassDB::bind_method(D_METHOD("addSpriteComponent", "id"), &ECS_EntityManager::addSpriteComponent);
	//ClassDB::bind_method(D_METHOD("getTransform2DComponentRef"), &ECS_EntityManager::getTransform2DComponentRef);
	//ClassDB::bind_method(D_METHOD("getSprite2DComponentManager"), &ECS_EntityManager::getSprite2DComponent);
}

ECS_EntityManager::ECS_EntityManager() {
	set_process(true);
}

int ECS_EntityManager::addEntity() {
	++m_IDTracker; //we just will keep this sequential to avoid issues
	m_EntityIDs.push_back(m_IDTracker);
	//addTransformComponent(m_IDTracker);
	//addSpriteComponent(m_IDTracker);
	//addSineMoverComponent(m_IDTracker);
	return m_IDTracker;
}

void ECS_EntityManager::removeEntity(int id) {
	for (size_t i = 0; i < m_EntityIDs.size(); i++) {
		if (m_EntityIDs[i] == id) {
			m_EntityIDs.erase(m_EntityIDs.begin() + i);
			break;
		}
	}
}

void ECS_EntityManager::addTransformComponent(int e) {
	m_TransformComponentMap[e] = ECS_Transform2DComponent();
}

void ECS_EntityManager::addSpriteComponent(int e) {
	m_SpriteComponentMap[e] = ECS_Sprite2DComponent();
}

void ECS_EntityManager::addSineMoverComponent(int e) {
	m_SineMoverComponentMap[e] = ECS_SineMover2DComponent();
}

ECS_Transform2DComponent *ECS_EntityManager::getTransform2DComponent(int e) {
	
	try {
		return &m_TransformComponentMap.at(e);
	}
	catch (std::out_of_range) {
		return nullptr;
	}
}

ECS_Sprite2DComponent *ECS_EntityManager::getSprite2DComponent(int e) {
	
	try {
		return &m_SpriteComponentMap.at(e);
	} catch (std::out_of_range) {
		return nullptr;
	}
}

ECS_SineMover2DComponent *ECS_EntityManager::getSineMover2DComponent(int e) {
	try {
		return &m_SineMoverComponentMap.at(e);
	} catch (std::out_of_range) {
		return nullptr;
	}
}

void ECS_EntityManager::setEntitySprite(int id, Ref<Texture> texture) {
	ECS_Sprite2DComponent *comp = getSprite2DComponent(id);
	if (comp != nullptr) {
		comp->texture = texture;
	}
}

void ECS_EntityManager::setEntityPosition(int id, Point2 pos) {
	ECS_Transform2DComponent *comp = getTransform2DComponent(id);
	if (comp != nullptr) {
		comp->pos = pos;
	}
}

void ECS_EntityManager::setEntitySineMoveIntensity(int id, Point2 intensity) {
	ECS_SineMover2DComponent *comp = getSineMover2DComponent(id);
	if (comp != nullptr) {
		comp->intensity = intensity;
	}

}

void ECS_EntityManager::setEntitySineMoveSpeed(int id, float speed) {
	ECS_SineMover2DComponent *comp = getSineMover2DComponent(id);
	if (comp != nullptr) {
		comp->speed = speed;
	}
}

void ECS_EntityManager::setEntitySineMoveSeed(int id, float seed) {
	ECS_SineMover2DComponent *comp = getSineMover2DComponent(id);
	if (comp != nullptr) {
		comp->seed = seed;
	}
}

void ECS_EntityManager::removeTransformComponent(int e) {
	m_TransformComponentMap.erase(e);
}

void ECS_EntityManager::removeSpriteComponent(int e) {
	m_SpriteComponentMap.erase(e);
}

void ECS_EntityManager::removeSineMoverComponent(int e) {
	m_SineMoverComponentMap.erase(e);
}

void ECS_EntityManager::_notification(int p_what) {
	/*
	if (!Engine::get_singleton()->is_editor_hint()) {
	}
	*/

	switch (p_what) {
		case NOTIFICATION_PROCESS:
			_process(get_process_delta_time()); //this is called each frame like Update() in Unity
			update();
			break;
		case NOTIFICATION_DRAW:
			_draw();
	}
}

void ECS_EntityManager::_process(float dt) {
	_processRenderSystem(dt);
	_processSineMoverSystem(dt);
}

void ECS_EntityManager::_draw() {
	_drawRenderSystem();
}

void ECS_EntityManager::_processRenderSystem(float dt) {
	
}

void ECS_EntityManager::_drawRenderSystem() {
	Engine *e = Engine::get_singleton();
	for (auto itr = m_EntityIDs.begin(); itr != m_EntityIDs.end(); ++itr) {
		ECS_Sprite2DComponent *spriteComp = getSprite2DComponent(*itr);
		ECS_Transform2DComponent *transformComp = getTransform2DComponent(*itr);

		if (spriteComp == nullptr || transformComp == nullptr) {
			continue;
		}

		draw_texture(spriteComp->texture, transformComp->pos);
	}
}

void ECS_EntityManager::_processSineMoverSystem(float dt) {
	Engine *e = Engine::get_singleton();
	for (auto itr = m_EntityIDs.begin(); itr != m_EntityIDs.end(); ++itr) {
		ECS_SineMover2DComponent *sineComp = getSineMover2DComponent(*itr);
		ECS_Transform2DComponent *transformComp = getTransform2DComponent(*itr);

		if (sineComp == nullptr || transformComp == nullptr) {
			continue;
		}

		transformComp->pos += sineComp->intensity * sin((static_cast<double>(OS::get_singleton()->get_system_time_msecs()) * sineComp->speed) + sineComp->seed);
	}
}


