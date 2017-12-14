#ifndef __GUI_IMAGE__
#define __GUI_IMAGE__

#include "GuiElement.h"
#include "p2Point.h"
#include "j1App.h"
#include "SDL\include\SDL.h"
#include "p2Defs.h"
#include "j1Animation.h"

class GuiImage : public GuiElement
{
public:

	GuiImage();
	GuiImage(iPoint position, SDL_Rect rect, menu_type mtype, uint index = 0, bool follows_camera = false);
	~GuiImage();

	void Draw();
	void DrawStatus();

public:

	Animation status;
	uint index = 0;

	image_type itype = DEFAULT;

};

#endif