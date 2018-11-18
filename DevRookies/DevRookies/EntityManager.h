#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Entity.h"
#include "Animation.h"


class Player;

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

	Entity* CreateEntity(entityType type);
	bool DestroyEntity(Entity* entity);
	void OnCollision(Collider* collider1, Collider* collider2);

public:
	p2SString		folder;
	p2SString		texture_path;
	SDL_Texture*	texture = nullptr;
	p2List<Entity*> entities;
	Player*			player = nullptr;
	uint			gargoyle_count = 4;
	uint			skeleton_count = 6;
};
#endif // !__ENTITYMANAGER_H__

