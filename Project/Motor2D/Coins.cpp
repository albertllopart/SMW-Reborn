#include "j1App.h"
#include "Coins.h"
#include "SDL_image/include/SDL_image.h"
#include "j1Textures.h"

Coins::Coins() : Entity()
{
	name.create("Coins");
	
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

	return true;
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
