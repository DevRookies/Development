#ifndef _JRGARGOYLE_H__
#define _JRGARGOYLE_H__

#include "Enemy.h"
#include "Textures.h"

class JrGargoyle : public Enemy
{
public:
	JrGargoyle();
	JrGargoyle(entityType type);
	~JrGargoyle();

	bool	Awake(pugi::xml_node & config);
	bool	Start(uint i);
	bool	Restart(uint i);
	bool	PreUpdate();
	bool	Update(float dt);
	bool	PostUpdate();
	void	OnCollision(Collider* collider1, Collider* collider2);
	void	Fly(const p2DynArray<iPoint> *path);

	//Save and Load
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	bool LoadAnimation(pugi::xml_node &node, Animation &anim);
private:

	bool CleanUp();

private:
	SDL_Texture* gargoyle_tex = nullptr;
	p2SString   gargoyle_texture;

	Animation*	current_animation = nullptr;
	Animation idle;
	Animation fly;
	Animation dead;
};

#endif// _JRGARGOYLE_H__