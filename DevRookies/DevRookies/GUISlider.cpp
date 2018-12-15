#include "DevRookiesApp.h"
#include "GUIButton.h"
#include "p2Log.h"
#include "GUIManager.h"
#include "GUISlider.h"
#include "Render.h"

GUISlider::GUISlider(iPoint pos, SDL_Rect rectangle, SDL_Texture* texture) : GUIElement(pos, GUI_Type::SLIDER, callback)
{
	//this->position = pos;

	this->slider_rect = rectangle;
	rect = rectangle;

	this->position = pos;
	this->texture = texture;

	/*rect.x = position.x;
	rect.y = position.y;*/

	//make this dont blit when enabled == false
	//slider_btn = App->guimanager->CreateButton(pos, rectangle, rectangle, rectangle, callback);
}

GUISlider::~GUISlider()
{
}

void GUISlider::SetButton(GUIButton * slider_btn)
{
	this->slider_btn = slider_btn;
}

void GUISlider::SetValue(uint slider_btn_pos)
{
	value = slider_btn_pos * 100 / (rect.w - slider_btn->GetRect().w);
}

void GUISlider::SetStartValue(int value) {
	value = value * 100 / (rect.w - slider_btn->GetRect().w);
	this->slider_btn->SetLocalPosition((this->rect.w + 2) * value / 100, 0);
}

uint GUISlider::GetValue() const
{
	return value;
}

GUIButton * GUISlider::GetButton() const
{
	return slider_btn;
}

bool GUISlider::PostUpdate()
{
	bool ret = true;
	
	App->render->Blit(texture, position.x, position.y, &slider_rect, 0.0f);

	return ret;
}