#ifndef __GUIELEMENT_H__
#define __GUIELEMENT_H__

#include "p2Point.h"
#include "SDL\include\SDL_rect.h"
#include "Module.h"

struct SDL_Texture;

enum class GUI_Type
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
	GUIElement(iPoint pos, GUI_Type type,Module* callback = nullptr);
	virtual ~GUIElement();

	virtual bool Update(float dt);
	virtual bool PostUpdate() { return true; };
	virtual void Draw(SDL_Texture* texture);
	//virtual void DebugDraw();

	iPoint GetPosition() const;
	void SetPosition(iPoint pos);
	SDL_Rect GetRect() const;


public:
	SDL_Texture* texture = nullptr;
	p2SString   tex;
	GUI_Type	type;
	SDL_Rect	rect;
	iPoint		position,screen_position;
	Module*		callback = nullptr;
	bool		to_delete = false;
	bool		hovered = false;

private:

	bool debug = false;
	
};

#endif // __!GUIELEMENT_H__
