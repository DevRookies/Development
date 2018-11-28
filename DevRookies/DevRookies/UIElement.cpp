#include "DevRookiesApp.h"
#include "UIElement.h"
#include "Render.h"
#include "UIManager.h"
#include "Input.h"
#include "Textures.h"


UIElement::UIElement(UI_Type type, Module* callback)
{

}

UIElement::~UIElement()
{
	App->textures->UnLoad(texture);
	texture = nullptr;
}


iPoint UIElement::GetLocalPosition() const
{
	return this->local_position;
}

iPoint UIElement::GetScreenPosition() const
{
	return this->screen_position;
}

void UIElement::SetLocalPosition(iPoint pos) 
{
	this->local_position = iPoint(pos);
}

void UIElement::SetScreenPosition(iPoint pos) 
{
	this->screen_position = iPoint(pos);
}