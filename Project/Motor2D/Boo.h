#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Animation.h"
#include "Entity.h"

#define BOO_SIZE 16 //same hight/width

struct SDL_Texture;

class Boo : public Entity
{
public:

	Boo();
	virtual ~Boo();

	// Called before render is available
	bool				Awake();

	// Called before the first frame
	bool				Start();

	// Called before all Updates
	bool				PreUpdate();

	// Called each loop iteration
	bool				Update(float dt);

	void				Draw();

	// Called before all Updates
	bool				PostUpdate();

	//Save and Load functions
	bool				Load(pugi::xml_node &);
	bool				Save(pugi::xml_node&)const;

	
	// Called before quitting
	bool				CleanUp();

	//move
	void				Move();
	void				Pathfinding();
	bool				CreatePath(fPoint destination);
	bool				Find_a_Path();
	void				Movement(iPoint go_to);
	iPoint				GetPositionINT() const;

private:

	SDL_Texture*		graphic = nullptr;

	//Animations
	Animation			idle;
	Animation			chase_left;
	Animation			chase_right;
	Animation			stop_left;
	Animation			stop_right;
	Animation*			current_animation;

	//pathfinding
	bool						create_path;
	bool						path_stopped;
	bool						pathfinding;
	bool						find_path;
	bool						is_path_done;
	int							path;
	int							last_path;
	int							path_size;
	const p2DynArray<iPoint>*	last_pathfinding;
	p2DynArray<iPoint>			mlast_pathfinding; //m was Daniel Branicki idea lul

	//pathfinding timer
	float						pathfind_timer = 0;
	bool						boo_chase = false;
	
};