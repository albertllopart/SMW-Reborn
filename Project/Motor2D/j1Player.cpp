#include "p2Defs.h"
#include "p2Log.h"
#include "j1Player.h"
#include "p2List.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1EntityModule.h"

#include "Brofiler\Brofiler.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

j1Player::j1Player() : Entity()
{
	name.create("player");

	//Animations
	
	idle_right.PushBack({ 0, 2, 15, 28 });
	idle_left.PushBack({ 140, 2, 15, 28 });

	walk_right.PushBack({ 40, 2, 16, 28 });
	walk_right.PushBack({ 20, 3, 16, 27 });
	walk_right.PushBack({ 0, 2, 15, 28 });

	walk_left.PushBack({ 99, 2, 16, 28 });
	walk_left.PushBack({ 119, 3, 16, 27 });
	walk_left.PushBack({ 140, 2, 15, 28 });

	short_hop_right.PushBack({ 60, 0, 16, 31 });
	short_hop_left.PushBack({ 79, 0, 16, 31 });
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	LOG("Loading Player");
	bool ret = true;
	collision = App->collision->AddCollider({ (int)position.x, (int)position.y, MARIO_WIDTH, MARIO_HIGHT - 3 }, COLLIDER_PLAYER, this);
	return ret;
}

bool j1Player::Start()
{
	LOG("starting player");
	bool ret = true;
	graphic = App->tex->Load("maps/Mario.png");

	position.x = 10;
	position.y = 197;

	

	//player quadrant position
	player_quadrant_1.x = position.x / TILE_WIDTH;
	player_quadrant_2.x = (position.x + MARIO_WIDTH) / TILE_WIDTH;

	player_quadrant_1.y = position.y / TILE_WIDTH;
	player_quadrant_2.y = (position.y + MARIO_HIGHT) / TILE_WIDTH;

	velocity.x = 2;
	velocity.y = 3;

	state = IDLE_RIGHT;
	direction = R;

	return ret;
}

bool j1Player::Update(float dt)
{
	BROFILER_CATEGORY("Player Update", Profiler::Color::Orange)

		if (dead_timer == 0 || dead_timer > 1.0f)
		{
			if (dead_timer != 0)
			{
				dead_timer = 0;
				dead = false;
				App->scene->LoadLvl(App->scene->current_lvl, true);
								
			}

			Input(dt);
			if (jump)
			{
				if (Jump())
				{
					position.y -= 150 * dt;
				}
			}
			else
			{
				if (Falling())
				{
					position.y += 150 * dt;
				}
			}

			if (jump == true)
			{
				if (direction == L)
					state = SHORT_HOP_LEFT;
				else if (direction == R)
					state = SHORT_HOP_RIGHT;
			}

			collision->SetPos(position.x, position.y);
		}

	if (dead)
	{
		dead_timer += dt;
		App->scene->LoadLvl(App->scene->current_lvl, true);
	}
	if (position.y > 300 || position.y < 0)
	{
		position.y = 167;
	}
	Draw();

	return true;
}

bool j1Player::PostUpdate()
{
	if (dead)
	{
		state = IDLE_RIGHT;
		//App->map->restart();
	}

	player_quadrant_1.x = position.x / TILE_WIDTH;
	player_quadrant_2.x = (position.x + MARIO_WIDTH) / TILE_WIDTH;

	player_quadrant_1.y = position.y / TILE_WIDTH;
	player_quadrant_2.y = (position.y + MARIO_HIGHT) / TILE_WIDTH;
	
	return true;
}

bool j1Player::CleanUp()
{
	LOG("Destroying player");
	bool ret = true;
	return ret;
}



void j1Player::Draw()
{
	switch (state)
	{
		case IDLE_RIGHT:
			current_animation = &idle_right;
			break;

		case IDLE_LEFT:
			current_animation = &idle_left;
			break;
	
		case SHORT_HOP_LEFT:
			current_animation = &short_hop_left;
			break;
	
		case SHORT_HOP_RIGHT:
			current_animation = &short_hop_right;
			break;
		
		case WALK_LEFT:
			current_animation = &walk_left;
			break;
		
		case WALK_RIGHT:
			current_animation = &walk_right;
			break;
	

	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphic, position.x, position.y, &r);
}

