#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Module.h"
//#include "Textures.h"
#include "Entity.h"
#include "p2DynArray.h"

class Enemy: public Entity
{
protected:

	float distance = 400.0F;

public:
	//iPoint position;

public:
	Enemy(entityType type);
	virtual ~Enemy();

	// Called before the first frame
	virtual bool Start();

	virtual bool Restart() { return true; };

	// Called before all Updates
	virtual bool PreUpdate();

	// Called each loop iteration
	virtual bool Update(float dt);

	// Called before all Updates
	virtual bool PostUpdate();

	// Called before quitting
	virtual bool CleanUp();

	//Save and Load
	virtual bool Load(pugi::xml_node&);
	virtual bool Save(pugi::xml_node&) const;

	const Collider* GetCollider() const;

	//virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider*, Collider*) {};

};

#endif // __ENEMY_H__
