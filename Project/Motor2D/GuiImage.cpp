#include "GuiImage.h"
#include "j1Render.h"

GuiImage::GuiImage() {};

GuiImage::GuiImage(iPoint position, SDL_Rect rect, menu_type mtype, uint index, bool follows_camera)
{
	this->position = position;
	this->rect = rect;
	this->mtype = mtype;
	this->index = index;
	this->follows_camera = follows_camera;
	
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
	if (active && follows_camera == false)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect);
	}
	else if (active && follows_camera == true)
	{
		App->render->Blit(App->gui->GetAtlas(), position_camera.x, position.y, &rect);
	}
}

void GuiImage::DrawStatus()
{
	if (active && follows_camera == false)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &status.frames[index]);
	}
	else if (active && follows_camera == true)
	{
		App->render->Blit(App->gui->GetAtlas(), position_camera.x, position.y, &status.frames[index]);
	}
}