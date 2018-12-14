#ifndef _OFFICERSKELETON_H__
#define _OFFICERSKELETON_H__

#include "Enemy.h"
//#include "Entity.h"
//#include "EntityManager.h"
#include "Textures.h"
//#include "p2Point.h"

class OfficerSkeleton : public Enemy
{
public:
	OfficerSkeleton();
	OfficerSkeleton(entityType type);
	~OfficerSkeleton();

	bool	Awake(pugi::xml_node & config);
	bool	Start(uint i);
	bool	Restart(uint i);
	bool	PreUpdate();
	bool	Update(float dt);
	bool	PostUpdate();
	void	OnCollision(Collider* collider1, Collider* collider2);
	void	Walk(const p2DynArray<iPoint> *path);

	//Save and Load
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	bool LoadAnimation(pugi::xml_node &node, Animation &anim);
private:

	bool CleanUp();

private:
	SDL_Texture * skeleton_tex = nullptr;
	p2SString   skeleton_texture, die_fx_name;

	Animation*	current_animation = nullptr;
	Animation idle;
	Animation walk;
	Animation dead;
};

#endif // _OFFICERSKELETON_H__