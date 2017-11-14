#pragma once
#ifndef __j1ENEMY_H_
#define __j1ENEMY_H_

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "EnemyTemplate.h"
#include "Chuck.h"
#include "Boo.h"

class j1EnemyModule : public j1Module
{
public:

	j1EnemyModule();
	virtual ~j1EnemyModule();

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

	void				DeleteBoo(Enemy* boo);
	void				DeleteChuck(Enemy* chuck);

	bool				Load(pugi::xml_node&);
	bool				Save(pugi::xml_node&)const;

public:

	p2List<Enemy*>		enemies;
	bool				flies;
};

#endif