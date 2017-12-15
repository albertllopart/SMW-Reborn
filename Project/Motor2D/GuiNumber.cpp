#include "GuiNumber.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Fonts.h"

GuiNumber::GuiNumber() {};

GuiNumber::GuiNumber(iPoint position, uint* number, SDL_Color color, _TTF_Font* font, menu_type mtype, bool follows_camera)
{
	this->position = position;
	this->number = number;
	this->color = color;
	this->font = font;
	this->follows_camera = follows_camera;
	this->mtype = mtype;

	etype = NUMBER;
}

GuiNumber::~GuiNumber() {};

void GuiNumber::Draw()
{
	p2SString string;
	sprintf(string.str, "%i", *number);

	texture = App->tex->textures.add(App->fonts->Print(string.str, color, font))->data;

	if (active == true && follows_camera == false)
		App->render->Blit(texture, position.x, position.y);
	else if (active == true && follows_camera == true)
		App->render->Blit(texture, position_camera.x, position.y);
}