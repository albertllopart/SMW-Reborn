#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Animation.h"
#include "EnemyTemplate.h"

#define BOO_SIZE 16 //same hight/width

struct SDL_Texture;

class Boo : public Enemy
{
public:

	Boo();
	virtual ~Boo();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void Draw();

	// Called before all Updates
	bool PostUpdate();

	//Save and Load functions
	bool Load(pugi::xml_node &);
	bool Save(pugi::xml_node&)const;

	int GetDirection() const;

	iPoint Getposition() const;

	// Called before quitting
	bool CleanUp();

private:

	EDirection direction;
	SDL_Texture* graphic = nullptr;

	//Animations
	Animation			idle;
	Animation			chase_left;
	Animation			chase_right;
	Animation			stop_left;
	Animation			stop_right;
	Animation*			current_animation;
};