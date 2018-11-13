#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Module.h"
#include "Textures.h"

enum TYPE { FLYING_ENEMY, LAND_ENEMY };

class Enemy: public Module
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;
	TYPE type;

public:
	Enemy();
	Enemy(TYPE type, iPoint position);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	//virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
};

#endif // __ENEMY_H__
