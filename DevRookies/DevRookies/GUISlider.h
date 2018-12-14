#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__
#include "Fonts.h"
#include "GUIElement.h"
#include "GUIButton.h"
class GUISlider : public GUIElement
{
public:
	SDL_Rect rect;
private:
	uint value = 0u;
	GUIButton* slider_btn = nullptr;
public:
	GUISlider(iPoint pos, SDL_Rect rect);
	virtual ~GUISlider();
	void SetButton(GUIButton* slider_btn);
	void SetValue(uint slider_btn_pos);
	void SetStartValue(int value);
	uint GetValue() const;
	GUIButton* GetButton() const;
	bool PostUpdate();
};
#endif //__!GUISLIDER_H__ 