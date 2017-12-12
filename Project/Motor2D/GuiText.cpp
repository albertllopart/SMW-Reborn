#include "GuiText.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Render.h"

GuiText::GuiText() {};

GuiText::GuiText(iPoint position, char* string, SDL_Color color, _TTF_Font* font)
{
	this->position = position;
	this->string = string;
	this->color = color;
	active = true;

	text = App->tex->textures.add(App->fonts->Print(string, color, font))->data;

	etype = TEXT;
}

GuiText::~GuiText() {};

void GuiText::Draw()
{
	if(active == true)
		App->render->Blit(text, position.x, position.y);
}