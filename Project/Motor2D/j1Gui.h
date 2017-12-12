#ifndef __j1GUI_H__
#define __j1GUI_H__ 

#include "j1App.h"
#include "j1Module.h"
#include "p2List.h"

#define CURSOR_WIDTH 2

struct SDL_Rect;
struct SDL_Texture;
class GuiElement;

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
	NONE
};

class j1Gui : public j1Module
{
public:

	j1Gui();
	virtual ~j1Gui();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool PostUpdate();

	bool CleanUp();


	SDL_Texture* GetAtlas() const;

	bool MouseOnRect(SDL_Rect rect);

	bool GuiTrigger(GuiElement* element);

	GuiElement* CreateImage(int x, int y, SDL_Rect rect);

	GuiElement* CreateButton(int x, int y, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, j1Module* callback);

	void DeleteElement(GuiElement* element);

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<GuiElement*> elements;

};

#endif