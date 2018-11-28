#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__

#include "GUIElement.h"

class GUIImage : public GUIElement
{
private:
	SDL_Rect image;

public:

	GUIImage(iPoint pos);
	virtual ~GUIImage();
	bool Awake(pugi::xml_node & conf);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:
	//SDL_Texture *  image_texture = nullptr;
	//p2SString   gui_image_tex;
};

#endif //__!GUIIMAGE_H__
