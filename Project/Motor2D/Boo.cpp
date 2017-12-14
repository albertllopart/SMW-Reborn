#include "Boo.h"
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
#include "Brofiler\Brofiler.h"

Boo::Boo() : Entity()
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
	position.create(144, 50);
	collision = App->collision->AddCollider({ (int)position.x, (int)position.y, BOO_SIZE, BOO_SIZE }, COLLIDER_BOO, this);

	position.create(188, 96);
	collision = App->collision->AddCollider({ (int)position.x, (int)position.y, BOO_SIZE, BOO_SIZE }, COLLIDER_BOO, this);
	return true;
}

bool Boo::Start()
{
	graphic = App->tex->Load("textures/Boo.png");
	current_animation = &idle;
	state = IDLE_LEFT;
	direction = R;

	//pathfinding
	is_path_done = true;
	path = 0;
	last_path = 0;
	path_size = 0;
	path_stopped = false;
	pathfinding = false;
	find_path = true;
	create_path = true;

	return true;
}

bool Boo::PreUpdate()
{
	return true;
}

bool Boo::Update(float dt)
{
	if (boo_chase)
	{
		Move();

		if (pathfinding)
		{
			// go to
			if (!Find_a_Path() && find_path)
			{
				find_path = false;
			}
			else
			{
				//in case the enemy reaches the final of the path
				pathfinding = false;
				is_path_done = true;
			}

		}
	}

	Draw();
	if (collision != NULL)
	{
		collision->SetPos(position.x, position.y);
		OnCollision(collision, App->entitymodule->player->collision);
	}

	pathfind_timer += dt;
	return true;
}

bool Boo::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
	{
		boo_chase = !boo_chase;
	}

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


	case WALK_LEFT:
		current_animation = &chase_left;
		break;

	case WALK_RIGHT:
		current_animation = &chase_right;
		break;


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
	return direction;
}

fPoint Boo::Getposition() const
{
	return position;
}

bool Boo::CleanUp()
{
	return true;
}

void Boo::Move()
{
	Pathfinding();
}

bool Boo::CreatePath(fPoint destination)
{
	BROFILER_CATEGORY("Boo CreatePath", Profiler::Color::Orange)

	bool ret = false;

	//we call the pathfinding module and create a path, the bool we send is to know if the enmy can go in diagonal lines
	if (App->pathfinding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(destination.x, destination.y), true)> -1)
	{
		//we save the last path in a variable
		last_pathfinding = App->pathfinding->GetLastPath();
		path_size = last_pathfinding->Count();
		path = 1;

		//we clear the variable before pushing back our points
		mlast_pathfinding.Clear();

		for (int i = 0; i < path_size; ++i) 
		{
			mlast_pathfinding.PushBack(*last_pathfinding->At(i));
			ret = true;
		}
	}

	return ret;
}

void Boo::Pathfinding()
{
	BROFILER_CATEGORY("Boo Pathfinding", Profiler::Color::Orange)

	if (is_path_done) 
	{
		is_path_done = false;
		path = 0;
		last_path = 0;
		path_size = 0;
		path_stopped = false;
		pathfinding = false;
		find_path = true;
		last_path = path;
		create_path = true;
		
	}

	//create a path
	if (pathfind_timer >= 0.2f)
	{
		if (create_path)
		{
			fPoint destination;
			destination.x = App->entitymodule->player->position.x;
			destination.y = App->entitymodule->player->position.y;

			//if the path creates->
			if (CreatePath(destination))
			{
				pathfinding = true;
				create_path = false;
			}
		}
		pathfind_timer = 0;
	}
}

bool Boo::Find_a_Path()
{
	BROFILER_CATEGORY("Boo Find_a_Path", Profiler::Color::Orange)

	bool ret = true;

	//when boo needs more than one step to reach player, if he doesn't then player probably dead af
	if (path_size > 1) 
	{
		iPoint go_to = App->map->MapToWorld(mlast_pathfinding[path].x, mlast_pathfinding[path].y);
		//once we know where boo gotta go we send it to the function that moves him
		Movement(go_to);

		if (GetPositionINT() == go_to)
		{
			if (path < path_size - 1)
				path++;
		}

		if (GetPositionINT() == App->map->MapToWorld(mlast_pathfinding[path_size - 1].x, mlast_pathfinding[path_size - 1].y))
			ret = false;
	}
	else
		ret = false;

	return ret;
}

void Boo::Movement(iPoint go_to)
{
	if (position.x < go_to.x)		position.x += 5.0f, state = WALK_LEFT;
	else if (position.x > go_to.x)	position.x -= 5.0f, state = WALK_RIGHT;
	if (position.y < go_to.y)		position.y +=5.0f;
	else if (position.y > go_to.y)	position.y -= 5.0f;
}

iPoint Boo::GetPositionINT() const
{
	return iPoint(position.x, position.y);
}