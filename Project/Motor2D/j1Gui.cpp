#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
//#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

#include "GuiElement.h"
#include "GuiImage.h"
#include "GuiButton.h"

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
	atlas = App->tex->Load(atlas_file_name.GetString());

	CreateImage(0, 0, { 0,0,400,240 });//main screen
	CreateButton(185, 120, { 400, 0, 30, 7 }, { 400, 0, 30, 7 }, { 400, 0, 30, 7 }, PLAY);//play
	CreateButton(169, 135, { 400, 8, 60, 7 }, { 400, 8, 60, 7 }, { 400, 8, 60, 7 }, CONTINUE);//continue

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
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

GuiElement* j1Gui::CreateImage(int x, int y, SDL_Rect rect)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiImage(position, rect);

	elements.add(item);

	return item;
}

GuiElement* j1Gui::CreateButton(int x, int y, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiButton(position, rect, mover, pressed, btype);

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

void j1Gui::Trigger()
{
	return;
}

// class Gui ---------------------------------------------------

