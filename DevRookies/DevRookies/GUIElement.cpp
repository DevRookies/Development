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

SDL_Rect GUIElement::GetRect() const 
{
	return rect;
}