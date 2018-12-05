#include "DevRookiesApp.h"
#include "GUIButton.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"
#include "GUIManager.h"

#include "Brofiler\Brofiler.h"


GUIButton::GUIButton(iPoint pos, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, SDL_Texture* texture) : GUIElement(pos, GUI_Type::BUTTON, callback)
{
	this->normal = normal;
	this->hovered = hovered;
	this->pressed = pressed;
	this->texture = texture;
}

GUIButton::~GUIButton()
{

}


bool GUIButton::PostUpdate()
{
	bool ret = false;

	switch (App->guimanager->state) {
	case GUI_State::HOVERED:
		App->render->Blit(texture, position.x, position.y, &hovered, 0.0f);
		break;
	case GUI_State::NORMAL:
		App->render->Blit(texture, position.x, position.y, &normal, 0.0f);
		break;
	case GUI_State::PRESSED:
		App->render->Blit(texture, position.x, position.y, &pressed, 0.0f);
		break;
	}

	return ret;
}