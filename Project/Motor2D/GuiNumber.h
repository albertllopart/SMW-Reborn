#ifndef __GUI_NUMBER__
#define __GUI_NUMBER__

#include "p2Point.h"
#include "j1App.h"
#include "GuiElement.h"
#include "SDL\include\SDL.h"
#include "p2Defs.h"

struct SDL_Texture;
struct SDL_Rect;
struct _TTF_FONT;
class GuiImage;

class GuiNumber : public GuiElement
{
public:

	GuiNumber();
	GuiNumber(iPoint position, uint* number, SDL_Color color, _TTF_Font* font, menu_type mtype, bool follow_camera);
	~GuiNumber();

	void Draw();

public:

	SDL_Texture* texture;
	SDL_Color color;
	_TTF_Font* font = nullptr;
	uint* number = nullptr;
};

#endif