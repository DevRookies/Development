#ifndef __COLLISION_H__
#define __COLLISION_H__

#define MAX_COLLIDERS 2000

#include "Module.h"
#include "SDL/include/SDL_rect.h"

enum COLLIDER_TYPE {
	COLLIDER_NONE = -1,
	COLLIDER_PLAYER,
	COLLIDER_ICE,
	COLLIDER_FIRE,
	COLLIDER_POISON,
	COLLIDER_BORDER,
	COLLIDER_FINAL,
	COLLIDER_MAX,
};

struct Collider
{
	SDL_Rect		rect;
	COLLIDER_TYPE	type;
	Module*			callback = nullptr;
	bool			to_delete = false;
	bool			enable = true;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) : rect(rectangle),	type(type),	callback(callback) {}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	void SetShape(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	void SetType(COLLIDER_TYPE type)
	{
		this->type = type;
	}
	bool CheckCollision(const SDL_Rect& r) const;
	

};

class Collision : public Module

{
public:

	Collision();

	// Destructor
	~Collision();

	bool		PreUpdate();
	bool		Update(float dt);
	bool		CleanUp();

	Collider*	AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	bool		CheckCollision() const;
	Collider*	player_collider = nullptr;

private:

	Collider*	colliders[MAX_COLLIDERS];
	bool		matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool		debug = false;
};


#endif // __COLLISION_H__