#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Entity.h"
#include "Animation.h"
#include "Player.h"


class Entity;

struct officer_skeleton_info {
	fPoint speed, acceleration;
	float range_of_trigger;
};

class EntityManager : public Module
{
public:
	EntityManager();
	~EntityManager();

	bool Awake(pugi::xml_node & config);
	bool Start();
	bool Restart();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	Entity* CreateEntity(Entity::entityType type, iPoint position);
	bool DestroyEntity(Entity* entity);
	//void DestroyEntities();
	void OnCollision(Collider* collider1, Collider* collider2);
	void LoadEntityInfo(Entity::entityType type, pugi::xml_node & node);

public:
	p2SString		folder;
	p2SString		texture_path;
	SDL_Texture*	texture;
	p2List<Entity*> entities;
	Player*			player = nullptr;
	officer_skeleton_info skeleton_info;
};
#endif // !__ENTITYMANAGER_H__

