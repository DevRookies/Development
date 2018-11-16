#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Module.h"
//#include "Textures.h"
#include "Entity.h"

class Enemy: public Entity
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;

public:
	Enemy(Entity::entityType type);
	Enemy(Entity::entityType type, iPoint position);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	//virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);

	void Save(pugi::xml_node&) const;
	void Load(pugi::xml_node&);
};

#endif // __ENEMY_H__
