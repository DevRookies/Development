#include "DevRookiesApp.h"
#include "GUILabel.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"

#include "Brofiler\Brofiler.h"


GUILabel::GUILabel(iPoint pos, p2SString text, int size) : GUIElement(GUI_Type::LABEL)
{
	this->text = text;
	this->size = size;

	int width = 0, height = 0;
	App->fonts->CalcSize(this->text.GetString(), width, height, App->fonts->default);
	rect.w = width;
	rect.h = height;
}

GUILabel::~GUILabel()
{}

void GUILabel::SetText(p2SString text)
{
	App->textures->UnLoad(texture);
	texture = nullptr;
	this->text = text;

	int width = 0, height = 0;
	App->fonts->CalcSize(this->text.GetString(), width, height, App->fonts->default);
	rect.w = width;
	rect.h = height;
}
