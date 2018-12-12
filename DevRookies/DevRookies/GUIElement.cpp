#include "GUIManager.h"
#include "GUIElement.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Input.h"
#include "Textures.h"


GUIElement::GUIElement(iPoint pos, GUI_Type type, Module* callback)
{
	this->position = pos;
	this->callback = callback;
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

	return true;
}

void GUIElement::Draw(SDL_Texture* sprites)
{
	//debug draw
}

iPoint GUIElement::GetPosition() const
{
	return this->position;
}

/*void GUIElement::SetPosition(iPoint pos) 
{
	this->screen_position = iPoint(pos);
}*/

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