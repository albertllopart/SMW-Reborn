#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
//#include "j1Fonts.h"
#include "j1Input.h"
#include "j1EntityModule.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "j1Gui.h"
#include "j1Fonts.h"

#include "GuiElement.h"
#include "GuiImage.h"
#include "GuiButton.h"
#include "GuiText.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{
	App->tex->UnLoad(atlas);
}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	App->entitymodule->active = false;
	App->pathfinding->active = false;
	App->collision->active = false;

	atlas = App->tex->Load(atlas_file_name.GetString());
	App->audio->PlayMusic("audio/title_theme.ogg");

	//main menu
	CreateImage(0, 0, { 0,0,400,240 }, OTHER);//main screen
	CreateImage(105, 35, { 400, 65, 214, 61 }, MAINMENU);//super mario world
	CreateButton(185, 120, { 400, 0, 30, 7 }, { 462, 0, 30, 7 }, { 524, 0, 30, 7 }, PLAY, MAINMENU, (j1Module*)App->gui);//play
	CreateButton(169, 135, { 400, 8, 60, 7 }, { 462, 8, 60, 7 }, { 524, 8, 60, 7 }, CONTINUE, MAINMENU, (j1Module*)App->scene);//continue
	CreateButton(169, 150, { 400, 16, 60, 7 }, { 462, 16, 60, 7 }, { 524, 16, 60, 7 }, SETTINGS, MAINMENU, (j1Module*)App->gui);//settings
	CreateButton(173, 165, { 400, 24, 52, 7 }, { 462, 24, 52, 7 }, { 524, 24, 52, 7 }, CREDITS, MAINMENU, (j1Module*)App->gui);//credits
	CreateButton(186, 180, { 400, 32, 28, 7 }, { 462, 32, 28, 7 }, { 524, 32, 28, 7 }, EXIT, MAINMENU, (j1Module*)App->scene);//exit

	//credits menu
	CreateButton(288, 32, { 400, 127, 44, 19 }, { 444, 127, 44, 19 }, { 444, 127, 44, 19 }, BACK, CREDITSMENU, (j1Module*)App->gui);//credditsback
	CreateText(60, 40, "LOOK AT THESE CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU);
	CreateText(60, 55, "WOW SUCH CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU);
	CreateText(60, 70, "AMAZING CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU);
	CreateText(60, 85, "UNBELIEVEABLE CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU);
	CreateText(60, 100, "even  with  lowercase  wow", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	p2List_item<GuiElement*>* item = elements.start;
	while (item != nullptr)
	{
		if (item->data->active == true && MouseOnRect({ item->data->position.x, item->data->position.y, item->data->rect.w, item->data->rect.h }) == true)
		{
			item->data->mouseover = true;
		}
		else
		{
			item->data->mouseover = false;
		}

		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
		{
			item->data->OnClick();
		}
		item = item->next;
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<GuiElement*>* item = elements.start;
	while (item != nullptr)
	{
		item->data->Draw();
		item = item->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

GuiElement* j1Gui::CreateImage(int x, int y, SDL_Rect rect, menu_type mtype)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiImage(position, rect, mtype);

	elements.add(item);

	return item;
}

GuiElement* j1Gui::CreateButton(int x, int y, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, menu_type mtype, j1Module* callback)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiButton(position, rect, mover, pressed, btype, mtype, callback);

	elements.add(item);

	return item;
}

GuiElement* j1Gui::CreateText(int x, int y, char* string, SDL_Color color, _TTF_Font* font, menu_type mtype)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiText(position, string, color, font, mtype);

	elements.add(item);

	return item;
}

void j1Gui::DeleteElement(GuiElement* element)
{
	if (element != nullptr)
	{
		int find = elements.find(element);
		int current_position = 0;
		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (current_position == find)
			{
				elements.del(item);
				return;
			}
			item = item->next;
			current_position++;
		}
	}
}

bool j1Gui::MouseOnRect(SDL_Rect rect)
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (x < (rect.x + rect.w) && x > rect.x &&y < (rect.y + rect.h) && y > rect.y)
		return true;
	else
		return false;
}

bool j1Gui::GuiTrigger(GuiElement* element)
{
	GuiButton* button = (GuiButton*)element;

	switch (button->btype)
	{
	case PLAY:
	{
		App->pathfinding->active = true;
		App->collision->active = true;
		App->entitymodule->active = true;

		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			item->data->active = false;
			item = item->next;
		}

		App->audio->PlayMusic("audio/main_music.ogg");

		break;
	}
		
	case SETTINGS:
	{
		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (item->data->mtype != SETTINGSMENU)
			{
				item->data->active = false;
			}
			else if (item->data->mtype == SETTINGSMENU)
			{
				item->data->active = true;
			}
			item = item->next;
		}

		break;
	}

	case CREDITS:
	{
		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (item->data->mtype != CREDITSMENU && item->data->mtype != OTHER)
			{
				item->data->active = false;
			}
			else if (item->data->mtype == CREDITSMENU)
			{
				item->data->active = true;
			}
			item = item->next;
		}

		break;
	}

	case BACK:
	{
		switch (button->mtype)
		{
		case CREDITSMENU:
		{
			p2List_item<GuiElement*>* item = elements.start;
			while (item != NULL)
			{
				if (item->data->mtype == MAINMENU || item->data->mtype == OTHER)
				{
					item->data->active = true;
				}
				else if (item->data->mtype == CREDITSMENU)
				{
					item->data->active = false;
				}
				item = item->next;
			}
			break;
		}
		}

		break;
	}
	}
	return true;
}

// class Gui ---------------------------------------------------

