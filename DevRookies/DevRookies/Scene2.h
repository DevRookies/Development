#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"

struct SDL_Texture;


class Scene2 : public Module
{
public:

	Scene2();

	// Destructor
	virtual ~Scene2();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:

	p2SString tile_name = "";
};

#endif // __SCENE2_H__