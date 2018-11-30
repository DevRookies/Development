#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GUIElement.h"
#include "Fonts.h"
#include "GUILabel.h"

class GUIButton : public GUIElement
{
private:
	SDL_Rect normal;
	SDL_Rect hovered;
	SDL_Rect pressed;
	GUILabel* label = nullptr;

public:

	GUIButton(iPoint pos);
	virtual ~GUIButton();
	bool Awake(pugi::xml_node & conf);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void PrintText();
private:
	//SDL_Texture *  image_texture = nullptr;
	//p2SString   gui_image_tex;
};

#endif //__!GUIBUTTON_H__
