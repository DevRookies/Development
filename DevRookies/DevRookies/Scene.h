#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GUIManager.h"
#include "GUIButton.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "GUILabel.h"

struct SDL_Texture;


class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

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

	//Save and Load
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	//Restart scene
	void Restart() const;

	uint			scene_actual = 1;
	SDL_Texture*	 debug_tex = nullptr;
private:

	p2SString		tile_name_scene1 = "", tile_name_scene2 = "";
	p2SString		lvl1_music_name = "", lvl2_music_name = ""; 
	p2SString		godmode_texture = "", pause_texture = "";
	SDL_Rect		camera;

	fPoint			godmode_pos, pause_pos;
	
	SDL_Texture*  godmode_tex = nullptr;
	SDL_Texture*  pause_tex = nullptr;

	GUIImage* image = nullptr;
	GUILabel* label = nullptr;
	GUIButton* button = nullptr;
	
	SDL_Rect img_rect;

	SDL_Rect normal;
	SDL_Rect pressed;
	SDL_Rect hovered;
};

#endif // __SCENE_H__