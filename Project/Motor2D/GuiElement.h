#ifndef __GUI_ELEMENT__
#define __GUI_ELEMENT__

#include "j1Module.h"
#include "j1Gui.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "p2Defs.h"


struct SDL_Rect;

enum element_type
{
	IMAGE,
	BUTTON,
	TEXT,
	EMPTY
};

enum image_type
{
	MENUBACKGROUND,
	PAUSEBACKGROUND,
	DEFAULT
};

enum menu_type
{
	MAINMENU,
	SETTINGSMENU,
	CREDITSMENU,
	PAUSEMENU,
	OTHER
};

class GuiElement
{
public:

	GuiElement();
	virtual ~GuiElement();

	virtual void Start();

	void Update(float dt);

	virtual void Draw();

	virtual void OnClick();

public:

	element_type etype = EMPTY;
	menu_type mtype = OTHER;

	iPoint position;
	bool mouseover;
	bool active;
	bool selected;

	SDL_Rect rect;
};

#endif