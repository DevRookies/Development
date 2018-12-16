#include "GUIManager.h"
#include "GUIElement.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Input.h"
#include "Textures.h"


GUIElement::GUIElement(iPoint pos, GUI_Type type, bool draggable, GUIElement* parent)
{
	this->position = pos;
	this->parent = parent;
	this->draggable = draggable;
	this->type = type;
}

GUIElement::~GUIElement()
{
	App->textures->UnLoad(texture);
	texture = nullptr;
}

iPoint GUIElement::GetPosition() const
{
	return this->position;
}

SDL_Rect GUIElement::GetRect() const 
{
	return rect;
}

void GUIElement::Enabled(bool enabled)
{
	this->enabled = enabled;
}

void GUIElement::SetLocalPosition(int x, int y) {
	this->position = iPoint(x, y);
}