void j1Player::Input(float dt)
{
	BROFILER_CATEGORY("Player Input", Profiler::Color::Orange)

	//Right
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		direction = R;
		if (App->map->IsWalkable(this))
		{
			position.x += (SPEED_X * dt);
		}
		if (Falling() == false)
			state = WALK_RIGHT;
		
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		direction = R;
		if (App->map->IsWalkable(this))
		{
			position.x += (SPEED_X * dt);
		}
		state = IDLE_RIGHT;
	}


	//Left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		direction = L;
		if (App->map->IsWalkable(this))
		{
			position.x -= (SPEED_X * dt);
		}
		if (Falling() == false)
			state = WALK_LEFT;	
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		direction = L;
		if (App->map->IsWalkable(this))
		{
			position.x -= (SPEED_X * dt);
		}
		state = IDLE_LEFT;
	}

	//Jump
	if (!jump1_on)
	{
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			App->audio->PlayFx(1);
			jump = true;
			jump_height = position.y - 35;
			jump1_on = true;
		}
	}
	else if (!jump2_on)
	{
 		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			App->audio->PlayFx(2);
			jump = true;
			jump_height = position.y - 35;
			jump2_on = true;
		}
	}

	//change map
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->map->want_to_change_map = true;
		App->map->level_1 = true;
		App->map->level_2 = false;
		App->scene->LoadLvl(1, true);
	}

	//reset the lvl
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->scene->LoadLvl(App->scene->current_lvl, true);
	}

	//save
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		App->SaveGame();
	}

	//load
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		App->LoadGame();
	}
	//GodMode
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		GodMode();
	}
	// To lvl1
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->scene->LoadLvl(1, true);
	}
	// To lvl 2
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->scene->LoadLvl(2, true);
	}

}
bool j1Player::Save()const
{
	return true;
}

bool j1Player::Load()
{
	return true;
}

bool j1Player::GodMode()
{
	if (god_mode == false)
	{
		god_mode = true;
	}
		
	else if (god_mode == true)
	{
		god_mode = false;
	}
			
	
	return true;
}
bool j1Player::Jump()
 {
	bool ret;
	if (position.y > jump_height)
	{
		ret = true;
		
	}
	else
	{
		jump = false;
		ret = false;
		jump_height = 0;
		//todo something wrong with jump player starts jumping some times and stop when arrives on height 0;
		if (direction == L) state = IDLE_LEFT;
		else if (direction == R) state = IDLE_RIGHT;
	}
	return ret;
}



bool j1Player::Falling()
{
	BROFILER_CATEGORY("Player Falling", Profiler::Color::Orange)

	bool ret = false;
	p2List_item<MapLayer*>* iterator;
	p2List_item<MapLayer*>* fakeLayer = nullptr;

	for (iterator = App->map->data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logica")
		{
			fakeLayer = iterator;
		}
	}

	//uint nextGid = fakeLayer->data->GetGid(player_x,player_y);
	uint* nextGid1 = &fakeLayer->data->gid[1 + player_quadrant_1.x + player_quadrant_2.y * fakeLayer->data->width];
	uint* nextGid2 = &fakeLayer->data->gid[1 + player_quadrant_2.x + player_quadrant_2.y * fakeLayer->data->width];


		if (*nextGid1 == 0 && *nextGid2 == 0)
		{
			ret = true; 
			jump1_on = true;
		}
		else if(*nextGid1 == 19 || *nextGid2 == 19)
		{
			ret = false;
			jump2_on = false;
			jump1_on = false;
		}
		else if (*nextGid1 == 20)
		{
			App->audio->PlayFx(5);
			App->fadetoblack->FadeToBlack(App->entitymodule, App->entitymodule, 1.5f);
			dead = true;
			ret = false;
			jump2_on = false;
			jump1_on = false;
		}
		else
		{
			ret = true;
		}

		if (*nextGid1 == 28 || *nextGid2 == 28)
		{
			App->audio->PlayFx(3);
			level_complete = true;
			//App->fadetoblack->FadeToBlack(this, this, 2);
			App->scene->LoadLvl(2, true);
			jump = false;
		}

	return ret;
}