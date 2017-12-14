#include "GuiButton.h"
#include "GuiImage.h"
#include "j1Render.h"

GuiButton::GuiButton() {};

GuiButton::GuiButton(iPoint position, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, menu_type mtype, j1Module* callback, bool follows_camera)
{
	this->position = position;
	this->rect = rect;
	this->mover = mover;
	this->pressed = pressed;
	this->btype = btype;
	this->mtype = mtype;
	this->callback = callback;
	this->follows_camera = follows_camera;

	if (mtype == MAINMENU || mtype == OTHER)
	{
		active = true;
	}
	else
	{
		active = false;
	}

	etype = BUTTON;
}

GuiButton::~GuiButton() {};

void GuiButton::Draw()
{
	if (active && follows_camera == false)
	{
		if (mouseover == true && selected == false)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &mover);
		}
		else if (selected == true)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &pressed);
		}
		else
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect);
		}
	}
	else if (active && follows_camera == true)
	{
		if (mouseover == true && selected == false)
		{
			App->render->Blit(App->gui->GetAtlas(), position_camera.x, position.y, &mover);
		}
		else if (selected == true)
		{
			App->render->Blit(App->gui->GetAtlas(), position_camera.x, position.y, &pressed);
		}
		else
		{
			App->render->Blit(App->gui->GetAtlas(), position_camera.x, position.y, &rect);
		}
	}
}

void GuiButton::OnClick()
{
	if (mouseover == true && active == true)
	{
		callback->GuiTrigger(this);
	}
	return;
}