#ifndef _JRGARGOYLE_H__
#define _JRGARGOYLE_H__

#include "Enemy.h"

class JrGargoyle : public Enemy
{
public:
	JrGargoyle();
	JrGargoyle(iPoint position);
	~JrGargoyle();

	bool Update(float dt);
	bool Start();
	bool Fly();

	bool LoadAnimation(pugi::xml_node &node, Animation &anim);
private:

	bool CleanUp();

private:
	/*SDL_Texture* gargoyle_texture;*/
	p2SString   texture;

	Animation*	current_animation = nullptr;
	Animation idle;
	Animation fly;
	Animation dead;
};

#endif