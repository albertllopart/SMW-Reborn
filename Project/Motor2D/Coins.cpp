#include "j1App.h"
#include "Coins.h"
#include "SDL_image/include/SDL_image.h"
#include "j1Textures.h"
#include "j1Render.h"


Coins::Coins() : Entity()
{
	name.create("Coins");

	idle.PushBack({440,41,46,44});

}

// Destructor
Coins::~Coins()
{}

// Called before render is available
bool Coins::Awake()
{

	return true;
}

bool Coins::Start()
{
	graphic = App->tex->Load("gui/atlas.png");
	position.create(184, 110);
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
