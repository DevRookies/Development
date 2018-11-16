#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Entity.h"
#include "Player.h"


class Entity;

class EntityManager : public Module
{
public:
	EntityManager();
	~EntityManager();

	bool Awake(pugi::xml_node & config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	Entity* CreateEntity(Entity::entityType type, iPoint position);
	bool DestroyEntity(Entity* entity);
	void DestroyEntities();

public:
	p2SString		folder;
	p2SString		texture_path;
	SDL_Texture*	texture;
	p2List<Entity*> entities;
	Player*			player = nullptr;

};
#endif // !__ENTITYMANAGER_H__

