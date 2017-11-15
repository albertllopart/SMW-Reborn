#pragma once
#ifndef __j1Entity_H_
#define __j1Entity_H_

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Entity.h"
#include "Chuck.h"
#include "Boo.h"

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

	void				CreateBoo(iPoint position);
	void				CreateChuck(iPoint position);

	void				DeleteBoo(Entity* boo);
	void				DeleteChuck(Entity* chuck);

	bool				Load(pugi::xml_node&);
	bool				Save(pugi::xml_node&)const;

public:

	p2List<Entity*>		entities;
};

#endif