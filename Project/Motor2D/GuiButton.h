#ifndef __GUI_BUTTON__
#define __GUI_BUTTON__

#include "p2Point.h"
#include "j1App.h"
#include "GuiElement.h"
#include "SDL\include\SDL.h"
#include "p2Defs.h"

struct SDL_Texture;
struct SDL_Rect;
class GuiImage;

class GuiButton : public GuiElement
{
public:

	GuiButton();
	GuiButton(iPoint position, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, menu_type mtype, j1Module* callback);
	~GuiButton();

	void Draw();

	//interaction
	void OnClick();

public:

	button_type btype;

	//SDL_Rect brect;
	SDL_Rect mover;
	SDL_Rect pressed;

	j1Module* callback = nullptr;
	GuiImage* imgcallback = nullptr;
};

#endif