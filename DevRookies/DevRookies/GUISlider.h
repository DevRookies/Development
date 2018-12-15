#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "Fonts.h"
#include "GUIElement.h"
#include "GUIButton.h"

class GUISlider : public GUIElement
{
public:
	SDL_Rect slider_rect;

private:
	uint value = 0u; //float
	GUIButton* slider_btn = nullptr;

public:
	GUISlider(iPoint pos, SDL_Rect rectangle, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, SDL_Texture* texture = nullptr);
	virtual ~GUISlider();

	void SetButton(GUIButton* slider_btn);
	void SetValue(bool horizontal);
	void SetStartValue(bool horizontal, int value);

	uint GetValue() const;
	GUIButton* GetButton() const;

	bool Update(float dt);
	bool PostUpdate();
};
#endif //__!GUISLIDER_H__ 