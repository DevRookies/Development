#include "DevRookiesApp.h"
#include "GUIButton.h"
#include "p2Log.h"
#include "GUIManager.h"
#include "GUISlider.h"
#include "Render.h"
GUISlider::GUISlider(iPoint pos, SDL_Rect rect) : GUIElement(pos, GUI_Type::SLIDER, callback)
{
	this->position = pos;
	this->rect = rect;
	slider_btn = App->guimanager->CreateButton(pos, rect, rect, rect, callback);
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
	App->render->DrawQuad(rect, 255, 0, 0, 255, true, false);
	return ret;
}