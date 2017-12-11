#ifndef __GUI_IMAGE__
#define __GUI_IMAGE__

#include "GuiElement.h"
#include "p2Point.h"
#include "j1App.h"
#include "SDL\include\SDL.h"
#include "p2Defs.h"

class GuiImage : public GuiElement
{
public:

	GuiImage();
	GuiImage(iPoint position, SDL_Rect rect);
	~GuiImage();

	void Draw();

public:


};

#endif