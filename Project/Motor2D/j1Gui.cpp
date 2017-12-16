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
#include "GuiNumber.h"
#include "GuiSlider.h"



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

	//pause menu
	GuiImage* image = CreateImage(0, 0, { 0, 240, 400, 240 }, PAUSEMENU, 0, true);//pause background
	{
		image->itype = PAUSEBACKGROUND;
	}
	CreateImage(105, 40, { 400, 65, 214, 61 }, PAUSEMENU, 0, true);//super mario world
	CreateText(166, 120, "PAUSE MENU", { 0, 216, 248, 255 }, App->fonts->default, PAUSEMENU, true);
	CreateButton(176, 145, { 400, 197, 46, 7 }, { 493, 197, 46, 7 }, { 493, 197, 46, 7 }, RESUME, PAUSEMENU, (j1Module*)App->gui, true);//resume
	CreateButton(155, 160, { 400, 205, 92, 7 }, { 493, 205, 92, 7 }, { 493, 205, 92, 7 }, SAVEANDRESUME, PAUSEMENU, (j1Module*)App->gui, true);//save and resume
	CreateButton(162, 175, { 400, 213, 74, 7 }, { 493, 213, 74, 7 }, { 493, 213, 74, 7 }, SAVEANDEXIT, PAUSEMENU, (j1Module*)App->gui, true);//save and exit
	CreateButton(169, 190, { 400, 16, 60, 7 }, { 524, 16, 60, 7 }, { 524, 16, 60, 7 }, SETTINGS, PAUSEMENU, (j1Module*)App->gui, true);//settings
	CreateButton(186, 205, { 400, 32, 28, 7 }, { 524, 32, 28, 7 }, { 524, 32, 28, 7 }, EXIT, PAUSEMENU, (j1Module*)App->gui, true);//exit

	//ingame ui
	CreateImage(10, 10, { 413, 40, 12, 15 }, INGAMEMENU, 0, true);//mario lives
	CreateImage(25, 14, { 426, 40, 7, 7 }, INGAMEMENU, 0, true);//mario x
	CreateNumber(37, 8, &App->entitymodule->player->player_lives, { 255, 255, 255, 255 }, App->fonts->numbers, INGAMEMENU, true);//mario lives number

	CreateImage(75, 9, {400, 40, 12, 16}, INGAMEMENU, 0, true);//coins
	CreateImage(90, 14, { 426, 40, 7, 7 }, INGAMEMENU, 0, true);//coins x
	CreateNumber(102, 8, &App->entitymodule->player->player_coins, { 255, 255, 255, 255 }, App->fonts->numbers, INGAMEMENU, true);//coins number

	CreateText(240, 7, "score", { 248, 56, 56, 255 }, App->fonts->default, INGAMEMENU, true);//score
	CreateNumber(240, 19, &App->entitymodule->player->player_score, { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);//score number

	CreateText(300, 7, "timer", { 248, 56, 56, 255 }, App->fonts->default, INGAMEMENU, true);//time
	CreateNumber(300, 19, &App->entitymodule->player->player_hours, { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);
	CreateText(315, 19, "h", { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);//time numbers
	CreateNumber(330, 19, &App->entitymodule->player->player_minutes, { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);
	CreateText(345, 19, "m", { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);//time numbers
	CreateNumber(360, 19, &App->entitymodule->player->player_seconds, { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);
	CreateText(375, 19, "s", { 255, 255, 255, 255 }, App->fonts->default, INGAMEMENU, true);//time numbers

	//ShellExecute(NULL, "open", "https://www.google.com", NULL, NULL, SW_SHOWNORMAL);

	//main menu
	menubackground = CreateImage(0, 0, { 0,0,400,240 }, OTHER, 0, true);//main screen
	{
		menubackground->itype = MENUBACKGROUND;
	}
	CreateImage(105, 35, { 400, 65, 214, 61 }, MAINMENU, 0, true);//super mario world
	CreateButton(185, 120, { 400, 0, 30, 7 }, { 462, 0, 30, 7 }, { 524, 0, 30, 7 }, PLAY, MAINMENU, (j1Module*)App->gui, true);//play
	CreateButton(169, 135, { 400, 8, 60, 7 }, { 462, 8, 60, 7 }, { 524, 8, 60, 7 }, CONTINUE, MAINMENU, (j1Module*)App->scene, true);//continue
	CreateButton(169, 150, { 400, 16, 60, 7 }, { 462, 16, 60, 7 }, { 524, 16, 60, 7 }, SETTINGS, MAINMENU, (j1Module*)App->gui, true);//settings
	CreateButton(173, 165, { 400, 24, 52, 7 }, { 462, 24, 52, 7 }, { 524, 24, 52, 7 }, CREDITS, MAINMENU, (j1Module*)App->gui, true);//credits
	CreateButton(186, 180, { 400, 32, 28, 7 }, { 462, 32, 28, 7 }, { 524, 32, 28, 7 }, EXIT, MAINMENU, (j1Module*)App->scene, true);//exit

	//settings menu
	image = CreateImage(90, 60, { 560, 147, 38, 32 }, SETTINGSMENU, 3, true);//musicsound
	{
		image->status.PushBack({ 400, 147, 38, 32 });
		image->status.PushBack({ 440, 147, 38, 32 });
		image->status.PushBack({ 480, 147, 38, 32 });
		image->status.PushBack({ 520, 147, 38, 32 });
		image->status.PushBack({ 560, 147, 38, 32 });
	}
	GuiButton* button = CreateButton(137, 70, { 400, 180, 16, 16 }, { 417, 180, 16, 16 }, { 417, 180, 16, 16 }, MUSICUP, SETTINGSMENU, (j1Module*)App->audio, true);//musicup
	button->imgcallback = image;
	button = CreateButton(65, 70, { 434, 180, 16, 16 }, { 451, 180, 16, 16 }, { 451, 180, 16, 16 }, MUSICDOWN, SETTINGSMENU, (j1Module*)App->audio, true);//musicdown
	button->imgcallback = image;
	image = CreateImage(90, 144, { 560, 147, 38, 32 }, SETTINGSMENU, 4, true);//fxsound
	{
		image->status.PushBack({ 400, 147, 38, 32 });
		image->status.PushBack({ 440, 147, 38, 32 });
		image->status.PushBack({ 480, 147, 38, 32 });
		image->status.PushBack({ 520, 147, 38, 32 });
		image->status.PushBack({ 560, 147, 38, 32 });
	}
	button = CreateButton(137, 154, { 400, 180, 16, 16 }, { 417, 180, 16, 16 }, { 417, 180, 16, 16 }, FXUP, SETTINGSMENU, (j1Module*)App->audio, true);//fxup
	button->imgcallback = image;
	button = CreateButton(65, 154, { 434, 180, 16, 16 }, { 451, 180, 16, 16 }, { 451, 180, 16, 16 }, FXDOWN, SETTINGSMENU, (j1Module*)App->audio, true);//fxdown
	button->imgcallback = image;
	CreateButton(288, 32, { 400, 127, 44, 19 }, { 444, 127, 44, 19 }, { 444, 127, 44, 19 }, BACK, SETTINGSMENU, (j1Module*)App->gui, true);//settingsback
	CreateText(60, 36, "MUSIC VOLUME", { 50, 50, 255, 255 }, App->fonts->default, SETTINGSMENU, true);
	CreateText(60, 120, "SOUND FX VOLUME", { 50, 50, 255, 255 }, App->fonts->default, SETTINGSMENU, true);

	//credits menu
	CreateButton(288, 32, { 400, 127, 44, 19 }, { 444, 127, 44, 19 }, { 444, 127, 44, 19 }, BACK, CREDITSMENU, (j1Module*)App->gui, true);//credditsback
	CreateText(60, 40, "LOOK AT THESE CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU, true);
	CreateText(60, 55, "WOW SUCH CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU, true);
	CreateText(60, 70, "AMAZING CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU, true);
	CreateText(60, 85, "UNBELIEVEABLE CREDITS", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU, true);
	CreateText(60, 100, "even  with  lowercase  wow", { 50, 50, 255, 255 }, App->fonts->default, CREDITSMENU, true);

	CreateSlider(60, 60, { 400, 247, 12, 6 }, { 400, 253, 12, 50 }, MUSIC, MAINMENU, (j1Module*)App->audio, true);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		if (App->entitymodule->active == true && menubackground->active == false)
		{
			App->audio->PlayFx(6);

			App->entitymodule->active = false;
			App->pathfinding->active = false;
			App->collision->active = false;

			p2List_item<GuiElement*>* item = elements.start;
			while (item != nullptr)
			{
				if (item->data->mtype == PAUSEMENU)
				{
					item->data->active = true;
				}
				item = item->next;
			}
		}
		else if(App->entitymodule->active == false && menubackground->active == false)
		{
			App->audio->PlayFx(6);

			App->entitymodule->active = true;
			App->pathfinding->active = true;
			App->collision->active = true;

			p2List_item<GuiElement*>* item = elements.start;
			while (item != nullptr)
			{
				if (item->data->mtype == PAUSEMENU)
				{
					item->data->active = false;
				}
				item = item->next;
			}
		}
	}

	p2List_item<GuiElement*>* item = elements.start;
	while (item != nullptr)
	{
		if (item->data->active == true && MouseOnRect({ item->data->position.x, item->data->position.y, item->data->rect.w, item->data->rect.h }) == true)
		{
			if (item->data->etype == BUTTON && item->data->mouseover == false)
			{
				App->audio->PlayFx(7);
			}
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
		if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)
		{
			if (item->data->etype == SLIDER)
				item->data->OnDrag();
		}
		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			if (item->data->etype == SLIDER)
				item->data->OnRelease();
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
		if (item->data->etype == IMAGE)
		{
			GuiImage* image = (GuiImage*)item->data;
			if (image->status.last_frame > 0)
			{
				if (item->data->follows_camera == true)
				{
					item->data->PositionUpdate();
				}
				image->DrawStatus();
			}
			else
			{
				item->data->PositionUpdate();
				item->data->Draw();
			}
		}
		else if (item->data->etype != IMAGE)
		{
			if (item->data->follows_camera == true)
			{
				item->data->PositionUpdate();
			}
			item->data->Draw();
		}
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

GuiImage* j1Gui::CreateImage(int x, int y, SDL_Rect rect, menu_type mtype, uint index, bool follows_camera)
{
	iPoint position = { x,y };
	GuiImage* item = new GuiImage(position, rect, mtype, index, follows_camera);

	elements.add(item);

	return item;
}

GuiButton* j1Gui::CreateButton(int x, int y, SDL_Rect rect, SDL_Rect mover, SDL_Rect pressed, button_type btype, menu_type mtype, j1Module* callback, bool follows_camera)
{
	iPoint position = { x,y };
	GuiButton* item = new GuiButton(position, rect, mover, pressed, btype, mtype, callback, follows_camera);

	elements.add(item);

	return item;
}

GuiElement* j1Gui::CreateText(int x, int y, char* string, SDL_Color color, _TTF_Font* font, menu_type mtype, bool follows_camera)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiText(position, string, color, font, mtype, follows_camera);

	elements.add(item);

	return item;
}

GuiElement* j1Gui::CreateNumber(int x, int y, uint* number, SDL_Color color, _TTF_Font* font, menu_type mtype, bool follows_camera)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiNumber(position, number, color, font, mtype, follows_camera);

	elements.add(item);

	return item;
}

GuiElement* j1Gui::CreateSlider(int x, int y, SDL_Rect rect, SDL_Rect bar_rect, slider_type stype, menu_type mtype, j1Module* callback, bool follows_camera)
{
	iPoint position = { x,y };
	GuiElement* item = new GuiSlider(position, rect, bar_rect, stype, mtype, callback, follows_camera);

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
	{
		return true;
	}
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

		App->pathfinding->Start();
		App->collision->Start();
		App->entitymodule->Start();

		App->render->camera.x = 0;

		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (item->data->mtype != INGAMEMENU)
			{
				item->data->active = false;
			}
			else if (item->data->mtype == INGAMEMENU)
			{
				item->data->active = true;
			}
			item = item->next;
		}

		App->audio->PlayMusic("audio/main_music.ogg");

		break;
	}

	case RESUME:
	{
		App->audio->PlayFx(6);

		App->pathfinding->active = true;
		App->collision->active = true;
		App->entitymodule->active = true;

		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (item->data->mtype != INGAMEMENU)
			{
				item->data->active = false;
			}
			else if (item->data->mtype == INGAMEMENU)
			{
				item->data->active = true;
			}
			item = item->next;
		}

		break;
	}
		
	case SETTINGS:
	{
		bool pause = false;
		GuiImage* pausebackground = new GuiImage();
		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (item->data->etype == IMAGE)
			{
				GuiImage* image = (GuiImage*)item->data;
				if (image->itype == PAUSEBACKGROUND)
				{
					pausebackground = image;
					if (image->active == true)
					{
						pause = true;
					}
				}
			}

			if (item->data->mtype != SETTINGSMENU && item->data->mtype != OTHER)
			{
				item->data->active = false;
			}
			else if (item->data->mtype == SETTINGSMENU || item->data->mtype == OTHER)
			{
				item->data->active = true;
				if (pause == true)
				{
					pausebackground->active = true;
				}
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
		case SETTINGSMENU:
		{
			bool pause = false;
			GuiImage* menubackground = new GuiImage();
			p2List_item<GuiElement*>* item = elements.start;
			while (item != NULL)
			{
				if (item->data->etype == IMAGE)
				{
					GuiImage* image = (GuiImage*)item->data;
					if (image->itype == PAUSEBACKGROUND)
					{
						if (image->active == true)
						{
							pause = true;
						}
					}
					else if (image->itype == MENUBACKGROUND)
					{
						menubackground = image;
					}
				}

				if (pause == true)
				{
					if (item->data->mtype == PAUSEMENU || item->data->mtype == INGAMEMENU)
					{
						item->data->active = true;
					}
					else if (item->data->mtype == SETTINGSMENU)
					{
						item->data->active = false;
					}
					menubackground->active = false;
				}
				else if (pause == false)
				{
					if (item->data->mtype == MAINMENU || item->data->mtype == OTHER)
					{
						item->data->active = true;
					}
					else if (item->data->mtype == SETTINGSMENU)
					{
						item->data->active = false;
					}
				}
				item = item->next;
			}
			break;
		}
	}

		break;
	}

	case EXIT:
	{
		p2List_item<GuiElement*>* item = elements.start;
		while (item != NULL)
		{
			if (item->data->mtype == MAINMENU || item->data->mtype == OTHER)
			{
				item->data->active = true;
			}
			else
			{
				item->data->active = false;
			}
			item = item->next;
		}
		App->audio->PlayMusic("audio/title_theme.ogg");
		break;
	}
	}
	return true;
}

// class Gui ---------------------------------------------------

