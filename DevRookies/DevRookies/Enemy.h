#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Module.h"
#include "Pathfinding.h"
#include "Map.h"

struct SDL_Texture;
struct Collider;
enum TYPE { FLYING_ENEMY, LAND_ENEMY };

class Enemy
{
protected:
	Animation * animation;
	Collider* collider;

public:
	iPoint position;
	TYPE type;

public:
	Enemy(TYPE type);
	Enemy(TYPE type, iPoint position);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);

	void Save(pugi::xml_node&) const;
	void Load(pugi::xml_node&);
};

#endif // __ENEMY_H__
