#ifndef _OFFICERSKELETON_H__
#define _OFFICERSKELETON_H__

#include "Enemy.h"
#include "Textures.h"

class OfficerSkeleton : public Enemy
{
public:

	OfficerSkeleton();
	OfficerSkeleton(iPoint position);
	~OfficerSkeleton();

	bool Awake(pugi::xml_node & config);
	bool Update(float dt);
	bool Start();
	bool Walk();

	bool LoadAnimation(pugi::xml_node &node, Animation &anim);
private:

	bool CleanUp();

private:
	SDL_Texture * skeleton_tex = nullptr;
	p2SString   skeleton_texture;

	Animation*	current_animation = nullptr;
	Animation idle;
	Animation walk;
	Animation dead;
};

#endif // _OFFICERSKELETON_H__