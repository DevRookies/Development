#include "DevRookiesApp.h"
#include "GUILabel.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"

#include "Brofiler\Brofiler.h"


GUILabel::GUILabel(iPoint pos, p2SString text, int size) : GUIElement(GUI_Type::LABEL)
{
}

GUILabel::GUILabel(iPoint pos, p2SString text, int size, uint32 boxWidth) : GUIElement(GUI_Type::LABEL) 
{

}

GUILabel::~GUILabel()
{}

void GUILabel::SetText(p2SString text)
{

	App->textures->UnLoad(texture);
	texture = nullptr;
	this->text = text;

	int width = 0, height = 0;
	App->fonts->CalcSize(this->text.GetString(), width, height, App->font->default);
	current_rect.w = width;
	current_rect.h = height;
}
