#ifndef __GUI_SLIDER__
#define __GUI_SLIDER__

#include "p2Point.h"
#include "j1App.h"
#include "GuiElement.h"
#include "SDL\include\SDL.h"
#include "p2Defs.h"

struct SDL_Texture;
struct SDL_Rect;

class GuiSlider : public GuiElement
{
public:

	GuiSlider();
	GuiSlider(iPoint position, SDL_Rect rect, SDL_Rect bar_rect, slider_type stype, menu_type mtype, j1Module* callback, bool follows_camera);
	~GuiSlider();

	void Draw();

	void OnClick();

	void OnDrag();

public:

	slider_type stype;

	GuiImage* bar = nullptr;
	uint top;
	uint bottom;

	j1Module* callback = nullptr;

	//drag
	iPoint stored_mouse;

};

#endif