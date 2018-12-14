#ifndef __COIN_H__
#define __COIN_H__

#include "Module.h"
#include "Animation.h"
#include "Entity.h"

class Coin : public Entity
{
public:

	Coin(entityType type);

	//Destructor
	~Coin();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start(uint i);
	bool Restart(uint i);

	// Called before all Updates
	bool PreUpdate() {return true;};

	// Called each loop iteration
	bool Update(float dt) { return true; };

	// Called before all Updates
	bool PostUpdate();

	void OnCollision(Collider* collider1, Collider* collider2);

	//Save and Load
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	
	bool LoadAnimation(pugi::xml_node &node, Animation &anim);

private:
	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* coin_tex = nullptr;
	p2SString   coin_texture;

	Animation	flip;
};


#endif // !__COIN_H__
