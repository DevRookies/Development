#include "DevRookiesApp.h"
#include "UI_Image.h"
#include "p2Log.h"


UIImage::UIImage(iPoint pos, SDL_Rect rect): UIElement(UI_Type::IMAGE)
{
	image = rect;
}

//bool UIImage::UpdateImage(SDL_Rect rect)
//{
//	bool ret = true;
//
//	current_rect = rect;
//
//	return ret;
//}