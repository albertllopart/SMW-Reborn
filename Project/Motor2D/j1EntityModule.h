#pragma once
#ifndef __j1Entity_H_
#define __j1Entity_H_

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Entity.h"
#include "Chuck.h"
#include "Boo.h"
#include "j1Player.h"
#include "j1Collision.h"

class j1EntityModule : public j1Module
{
public:

	j1EntityModule();
	virtual ~j1EntityModule();

	//Called before render is available
	bool				Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool				Start();

	// Called before all Updates
	bool				PreUpdate();

	// Called each loop iteration
	bool				Update(float dt);

	// Called before all Updates
	bool				PostUpdate();

	void				CreateBoo(fPoint position);
	void				CreateChuck(fPoint position);
	void				CreatePlayer(fPoint position);
	void				CreateCoins(fPoint position);

	void				DeleteEntity(Entity* entity);
	void				DeleteEntities();
	bool				Load(pugi::xml_node&);
	bool				Save(pugi::xml_node&) const;

public:

	p2List<Entity*>		entities;
	bool				level_complete = false;
	j1Player*				player = nullptr;
	j1Collision*        col = nullptr;

};

#endif