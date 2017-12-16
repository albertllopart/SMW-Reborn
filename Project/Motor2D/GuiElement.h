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
	NUMBER,
	EMPTY
};

enum image_type
{
	MENUBACKGROUND,
	PAUSEBACKGROUND,
	DEFAULT
};

enum button_type
{
	PLAY,
	CONTINUE,
	SETTINGS,
	CREDITS,
	EXIT,
	MUSICUP,
	MUSICDOWN,
	FXUP,
	FXDOWN,
	BACK,
	RESUME,
	SAVEANDRESUME,
	SAVEANDEXIT,
	NONE
};

enum slider_type
{
	MUSIC,
	FX,
	UNDEFINED
};

enum menu_type
{
	MAINMENU,
	SETTINGSMENU,
	CREDITSMENU,
	PAUSEMENU,
	INGAMEMENU,
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

	void PositionUpdate();

public:

	element_type etype = EMPTY;
	menu_type mtype = OTHER;

	iPoint position;
	iPoint position_camera;
	bool mouseover;
	bool active;
	bool selected;
	bool follows_camera;

	SDL_Rect rect;
};

#endif