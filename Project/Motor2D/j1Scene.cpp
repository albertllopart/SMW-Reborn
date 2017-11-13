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

#include "Brofiler\Brofiler.h"

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

	App->map->Load("level_1.tmx");
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

	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 1;

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
	if (App->player->level_complete == true)
	{
		App->player->level_complete = false;
		App->map->WantToChange();
	}

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
	}

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

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
