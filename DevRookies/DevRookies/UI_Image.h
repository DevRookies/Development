#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__

//#include "Fonts.h"
#include "UIElement.h"

class UIImage : public UIElement
{
private:
	SDL_Rect image;

public:
	UIImage(iPoint pos, SDL_Rect rect);

	//bool UpdateImage(SDL_Rect rect);
};

#endif //__UIIMAGE_H__
