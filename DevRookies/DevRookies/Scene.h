#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GUIManager.h"
#include "GUIButton.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "GUILabel.h"
#include "GUISlider.h"

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

	void AddFX(const int channel, const int repeat) const;
	//bool LoadAnimation(pugi::xml_node &node, Animation &anim);

	uint			scene_actual = 0;
	SDL_Texture*	 debug_tex = nullptr;
private:

	p2SString		tile_name_scene0 = "", tile_name_scene1 = "", tile_name_scene2 = "";
	p2SString		lvl0_music_name = "", lvl1_music_name = "", lvl2_music_name = "";
	p2SString		hover_fx_name = "";
	p2SString		godmode_texture = "", pause_texture = "";
	SDL_Rect		camera;

	fPoint			godmode_pos, pause_pos;
	
	SDL_Texture*  godmode_tex = nullptr;
	SDL_Texture*  pause_tex = nullptr;

	bool printUI_base = true;

	//----------------------------------------------------------------------------------------
	//------------------------------GUI-------------------------------------------------------
	//----------------------------------------------------------------------------------------
	bool guicreated = false;
	void GUIStart();
	void GUIUpdate();
	//--------------------------GUIElements---------------------------------------------------
	GUIImage* windows_img = nullptr;
	GUIImage* windows_hud_img = nullptr;
	GUIImage* title_img = nullptr;
	GUIImage* license_img = nullptr;
	GUIImage* music_img = nullptr;
	GUIImage* fx_img = nullptr;
	GUIImage* minus_music_img = nullptr;
	GUIImage* plus_music_img = nullptr;
	GUIImage* minus_fx_img = nullptr;
	GUIImage* plus_fx_img = nullptr;
	GUIImage* coins_img = nullptr;
	GUIImage* life_img = nullptr;
	GUIImage* score_img = nullptr;
	GUIImage* time_img = nullptr;

	GUIButton* settings_home_btn = nullptr;
	GUIButton* credits_home_btn = nullptr;
	GUIButton* play_btn = nullptr;
	GUIButton* continue_btn = nullptr;
	GUIButton* settings_btn = nullptr;
	GUIButton* credits_btn = nullptr;
	GUIButton* exit_btn = nullptr;
	GUIButton* resume_btn = nullptr;
	GUIButton* settings_hud_btn = nullptr;
	GUIButton* settings_hud_home_btn = nullptr;
	GUIButton* back_menu_btn = nullptr;

	GUISlider* music_sli = nullptr;
	GUISlider* fx_sli = nullptr;

	//GUILabel* label = nullptr;
	
	//--------------------------GUIRects---------------------------------------------------
	//IMG
	SDL_Rect windows_rect;
	SDL_Rect title_rect;
	SDL_Rect license_rect;
	SDL_Rect music_rect;
	SDL_Rect fx_rect;
	SDL_Rect minus_rect;
	SDL_Rect plus_rect;
	SDL_Rect coins_rect;
	SDL_Rect life_rect;
	SDL_Rect score_rect;

	//BTN
	SDL_Rect play_normal;
	SDL_Rect play_pressed;
	SDL_Rect play_hovered;

	SDL_Rect continue_normal;
	SDL_Rect continue_pressed;
	SDL_Rect continue_hovered;

	SDL_Rect settings_normal;
	SDL_Rect settings_pressed;
	SDL_Rect settings_hovered;

	SDL_Rect credits_normal;
	SDL_Rect credits_pressed;
	SDL_Rect credits_hovered;

	SDL_Rect exit_normal;
	SDL_Rect exit_pressed;
	SDL_Rect exit_hovered;

	SDL_Rect resume_normal;
	SDL_Rect resume_pressed;
	SDL_Rect resume_hovered;

	SDL_Rect back_menu_normal;
	SDL_Rect back_menu_pressed;
	SDL_Rect back_menu_hovered;

	//SLI
	SDL_Rect slider_rect;
};

#endif // __SCENE_H__