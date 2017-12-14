#ifndef __j1GUI_H__
#define __j1GUI_H__ 

#include "j1App.h"
#include "j1Module.h"
#include "p2List.h"
#include "j1Fonts.h"

#define CURSOR_WIDTH 2

struct SDL_Rect;
struct SDL_Texture;
enum menu_type;
class GuiElement;
class GuiImage;
class GuiButton;

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

	GuiImage* CreateImage(int x, int y, SDL_Rect rect, menu_type mtype, uint index = 0);

	GuiButton* CreateButton(int x, int y, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, menu_type mtype, j1Module* callback);

	GuiElement* CreateText(int x, int y, char* string, SDL_Color color, _TTF_Font* font, menu_type mtype);

	void DeleteElement(GuiElement* element);

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<GuiElement*> elements;

};

#endif