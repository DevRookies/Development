#include "DevRookiesApp.h"
#include "GUIElement.h"
#include "Render.h"
#include "GUIManager.h"
#include "Input.h"
#include "Textures.h"


GUIElement::GUIElement(GUI_Type type, Module* callback)
{

}

GUIElement::~GUIElement()
{
	App->textures->UnLoad(texture);
	texture = nullptr;
}

bool GUIElement::Update(float dt) 
{
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		debug = !debug;


}

void GUIElement::Draw(SDL_Texture* sprites)
{
	if (rect.w > 0 && rect.h > 0)
	{
		switch (this->type)
		{
		case IMAGE:
		case LABEL:
			App->render->Blit(texture, screen_position.x, screen_position.y, &rect);
			break;
		case BUTTON:
		//case SLIDER:
		//case CHECK_BOX:
		default:
			break;
		}

		if (debug) {
			SDL_Rect tmp_rect{ screen_position.x,screen_position.y,rect.w,rect.h };
			App->render->DrawQuad(tmp_rect, 255, 0, 0, 255, false);
		}
	}
}

iPoint GUIElement::GetPosition() const
{
	return this->position;
}

void GUIElement::SetPosition(iPoint pos) 
{
	this->screen_position = iPoint(pos);
}

SDL_Rect GUIElement::GetRect() const 
{
	return rect;
}

//iPoint GUIElement::GetLocalPosition() const
//{
//	return this->local_position;
//}
//
//iPoint GUIElement::GetScreenPosition() const
//{
//	return this->screen_position;
//}
//
//void GUIElement::SetLocalPosition(iPoint pos) 
//{
//	this->local_position = iPoint(pos);
//}
//
//void GUIElement::SetScreenPosition(iPoint pos) 
//{
//	this->screen_position = iPoint(pos);
//}