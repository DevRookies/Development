#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GUIElement.h"

class GUIButton : public GUIElement
{
private:
	SDL_Texture * texture = nullptr;
	SDL_Rect normal;
	SDL_Rect hovered;
	SDL_Rect pressed;

public:

	GUIButton(iPoint pos, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, bool draggable = false, SDL_Texture* texture = nullptr);
	virtual ~GUIButton();
	bool PostUpdate();
	
};

#endif //__!GUIBUTTON_H__
