#include "j1EnemyModule.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Defs.h"
#include "EnemyTemplate.h"

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
	p2List_item<Enemy*>* item = enemies.start;
	while (item != NULL)
	{
		item->data->Start();
		item = item->next;
	}
	return true;
}

bool j1EnemyModule::PreUpdate()
{
	p2List_item<Enemy*>* item = enemies.start;
	while (item != NULL)
	{
		item->data->PreUpdate();
		item = item->next;
	}
	return true;
}

bool j1EnemyModule::Update(float dt)
{
	p2List_item<Enemy*>* item = enemies.start;
	while (item != NULL)
	{
		item->data->Update(dt);
		item = item->next;
	}
	return true;
}

bool j1EnemyModule::PostUpdate()
{
	p2List_item<Enemy*>* item = enemies.start;
	while (item != NULL)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	return true;
}

void j1EnemyModule::CreateBoo(iPoint position)
{
	Boo* boo = new Boo();
	boo->Awake();
	boo->Start();
	boo->position = position;
	enemies.add(boo);
}

void j1EnemyModule::CreateChuck(iPoint position)
{
	Chuck* chuck = new Chuck();
	chuck->Awake();
	chuck->Start();
	chuck->position = position;
	enemies.add(chuck);
}

void j1EnemyModule::DeleteBoo(Enemy* boo)
{

}

void j1EnemyModule::DeleteChuck(Enemy* chuck)
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
