#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "GUIElement.h"
#include "p2SString.h"
#include "Fonts.h"


class GUILabel : public GUIElement
{
public:
	GUILabel(iPoint pos,p2SString text, _TTF_Font* font);
	virtual ~GUILabel();

	void SetText(p2SString text);
	bool PostUpdate();

public:
	p2SString text;
	_TTF_Font * font = nullptr;
};

#endif //__GUILABEL_H__