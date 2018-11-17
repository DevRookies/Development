#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Collision.h"

class Player;

class Entity
{
public:
	enum entityType
	{
		NO_TYPE,
		PLAYER,
		FLYING_ENEMY,
		LAND_ENEMY
	};

public:
	Entity();
	Entity(entityType type);
	~Entity();
	virtual bool Awake(pugi::xml_node & config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	//virtual void Move();

	virtual bool CleanUp() { return true; };
	virtual bool Save(pugi::xml_node& file) const { return true; };
	virtual bool Load(pugi::xml_node& file) { return true; };


	void		AddFX(const int channel, const int repeat) const;
	bool		LoadAnimation(pugi::xml_node &node, Animation &anim);
	void		OnCollision(Collider* collider1, Collider* collider2);
	void		AddCollider();

	/*fPoint		GetPosition();
	void		SetPosition(const float &x, const float &y);*/

public:
	entityType type;
	fPoint speed;
	iPoint position;
	iPoint max_speed;
	iPoint gravity;
	Collider* collider = nullptr;

};

#endif
