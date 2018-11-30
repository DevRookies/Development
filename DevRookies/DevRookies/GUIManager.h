#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "GUILabel.h"


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

	

	GUIImage* CreateImage(iPoint pos, SDL_Rect rect, Module* callback = nullptr);
	GUIButton* CreateButton(iPoint pos, SDL_Rect rect, Module* callback = nullptr);
	GUILabel* CreateLabel(iPoint pos, p2SString text, Module* callback = nullptr);
	//GUICheckBox* CreateCheckBox(iPoint pos, p2SString text, iPoint displacement = { 0,0 }, Module* callback = nullptr);
	//GUISlider* CreateSlider(iPoint pos, uint num_buttons, p2SString title, iPoint displacement = { 0,0 }, Module* callback = nullptr);

	GUIElement* GetMouseElement(iPoint pos);

private:

	GUIElement * CreateElement(GUI_Type type, iPoint pos);
	void UpdateElemEvent() const;
	bool ManageElemEvent();
	void DestroyGUIElement(GUIElement* element);

	p2List<GUIElement*> gui_elements;
	SDL_Texture* texture = nullptr;
	p2SString gui_texture;

	bool debug = false;
};

#endif // __!GUIMANAGER_H__
