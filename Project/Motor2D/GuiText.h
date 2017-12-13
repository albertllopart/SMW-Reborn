#ifndef __GUI_TEXT__
#define __GUI_TEXT__

#include "p2SString.h"
#include "GuiElement.h"

struct SDL_Texture;

class GuiText : public GuiElement
{
public:

	GuiText();
	GuiText(iPoint position, char* string, SDL_Color color, _TTF_Font* font, menu_type mtype);
	~GuiText();

	void Draw();

public:

	p2SString string;
	SDL_Texture* text;
	SDL_Color color;

};

#endif