#include "GuiImage.h"
#include "j1Render.h"

GuiImage::GuiImage() {};

GuiImage::GuiImage(iPoint position, SDL_Rect rect, menu_type mtype)
{
	this->position = position;
	this->rect = rect;
	this->mtype = mtype;
	
	if (mtype == MAINMENU || mtype == OTHER)
	{
		active = true;
	}
	else
	{
		active = false;
	}

	etype = IMAGE;
}

GuiImage::~GuiImage() {};

void GuiImage::Draw()
{
	if (active)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect);
	}
}