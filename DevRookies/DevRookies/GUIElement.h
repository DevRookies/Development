#ifndef __GUIELEMENT_H__
#define __GUIELEMENT_H__

#include "p2Point.h"
#include "SDL\include\SDL_rect.h"
#include "GUIManager.h"
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
	MOUSE_ENTER,
	MOUSE_LEAVE,
	LEFT_MOUSE_PRESSED,
	LEFT_MOUSE_RELEASED,
	RIGHT_MOUSE_PRESSED,
	LEFT_MOUSE_RELEASED,
	HOVERED,

	NO_TYPE
};

class GUIElement
{

public:
	GUIElement(GUI_Type type,Module* callback = nullptr);
	virtual ~GUIElement();

	virtual bool Awake(pugi::xml_node&config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update();
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	//virtual void Draw(SDL_Texture* texture);
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

private:

	bool debug = false;
	
};

#endif // __!GUIELEMENT_H__
