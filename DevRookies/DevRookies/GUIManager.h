#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "SDL_ttf/include/SDL_ttf.h"

#define CURSOR_WIDTH 2


class GUIElement;

class GUIManager : public Module
{

public:
	// Constructor
	GUIManager();

	// Destructor
	virtual ~GUIManager();

	// Called when before render is available
	bool Awake(pugi::xml_node& config);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	GUIImage* CreateImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture = nullptr, Module* callback = nullptr);
	GUILabel* CreateLabel(iPoint pos, p2SString text, _TTF_Font* font, Module* callback = nullptr);
	GUIButton* CreateButton(iPoint pos, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, SDL_Texture* texture = nullptr, Module* callback = nullptr);

	//GUICheckBox* CreateCheckBox(iPoint pos, p2SString text, iPoint displacement = { 0,0 }, Module* callback = nullptr);
	//GUISlider* CreateSlider(iPoint pos, uint num_buttons, p2SString title, iPoint displacement = { 0,0 }, Module* callback = nullptr);

	SDL_Texture* GetAtlas();

	GUIElement* GetMouseElement(iPoint pos);

	
private:

	SDL_Texture * atlas;
	p2SString atlas_file_name;

	void DestroyGUIElement(GUIElement* element);

	p2List<GUIElement*> gui_elements;

	bool debug = false;
};

#endif // __!GUIMANAGER_H__
