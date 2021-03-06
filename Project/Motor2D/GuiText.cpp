#include "GuiText.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Render.h"

GuiText::GuiText() {};

GuiText::GuiText(iPoint position, char* string, SDL_Color color, _TTF_Font* font, menu_type mtype, bool follows_camera)
{
	this->position = position;
	this->string = string;
	this->color = color;
	this->mtype = mtype;
	this->follows_camera = follows_camera;
	
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

GuiText::~GuiText() 
{
	App->tex->UnLoad(text);
};

void GuiText::Draw()
{
	if(active == true && follows_camera == false)
		App->render->Blit(text, position.x, position.y);
	else if(active == true && follows_camera == true)
		App->render->Blit(text, position_camera.x, position.y);
}