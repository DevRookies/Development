#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Textures.h"
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

protected:
	enum MOVEMENT_ENEMY { IDLE_E, RIGHT_E, LEFT_E, UP_E, DOWN_E };
	enum STATE_ENEMY { ONFLOOR_E, AIR_E, DEATH_E };

	STATE_ENEMY current_state;
	MOVEMENT_ENEMY last_movement;
	MOVEMENT_ENEMY current_movement = IDLE_E;

public:
	Entity();
	Entity(entityType type);
	~Entity();
	virtual bool Awake(pugi::xml_node & config) { return true; };
	virtual bool Start() { return true; };
	virtual bool Restart() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };

	virtual bool CleanUp() { return true; };
	virtual bool Save(pugi::xml_node& file) const { return true; };
	virtual bool Load(pugi::xml_node& file) { return true; };

	void		AddFX(const int channel, const int repeat) const;
	bool		LoadAnimation(pugi::xml_node &node, Animation &anim);
	virtual void OnCollision(Collider*, Collider*) {};
	void		AddCollider();

	bool sprite_flipY = false;
	bool sprite_flipX = false;

	virtual fPoint GetPosition();
	virtual void SetPosition(const float &x, const float &y);

public:
	entityType type;
	fPoint speed;
	iPoint position;
	iPoint max_speed;
	iPoint gravity; //fPoint?

	Collider* collider = nullptr;
	Animation* current_animation = nullptr;
	SDL_Texture* texture = nullptr;

};

#endif
