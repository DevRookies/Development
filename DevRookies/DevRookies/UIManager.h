#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;
class p2SString;
class UIElement;

enum UI_Type
{
	IMAGE,
	BUTTON,
	CHECKBOX,
	LABEL,
	SLIDER,
	NO_TYPE,

};

// ---------------------------------------------------
class UIManager : public Module
{

public:
	// Constructor
	UIManager();

	// Destructor
	virtual ~UIManager();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

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

	bool DestroyUIElement(UIElement *element);

	UIElement* CreateImage(iPoint pos, SDL_Rect rect);
	UIElement* CreateButton(iPoint pos, SDL_Rect rect);
	UIElement* CreateCheckBox(iPoint pos, bool checked = false);
	UIElement* CreateLabel(iPoint pos, p2SString text);
	UIElement* CreateSlider(iPoint pos, SDL_Rect slider_rect);

	UIElement* GetMouseElement(iPoint pos);

private:

	p2List<UIElement*> ui_elements;

	SDL_Texture* ui_tex = nullptr;
	p2SString ui_texture;
};

#endif // __!UIMANAGER_H__
