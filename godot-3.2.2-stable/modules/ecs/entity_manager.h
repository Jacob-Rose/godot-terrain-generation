/* entity_manager.h */

#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER

#include <scene/2d/node_2d.h>
#include <vector>
#include <map>
#include <stdexcept>
#include "component.h"

class ECS_EntityManager : public Node2D {
	GDCLASS(ECS_EntityManager, Node2D);
	protected:
		static void _bind_methods();
		
		std::map<int, ECS_Transform2DComponent> m_TransformComponentMap;
		std::map<int, ECS_Sprite2DComponent> m_SpriteComponentMap;
		std::map<int, ECS_SineMover2DComponent> m_SineMoverComponentMap;

		std::vector<int> m_EntityIDs;

		unsigned int m_IDTracker = 0;

	public:
		ECS_EntityManager();
		
		int addEntity();
		void removeEntity(int id);

		void addTransformComponent(int e);
		void addSpriteComponent(int e);
		void addSineMoverComponent(int e);

		ECS_Transform2DComponent* getTransform2DComponent(int e);
		ECS_Sprite2DComponent* getSprite2DComponent(int e);
		ECS_SineMover2DComponent *getSineMover2DComponent(int e);

		void setEntitySprite(int id, Ref<Texture> texture);
		void setEntityPosition(int id, Point2 pos);
		void setEntitySineMoveIntensity(int id, Point2 intensity);
		void setEntitySineMoveSpeed(int id, float speed);
		void setEntitySineMoveSeed(int id, float seed);

		void removeTransformComponent(int e);
		void removeSpriteComponent(int e);
		void removeSineMoverComponent(int e);


		void _notification(int p_what);

		void _process(float dt);
		void _draw();

		void _processRenderSystem(float dt);
		void _drawRenderSystem();

		void _processSineMoverSystem(float dt);
		
};


#endif // ECS_ENTITYMANAGER
