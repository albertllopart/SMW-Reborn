#include "Chuck.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1EnemyModule.h"
#include "j1Map.h"

Chuck::Chuck() : Enemy()
{
	name.create("Chuck");

	// create here all animations
}

Chuck::~Chuck()
{}

bool Chuck::Awake()
{
	position.create(50, 197);
	return true;
}

bool Chuck::Start()
{
	graphic = App->tex->Load("textures/Chuck.png");
	current_animation = &idle_left;
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

