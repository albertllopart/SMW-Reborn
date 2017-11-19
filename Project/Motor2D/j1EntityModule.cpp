#include "j1EntityModule.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Defs.h"
#include "Entity.h"

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
	j1Player* player_a = new j1Player();
	player_a->Awake();
	player_a->Start();
	player_a->position = position;
	entities.add(player_a);
	player = player_a;
}

void j1EntityModule::DeleteBoo(Entity* boo)
{
	if (boo != nullptr)
	{
		int find = entities.find(boo);
		int current_position = 0;
		p2List_item<Entity*>* item = entities.start;
		
		while (item != NULL)
		{
			if (current_position == find)
			{
				entities[current_position]->collision->to_delete = true;
				
				entities.del(item);
				
				return;
			}
			item = item->next;
			current_position++;
		}
	}
}

void j1EntityModule::DeleteChuck(Entity* chuck)
{
	if (chuck != nullptr)
	{
		int find = entities.find(chuck);
		int current_position = 0;
		p2List_item<Entity*>* item = entities.start;
		while (item != NULL)
		{
			if (current_position == find)
			{
				entities.del(item);
				return;
			}
			item = item->next;
			current_position++;
		}
	}
}

void j1EntityModule::DeletePlayer(Entity* player)
{

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
		else if (entities[i]->name == "player")
		{
			pugi::xml_node root = node.append_child("player_position");
			root.append_attribute("x") = entities[i]->position.x;
			root.append_attribute("y") = entities[i]->position.y;

		}
	}


	//pugi::xml_node root = node.append_child("position");
	//root.append_attribute("x") = position.x;
	//root.append_attribute("y") = position.y;

	return true;
}

bool j1EntityModule::Load(pugi::xml_node& node)
{
	//std::string name = new std::string(root.name());
	pugi::xml_node root = node.first_child();
	for (int i = 0; i < entities.count(); i++)
	{
		//delete boo
		if (entities[i]->name == "Boo")
		{
			DeleteBoo(entities[i]);
			i--;
		}
		//delete chuck
		else if (entities[i]->name == "Chuck")
		{
			DeleteChuck(entities[i]);
			i--;
		}
			/*if (entities[i]->name == "player")
			DeletePlayer(entities[i]);*/
	}

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
		else if (strncmp(root.name(), "player_position", 16) == 0)
		{
			
			App->entitymodule->player->position.x = root.attribute("x").as_int();
			App->entitymodule->player->position.y = root.attribute("y").as_int();

		}
		root = root.next_sibling();
	}
	
	//std::string name = new std::string();
	//char name [] = root.name();

	//strcpy_s(name,,root.name());
	//char* name = "boo_position";
	/*
	for (int i = 0; i < entities.count(); i++)
	{
		if (entities[i]->name == "Boo")
		{
			root = node;

			for (int j = 0; j < cont; j++)
			{
				if (j >= 1)
					root = root.child("boo_position").next_sibling();

			}
			if (cont2 == 0)
			{
				entities[i]->position.x = root.child("boo_position").attribute("x").as_int();
				entities[i]->position.y = root.child("boo_position").attribute("y").as_int();
			}
			else 
			{
				entities[i]->position.x = root.attribute("x").as_int();
				entities[i]->position.y = root.attribute("y").as_int();
			}
			
			cont2++;
		}
		else if (entities[i]->name == "Chuck")
		{
			root = node;
			for (int j = 0; j < cont; j++)
			{
				if (j >= 1)
				root = root.child("chuck_position").next_sibling();
			}
			entities[i]->position.x = root.child("chuck_position").attribute("x").as_int();
			entities[i]->position.y = root.child("chuck_position").attribute("y").as_int();

		}
		 if (entities[i]->name == "player")
		{
			root = node;
			for (int j = 0; j < cont ; j++)
			{
				if (j >= 1)
				root = root.child("player_position").next_sibling();
			}
			entities[i]->position.x = root.child("player_position").attribute("x").as_int();
			entities[i]->position.y = root.child("player_position").attribute("y").as_int();

		}
		cont++;
	}*/
	//pugi::xml_node root = node.child("position");
	//position.x = root.attribute("x").as_int();
	//position.y = root.attribute("y").as_int();

	return true;
}
