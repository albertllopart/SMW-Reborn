#include "Chuck.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1EntityModule.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include <math.h>

Chuck::Chuck() : Entity()
{
	name.create("Chuck");

	// create here all animations
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 25, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 50, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 50, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 50, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 50, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 50, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 25, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 100, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 75, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 75, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 75, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 75, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 75, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 100, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });
	idle.PushBack({ 0, 0, 24, CHUCK_HIGHT });

	walk_left.PushBack({ 264, 0, CHUCK_WIDTH, CHUCK_HIGHT });
	walk_left.PushBack({ 237, 0, CHUCK_WIDTH, CHUCK_HIGHT });

	walk_right.PushBack({ 183, 0, CHUCK_WIDTH, CHUCK_HIGHT });
	walk_right.PushBack({ 210, 0, CHUCK_WIDTH, CHUCK_HIGHT });

	jump_left.PushBack({ 154, 0, 28, CHUCK_HIGHT });

	jump_right.PushBack({ 125, 0, 28, CHUCK_HIGHT });
}

Chuck::~Chuck()
{}

bool Chuck::Awake()
{
	position.create(150, 150);
	return true;
}

bool Chuck::Start()
{
	graphic = App->tex->Load("textures/Chuck.png");
	current_animation = &idle;
	collision = App->collision->AddCollider({ (int)position.x, (int)position.y, CHUCK_WIDTH, CHUCK_HIGHT }, COLLIDER_CHUCK, this);
	state = IDLE_LEFT;
	direction = R;
	return true;
}

bool Chuck::PreUpdate()
{
	return true;
}

bool Chuck::Update(float dt)
{
	if ((position.x - CHASE_RANGE < App->entitymodule->player->position.x && position.x > App->entitymodule->player->position.x) || (position.x + CHASE_RANGE > App->entitymodule->player->position.x && position.x < App->entitymodule->player->position.x))
	{
		state = IDLE_LEFT;
		if (App->map->IsWalkable(this) == true && App->map->IsFallable(this) == false)
		{
			Move(dt);
		}
		if (position.x < App->entitymodule->player->position.x)
			direction = R;
		else
			direction = L;
	}
		
	else
	{
		state = IDLE_LEFT;
	}
	collision->SetPos(position.x, position.y);
	Draw();

	return true;
}

bool Chuck::PostUpdate()
{	
	return true;
}

void Chuck::Draw()
{
	switch (state)
	{
	case IDLE_RIGHT:
		current_animation = &idle;
		break;

	case IDLE_LEFT:
		current_animation = &idle;
		break;

	case SHORT_HOP_LEFT:
		current_animation = &jump_left;
		break;

	case SHORT_HOP_RIGHT:
		current_animation = &jump_right;
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

bool Chuck::Load(pugi::xml_node &)
{
	return true;
}

bool Chuck::Save(pugi::xml_node &) const
{
	return true;
}

int Chuck::GetDirection() const
{
	return 0;
}

fPoint Chuck::Getposition() const
{
	return position;
}

bool Chuck::CleanUp()
{
	return true;
}

fPoint Chuck::GetPositionINT() const
{
	return fPoint(position.x, position.y);
}


void Chuck::Move(float dt)
{
	walking_sound_timer += dt;
	//count += dt;
	//float count_rounded = roundf(count*10) / 10; //rounded to 1 decimal
	if (1)
	{
		if (position.x > App->entitymodule->player->position.x)
		{
			position.x -= 50.0f * dt;
			state = WALK_LEFT;
			direction = L;

			if (walking_sound_timer >= 0.15f)
			{
				walking_sound_timer = 0;
				App->audio->PlayFx(4);
			}
		}

		if (position.x < App->entitymodule->player->position.x)
		{
			position.x += 50.0f * dt;
			state = WALK_RIGHT;
			direction = R;

			if (walking_sound_timer >= 0.15f)
			{
				walking_sound_timer = 0;
				App->audio->PlayFx(4);
			}
		}
	}
	/*if (count_rounded > 0.2f)
		count = 0;*/
}