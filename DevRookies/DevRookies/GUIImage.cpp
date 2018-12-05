#include "DevRookiesApp.h"
#include "GUIImage.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"

#include "Brofiler\Brofiler.h"


GUIImage::GUIImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture): GUIElement(pos, GUI_Type::IMAGE, callback)
{
	this->position = pos;
	this->rect = rect;
	this->texture = texture;
}

GUIImage::~GUIImage()
{

}

bool GUIImage::PostUpdate()
{
	bool ret = false;

	App->render->Blit(texture, position.x, position.y, &rect,0.0f);

	return ret;
}
