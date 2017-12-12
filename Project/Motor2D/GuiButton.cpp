#include "GuiButton.h"
#include "j1Render.h"

GuiButton::GuiButton() {};

GuiButton::GuiButton(iPoint position, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, j1Module* callback)
{
	this->position = position;
	this->rect = rect;
	this->mover = mover;
	this->pressed = pressed;
	this->btype = btype;
	active = true;
	this->callback = callback;

	etype = BUTTON;
}

GuiButton::~GuiButton() {};

void GuiButton::Draw()
{
	if (active)
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
}

void GuiButton::OnClick()
{
	if (mouseover == true && active == true)
	{
		selected = true;
		callback->GuiTrigger(this);
	}
	return;
}