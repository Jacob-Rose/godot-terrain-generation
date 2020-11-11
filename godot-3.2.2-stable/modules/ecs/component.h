/* component.h */

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <core/object.h>
#include <scene/resources/texture.h>

struct ECS_SineMover2DComponent{

public:
	float speed;
	Point2 intensity;
	float seed;
};

struct ECS_Transform2DComponent {

public:
	Point2 pos;
};

struct ECS_Sprite2DComponent {
public:
	Ref<Texture> texture;
};

#endif // ECS_COMPONENT_H

//Entities
//	ID

//Entity Manager
//	hashmap of IDs to entity pointers

//Component
//	Component Specific Info in struct form

//Component Manager <template T>
//	stores hashmap of int to T type (or store as array of size entity)
//	needs to be array? (if so then hashmap might work if not it could be an int, int for id -> index of array component is at, solves pointer slowdown issue)

//Systems
//	iterate through render components and draw
//	iterate through input components to move
//	these run on the update function?
