#include "GuiText.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Render.h"

GuiText::GuiText() {};

GuiText::GuiText(iPoint position, char* string, SDL_Color color, _TTF_Font* font, menu_type mtype)
{
	this->position = position;
	this->string = string;
	this->color = color;
	this->mtype = mtype;
	
	if (mtype == MAINMENU || mtype == OTHER)
	{
		active = true;
	}
	else
	{
		active = false;
	}

	text = App->tex->textures.add(App->fonts->Print(string, color, font))->data;

	etype = TEXT;
}

GuiText::~GuiText() {};

void GuiText::Draw()
{
	if(active == true)
		App->render->Blit(text, position.x, position.y);
}