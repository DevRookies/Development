#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "GUIElement.h"
#include "p2SString.h"
#include "Fonts.h"


class GUILabel : public GUIElement
{
private:
	Fonts normal_font;

	int size = 0;
	
public:
	GUILabel(iPoint pos,p2SString text, int size);
	~GUILabel();
	void SetText(p2SString text);


public:
	p2SString text;
};

#endif //__GUILABEL_H__