#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1EntityModule.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Gui.h"
#include "GuiButton.h"

#include "Brofiler\Brofiler.h"

#define CHUCK_ENEMIES  3

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	BROFILER_CATEGORY("Scene Start", Profiler::Color::Brown)

	//sound fx
	App->audio->LoadFx("audio/jump.wav"); //1
	App->audio->LoadFx("audio/double_jump.wav"); //2
	App->audio->LoadFx("audio/level_complete.wav"); //3
	App->audio->LoadFx("audio/chuck_walk.wav"); //4
	App->audio->LoadFx("audio/mario_hurt.wav"); //5
	App->audio->LoadFx("audio/pause.wav"); //6
	App->audio->LoadFx("audio/menu_over.wav");//7
	App->audio->LoadFx("audio/menu_click.wav");//8
	App->audio->LoadFx("audio/smw_coin.wav");//9
	LoadLvl(1, true);
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Scene Update", Profiler::Color::Brown)

	
	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 10;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 10;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 10;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 10;

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		if (title_2 == true)
		{
			title_2 = false;
		}
		else if (title_2 == false)
		{
			title_2 = true;
		}
	}

	//change map

	if (App->entitymodule->level_complete == true)
	{
		
		if (current_lvl == 1)
			LoadLvl(2, true);

		else if (current_lvl == 2)
			LoadLvl(1, true);

		App->entitymodule->level_complete = false;
		//App->map->WantToChange();
	}
/*
	if (App->map->want_to_change_map == true)
	{
		if (App->map->level_1 == true)
		{
			App->map->UnloadMap();
			App->map->Load("level_1.tmx");
			App->map->want_to_change_map = false;
		}
		else if (App->map->level_2 == true)
		{
			App->map->UnloadMap();
			App->map->Load("level_2.tmx");
			App->map->want_to_change_map = false;
		}
	}*/

	//App->render->Blit(img, 0, 0);
	App->map->Draw(App->GetDT());

	// TODO 7: Set the window title like
	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	mouse = App->map->WorldToMap(mouse.x, mouse.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Mouse Position:%d,%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count(),
		mouse.x, mouse.y);
		


	if (title_2 == true) App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(exit_from_gui == true)
		ret = false;
	if (want_to_load_lvl == true)
	{
		LoadLvl(lvl_to_change, want_to_start_scene);
	}
	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
bool j1Scene::Save(pugi::xml_node& node)const
{
	node.append_attribute("current_lvl") = current_lvl;
	return true;
}

bool j1Scene::Load(pugi::xml_node& node)
{
	LoadLvl(node.attribute("current_lvl").as_int(), false);
	return true;
}

void j1Scene::LoadLvl(int current, bool lvl_start)
{
	want_to_load_lvl = false;
	int player_lives = -1;
	int player_coins = -1;
	int player_score = -1;
	if (App->entitymodule->player != NULL)
	{
		player_lives = App->entitymodule->player->player_lives;
		player_coins = App->entitymodule->player->player_coins;
		player_score = App->entitymodule->player->player_score;
	}
		

	App->entitymodule->DeleteEntities();
	App->entitymodule->CreatePlayer(fPoint(10,197));

	if (player_lives != -1)
	{
		App->entitymodule->player->player_lives = player_lives;
		App->entitymodule->player->player_score = player_score;
		App->entitymodule->player->player_coins = player_coins;
	}
		

	Entity* player = App->entitymodule->player;
	player->dead = true;
	if (current == 1)
	{
		App->audio->PlayMusic("audio/main_music.ogg");
		App->map->UnloadMap();
		App->map->Load("level_1.tmx");		
	}
	else if (current == 2)
	{
		App->audio->PlayMusic("audio/main_music.ogg");
		App->map->UnloadMap();
		App->map->Load("level_2.tmx");
		
	}
	if (lvl_start == true)
	{

		App->render->camera.x = 0;
		App->render->camera.y = 0;
		App->map->LoadEntities();
	}
	player->collision->SetPos(player->position.x, player->position.y);
	player->jump = false;
	player->dead = false;
	player->PostUpdate();
	current_lvl = current;
	

}

void j1Scene::WantToChangeLoadLvl(int next_lvl, bool lvl_start)
{
	want_to_load_lvl = true;
	lvl_to_change = next_lvl;
	want_to_start_scene = lvl_start;
}

bool j1Scene::GuiTrigger(GuiElement* element)
{
	GuiButton* button = (GuiButton*)element;
	switch (button->btype)
	{
		
	case EXIT:
		exit_from_gui = true;
		break;
	}
	return true;
}