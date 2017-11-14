#include "j1EnemyModule.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Defs.h"

j1EnemyModule::j1EnemyModule() : j1Module()
{
	name = "Enemyodule";
}

j1EnemyModule::~j1EnemyModule(){}

bool j1EnemyModule::Awake(pugi::xml_node& conf)
{
	return true;
}

bool j1EnemyModule::Start()
{
	return true;
}

bool j1EnemyModule::PreUpdate()
{
	return true;
}

bool j1EnemyModule::Update(float dt)
{
	return true;
}

bool j1EnemyModule::PostUpdate()
{
	return true;
}

void j1EnemyModule::CreateBoo(iPoint position)
{

}

void j1EnemyModule::CreateChuck(iPoint position)
{
	
}

void j1EnemyModule::DeleteBoo()
{

}

void j1EnemyModule::DeleteChuck()
{
	
}

bool j1EnemyModule::Load(pugi::xml_node& node)
{
	return true;
}

bool j1EnemyModule::Save(pugi::xml_node& node) const
{
	return true;
}
