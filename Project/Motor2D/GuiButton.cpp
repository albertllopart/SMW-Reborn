#include "GuiButton.h"
#include "j1Render.h"

GuiButton::GuiButton() {};

GuiButton::GuiButton(iPoint position, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype)
{
	this->position = position;
	this->rect = rect;
	this->mover = mover;
	this->pressed = pressed;
	btype = btype;

	etype = BUTTON;
}

GuiButton::~GuiButton() {};

void GuiButton::Draw()
{
	if (active)
	{
		if (mouseover)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &mover);
		}
		else
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect);
		}
	}
}

void GuiButton::OnClick()
{
	return;
}