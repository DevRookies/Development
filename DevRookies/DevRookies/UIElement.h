#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "p2Point.h"
#include "UIManager.h"
#include "Animation.h"

struct SDL_Texture;
struct SDL_Rect;


enum UI_Type
{
	IMAGE,
	BUTTON,
	CHECKBOX,
	LABEL,
	SLIDER,
	NO_TYPE

};

class UIElement
{

public:
	UIElement(UI_Type type,Module* callback = nullptr);
	virtual ~UIElement();

	virtual bool Awake(pugi::xml_node&config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	virtual bool Draw(SDL_Texture* texture) { return true; };

	iPoint GetLocalPosition() const;
	iPoint GetScreenPosition() const;

	void SetLocalPosition(iPoint pos);
	void SetScreenPosition(iPoint pos);


public:
	UI_Type type;

private:
	bool debug_UI = false;
	Animation*	current_animation = nullptr;
	iPoint local_position;
	iPoint screen_position;
	SDL_Texture* texture = nullptr;
	Module* callback = nullptr;

};

#endif // __UIELEMENT_H__
