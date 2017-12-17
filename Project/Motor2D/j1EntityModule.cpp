#include "j1EntityModule.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Defs.h"
#include "Entity.h"
#include "Coins.h"

j1EntityModule::j1EntityModule() : j1Module()
{
	name = "Entitymodule";
}

j1EntityModule::~j1EntityModule(){}

bool j1EntityModule::Awake(pugi::xml_node& conf)
{
	return true;
}

bool j1EntityModule::Start()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->Start();
		item = item->next;
	}
	return true;
}

bool j1EntityModule::PreUpdate()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->PreUpdate();
		item = item->next;
	}
	return true;
}

bool j1EntityModule::Update(float dt)
{
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->Update(dt);
		item = item->next;
	}
	return true;
}

bool j1EntityModule::PostUpdate()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	return true;
}

void j1EntityModule::CreateBoo(fPoint position)
{
	Boo* boo = new Boo();
	boo->Awake();
	boo->Start();
	boo->position = position;
	entities.add(boo);
}

void j1EntityModule::CreateChuck(fPoint position)
{
	Chuck* chuck = new Chuck();
	chuck->Awake();
	chuck->Start();
	chuck->position = position;
	entities.add(chuck);
	
	
}

void j1EntityModule::CreatePlayer(fPoint position)
{
	if (player != NULL)
	{
		DeleteEntity(player);
	}
	player = new j1Player();
	player->Awake();
	player->Start();
	player->position = position;
	entities.add(player);
	 
}

void j1EntityModule::CreateCoins(fPoint position)
{
	Coins* coins = new Coins();
	coins->position = position;
	coins->Awake();
	coins->Start();
	entities.add(coins);
	
}

void j1EntityModule::DeleteEntity(Entity* entity)
{
	if (entity != nullptr)
	{
	
		p2List_item<Entity*>* item = entities.start;
		while (item != NULL)
		{
			if (item->data == entity)
			{
				if (entity->name == "Chuck")
 					entity->collision_head->to_delete = true;
				entity->collision->to_delete = true;
				RELEASE(entity);
				entities.del(item);
				return;
			}
			item = item->next;
		}
	}
}


void j1EntityModule::DeleteEntities()
{
	for (int i = 0; i < entities.count(); i++)
	{
		App->entitymodule->DeleteEntity(entities[i]);
		i--;
	}
}




bool j1EntityModule::Save(pugi::xml_node& node) const
{
	for (int i = 0; i < entities.count(); i++)
	{
		if (entities[i]->name == "Boo")
		{
		
			pugi::xml_node root = node.append_child("boo_position");
			root.append_attribute("x") = entities[i]->position.x;
			root.append_attribute("y") = entities[i]->position.y;

		}
		else if (entities[i]->name == "Chuck")
		{
		
			pugi::xml_node root = node.append_child("chuck_position");
			root.append_attribute("x") = entities[i]->position.x;
			root.append_attribute("y") = entities[i]->position.y;

		}
		else if (entities[i]->name == "Player")
		{
		
			pugi::xml_node root = node.append_child("player");
			pugi::xml_node player_pos = root.append_child("player_position");
			 
			player_pos.append_attribute("x") = entities[i]->position.x;
			player_pos.append_attribute("y") = entities[i]->position.y;

			root.append_child("coins").append_attribute("value") = player->player_coins;
			root.append_child("score").append_attribute("value") = player->player_score;
			root.append_child("lives").append_attribute("value") = player->player_lives;
			root.append_child("time").append_attribute("value") = player->player_hours;

		}
		else if (entities[i]->name == "Coins")
		{
		
			pugi::xml_node root = node.append_child("coin_position");
			root.append_attribute("x") = entities[i]->position.x;
			root.append_attribute("y") = entities[i]->position.y;

		}
	}

	return true;
}

bool j1EntityModule::Load(pugi::xml_node& node)
{
	pugi::xml_node root = node.first_child();

	while (root != NULL)
	{
		
		if (strncmp(root.name(),"boo_position",13)==0)
		{
			fPoint point;
			point.create(root.attribute("x").as_int(), root.attribute("y").as_int());
			CreateBoo(point);

		}
		else if (strncmp(root.name(), "chuck_position", 15) == 0)
		{
			fPoint point;
			point.create(root.attribute("x").as_int(), root.attribute("y").as_int());
			CreateChuck(point);

		}
		else if (strncmp(root.name(), "coin_position", 14) == 0)
		{
			fPoint point;
			point.create(root.attribute("x").as_int(), root.attribute("y").as_int());
			CreateCoins(point);

		}
		else if (strncmp(root.name(), "player", 7) == 0)
		{
			pugi::xml_node player_pos = root.child("player_position");
			player->position.x = player_pos.attribute("x").as_int();
			player->position.y = player_pos.attribute("y").as_int();

			player->player_coins = root.child("coins").attribute("value").as_int();
			player->player_score = root.child("score").attribute("value").as_int();
			player->player_lives = root.child("lives").attribute("value").as_int();
			player->player_hours = root.child("time").attribute("value").as_int();
		}
		root = root.next_sibling();
	}

	return true;
}
