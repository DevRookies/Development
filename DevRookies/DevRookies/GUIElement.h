#ifndef __GUIELEMENT_H__
#define __GUIELEMENT_H__

#include "p2Point.h"
#include "SDL\include\SDL_rect.h"
#include "Module.h"

struct SDL_Texture;

enum GUI_Type
{
	IMAGE,
	LABEL,
	BUTTON,
	CHECKBOX,
	SLIDER,
	NO_TYPE
};

enum GUI_State
{
	NORMAL,
	PRESSED,
	HOVERED,
	NO_STATE
};

class GUIElement
{
public:
	GUIElement(iPoint pos, GUI_Type type,bool draggable = false,GUIElement* parent = nullptr);
	virtual ~GUIElement();

	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };

	iPoint GetPosition() const;
	SDL_Rect GetRect() const;

	void Enabled(bool enabled);
	void SetLocalPosition(int x, int y);

public:
	SDL_Texture* texture = nullptr;
	p2SString   tex;
	GUI_Type	type;
	SDL_Rect	rect;
	iPoint		position;
	iPoint		relative_position;
	GUIElement* parent = nullptr;
	GUI_State	state;
	bool		enabled = false;
	bool		draggable = false;

};

#endif // __!GUIELEMENT_H__
