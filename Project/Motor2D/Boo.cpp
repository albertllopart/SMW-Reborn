#include "Boo.h"
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

Boo::Boo() : Enemy()
{
	name.create("Boo");

	//animations
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 17, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 17, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 34, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 34, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
	idle.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });

	chase_left.PushBack({ 17, 0, BOO_SIZE, BOO_SIZE });

	chase_right.PushBack({ 34, 0, BOO_SIZE, BOO_SIZE });

	stop_left.PushBack({ 0, 0, BOO_SIZE, BOO_SIZE });

	stop_right.PushBack({ 51, 0, BOO_SIZE, BOO_SIZE });
}

Boo::~Boo()
{}

bool Boo::Awake()
{
	position.create(150, 100);
	return true;
}

bool Boo::Start()
{
	graphic = App->tex->Load("textures/Boo.png");
	current_animation = &idle;
	state = IDLE_LEFT;

	return true;
}

bool Boo::PreUpdate()
{
	return true;
}

bool Boo::Update(float dt)
{
	return true;
}

bool Boo::PostUpdate()
{
	Draw();
	return true;
}

void Boo::Draw()
{
	switch (state)
	{
	case IDLE_RIGHT:
		current_animation = &idle;
		break;

	case IDLE_LEFT:
		current_animation = &idle;
		break;

	/*case SHORT_HOP_LEFT:
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
		break;*/


	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphic, position.x, position.y, &r);
}

bool Boo::Load(pugi::xml_node &)
{
	return true;
}

bool Boo::Save(pugi::xml_node &) const
{
	return true;
}

int Boo::GetDirection() const
{
	return 0;
}

iPoint Boo::Getposition() const
{
	return position;
}

bool Boo::CleanUp()
{
	return true;
}