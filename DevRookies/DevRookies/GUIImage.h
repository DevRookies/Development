#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__

#include "GUIElement.h"

class GUIImage : public GUIElement
{
public:

	GUIImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture = nullptr);
	virtual ~GUIImage();
	bool PostUpdate();
};

#endif //__!GUIIMAGE_H__
