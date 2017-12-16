#include "GuiSlider.h"
#include "GuiImage.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Module.h"
#include "j1Render.h"
#include "j1Input.h"
#include "GuiElement.h"

GuiSlider::GuiSlider() {};

GuiSlider::GuiSlider(iPoint position, SDL_Rect rect, SDL_Rect bar_rect, slider_type stype, menu_type mtype, j1Module* callback, bool follows_camera)
{
	this->position = position;
	this->rect = rect;
	this->stype = stype;
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

	top = position.y;
	bottom = position.y + bar_rect.h - rect.h;//setting the minimum height the slider can reach without going any further from the bar

	bar = App->gui->CreateImage(position.x, position.y, bar_rect, mtype, 0, true);
	bar->active = false;

	etype = SLIDER;
}

GuiSlider::~GuiSlider() {};

void GuiSlider::Draw()
{
	if (active == true)
	{
		App->render->Blit(App->gui->GetAtlas(), bar->position.x, bar->position.y, &bar->rect);
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect);
	}
}

void GuiSlider::OnClick()
{
	if (mouseover == true && active == true)
	{
		int x, y;
		App->input->GetMousePosition(x, y);
		stored_mouse.create(x, y);
	}
}

void GuiSlider::OnDrag()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (mouseover == true && active == true)
	{
		if (y > stored_mouse.y)
		{
			if (position.y < bottom)
				position.y += y - stored_mouse.y;
		}
		else if (y < stored_mouse.y)
		{
			if (position.y > top)
				position.y -= stored_mouse.y - y;
		}
	}
}

