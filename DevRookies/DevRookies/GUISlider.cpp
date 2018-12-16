#include "DevRookiesApp.h"
#include "GUIButton.h"
#include "p2Log.h"
#include "GUIManager.h"
#include "GUISlider.h"
#include "Render.h"

GUISlider::GUISlider(iPoint pos, SDL_Rect rectangle, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, bool horizontal, SDL_Texture* texture) : GUIElement(pos, GUI_Type::SLIDER, false, parent)
{
	//this->position = pos;

	this->slider_rect = rectangle;
	rect = rectangle;

	this->position = pos;
	this->texture = texture;
	this->horizontal = horizontal;

	

	/*rect.x = position.x;
	rect.y = position.y;*/

	//make this dont blit when enabled == false
	slider_btn = App->guimanager->CreateButton(pos, normal, hovered, pressed, true, this);
}

GUISlider::~GUISlider()
{
}

void GUISlider::SetButton(GUIButton * slider_btn)
{
	this->slider_btn = slider_btn;
}

void GUISlider::SetValue(int value)
{
	if (horizontal) {
		this->value = value;
		slider_btn->SetLocalPosition(((this->rect.w - slider_btn->GetRect().w) * this->value / 100) + this->GetPosition().x , this->GetPosition().y + (this->rect.h / 2) - (slider_btn->GetRect().h / 2));
	}
	else {
		this->value = value;
		slider_btn->SetLocalPosition(this->GetPosition().x + (this->rect.w / 2) - (slider_btn->GetRect().w / 2), ((this->rect.h - slider_btn->GetRect().h) * this->value / 100) + this->GetPosition().y);
	}
}

uint GUISlider::GetValue() const
{
	int ret = 0;
	if (horizontal)
		ret = (slider_btn->position.x - position.x) * 100 / rect.w;
	else
		ret = (slider_btn->position.y - position.y) * 100 / (rect.h - slider_btn->GetRect().h);
	if (ret > 0 && ret <= 25) ret = 25;
	else if (ret > 25 && ret <= 50) ret = 50;
	else if (ret > 50 && ret <= 75) ret = 75;
	else if (ret > 75) ret = 100;

	return ret;
}

GUIButton * GUISlider::GetButton() const
{
	return slider_btn;
}

bool GUISlider::Update(float dt)
{
	bool ret = true;

	slider_btn->Enabled(enabled);
	
	return ret;
}

bool GUISlider::PostUpdate()
{
	bool ret = true;
	
	App->render->Blit(texture, position.x, position.y, &slider_rect, 0.0f);
	slider_btn->PostUpdate();

	return ret;
}