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

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

private:

	p2SString		tile_name = "";
	p2SString		lvl2_music_name = "";
	SDL_Rect		player;
	SDL_Rect		camera;
};

#endif // __SCENE2_H__