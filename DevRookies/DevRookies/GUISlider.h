#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "Fonts.h"
#include "GUIElement.h"
#include "GUIButton.h"

class GUIButton;

class GUISlider : public GUIElement
{
public:
	SDL_Rect slider_rect = { 0,0,0,0 };

private:
	uint value = 0u;
	GUIButton* slider_btn = nullptr;
	bool horizontal = true;

public:
	GUISlider(iPoint pos, SDL_Rect rectangle, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, bool horizontal, SDL_Texture* texture = nullptr);
	virtual ~GUISlider();

	void SetButton(GUIButton* slider_btn);
	void SetValue(int value);

	uint GetValue() const;
	GUIButton* GetButton() const;

	bool Update(float dt);
	bool PostUpdate();
};
#endif //__!GUISLIDER_H__ 