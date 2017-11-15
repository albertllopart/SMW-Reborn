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
	return true;
}

bool Chuck::Start()
{
	graphic = App->tex->Load("textures/Chuck.png");
	current_animation = &idle;
	state = IDLE_LEFT;

	return true;
}

bool Chuck::PreUpdate()
{
	return true;
}

bool Chuck::Update(float dt)
{
	return true;
}

bool Chuck::PostUpdate()
{
	Draw();
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

iPoint Chuck::Getposition() const
{
	return position;
}

bool Chuck::CleanUp()
{
	return true;
}

void Chuck::Move(Chuck Entity)
{
	if (App->player->position.x > 60)
	{
		App->pathfinding->CreatePath(App->player->player_quadrant_1, Entity.position, flies);
	}
}
