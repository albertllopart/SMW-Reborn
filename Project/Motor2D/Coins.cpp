#include "j1App.h"
#include "Coins.h"
#include "SDL_image/include/SDL_image.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1EntityModule.h"

Coins::Coins() : Entity()
{
	name.create("Coins");

	idle.PushBack({ 400,40,12,16});
	idle.PushBack({ 434,40,9,16 });
	idle.PushBack({ 443,40,7,16 });
	idle.PushBack({ 450,40,9,16 });
	
}

// Destructor
Coins::~Coins()
{}

// Called before render is available
bool Coins::Awake()
{
	collision = App->collision->AddCollider({ (int)position.x, (int)position.y, 12, 16 }, COLLIDER_COIN, this);
	return true;
}

bool Coins::Start()
{
	graphic = App->tex->Load("gui/atlas.png");
	current_animation = &idle;
	//collision = App->collision->AddCollider({ (int)position.x, (int)position.y, 12, 16 }, COLLIDER_COIN, this);
	return true;
}

bool Coins::PreUpdate()
{
	return true;
}

bool Coins::PostUpdate()
{
	
	return true;
}
bool Coins::Update(float dt)
{
	Draw();
	return true;
}

void Coins::Draw()
{
	switch (state)
	{
	case IDLE:
		current_animation = &idle;
		break;
	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphic, position.x, position.y, &r);
}
bool Coins::Load(pugi::xml_node &)
{
	return true;
}

bool Coins::Save(pugi::xml_node &) const
{
	return true;
}
// Called before quitting
bool Coins::CleanUp()
{
	
	return true;
}

// Play a music file
