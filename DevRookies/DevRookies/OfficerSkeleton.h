#ifndef _OFFICERSKELETON_H__
#define _OFFICERSKELETON_H__

#include "Enemy.h"

class OfficerSkeleton : public Enemy
{
public:

	OfficerSkeleton();
	OfficerSkeleton(iPoint position);
	~OfficerSkeleton();

	bool Update(float dt);
	bool Start();
	bool Walk();

	bool LoadAnimation(pugi::xml_node &node, Animation &anim);
private:

	bool CleanUp();

private:
	//SDL_Texture * skeleton_texture;
	p2SString   texture;

	Animation*	current_animation = nullptr;
	Animation idle;
	Animation walk;
	Animation dead;
};

#endif // _OFFICERSKELETON_H__