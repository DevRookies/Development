#include "DevRookiesApp.h"
#include "GUILabel.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"

#include "Brofiler\Brofiler.h"


GUILabel::GUILabel(iPoint pos, p2SString text, _TTF_Font* font) : GUIElement(pos, GUI_Type::LABEL, callback)
{
	SetText(text);
	this->font = font;
}

GUILabel::~GUILabel()
{}

void GUILabel::SetText(p2SString text)
{
	text.create(text.GetString());

	int width = 0, height = 0;
	App->fonts->CalcSize(text.GetString(), width, height, font);
	rect.w = width;
	rect.h = height;

	SDL_Color color = { 255, 255, 255, 255 };
	texture = App->fonts->Print(text.GetString(), color, font);
}

bool GUILabel::PostUpdate()
{
	bool ret = false;

	App->render->Blit(texture, position.x - rect.w / 2, position.y - rect.h / 2, &rect, 0.0f);

	return ret;
}
