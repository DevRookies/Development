#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Textures.h"
#include "Collision.h"

enum class entityType
{
	PLAYER,
	FLYING_ENEMY,
	LAND_ENEMY,
	COIN,
	NO_TYPE,
};

class Entity
{
protected:
	enum MOVEMENT {IDLE, RIGHT, LEFT, UP, DOWN, DEAD, LEFT_HIT, RIGHT_HIT};
	enum STATE {FLOOR, AIR, DEATH, WIN };

	STATE current_state;
	MOVEMENT last_movement;
	MOVEMENT current_movement = IDLE;

public:
	Entity();
	Entity(entityType type);
	~Entity();
	virtual bool Awake(pugi::xml_node & config) { return true; };
	virtual bool Start(uint i) { return true; };
	virtual bool Restart(uint i) { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	virtual bool Save(pugi::xml_node& file) const;
	virtual bool Load(pugi::xml_node& file);

	void		AddFX(const int channel, const int repeat) const;
	bool		LoadAnimation(pugi::xml_node &node, Animation &anim);
	virtual void OnCollision(Collider* collider1, Collider* collider2) {};
	void		AddCollider();

	

	virtual fPoint GetPosition();
	virtual void SetPosition(const float &x, const float &y);

public:
	entityType type;
	fPoint speed, position, max_speed, acceleration;

	Collider* collider = nullptr;
	Animation* current_animation = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect	current;
	bool flipX = false;
	bool visibility = true;

};

#endif
