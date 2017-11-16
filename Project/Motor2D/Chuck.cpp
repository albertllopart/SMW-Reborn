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
	return true;
}

bool Chuck::Start()
{
	graphic = App->tex->Load("textures/Chuck.png");
	current_animation = &idle;
	state = IDLE_LEFT;

	//Move
	prev_dt = 0;
	fake_dt = 0;

	return true;
}

bool Chuck::PreUpdate()
{
	return true;
}

bool Chuck::Update(float dt)
{
	if(App->player->position.x > 60 && App->player->position.x < 150)
		Move(dt);
	UpdatePrevDt(dt);
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

iPoint Chuck::Getposition() const
{
	return position;
}

bool Chuck::CleanUp()
{
	return true;
}

iPoint Chuck::GetPositionINT() const
{
	return iPoint(position.x, position.y);
}

void Chuck::UpdatePrevDt(float dt)
{
	prev_dt = dt;
}

void Chuck::Move(float dt)
{
	fake_dt = dt - prev_dt;
	count += fake_dt;
	float count_rounded = roundf(count*10) / 10; //rounded to 1 decimal
	if (count_rounded > 0.199f && count_rounded < 0.201 || count_rounded > 0.399f && count_rounded < 0.401 || count_rounded > 0.599f && count_rounded < 0.601 || count_rounded > 0.799f && count_rounded < 0.801 || count_rounded > 0.999f && count_rounded < 1.001)
	{
		if (enemy1.position.x > App->player->position.x)
			enemy1.position.x -= 1.0f;
		if (enemy1.position.x < App->player->position.y)
			enemy1.position.y += 1.0f;
	}
	if (count_rounded == 1)
		count = 0;
}