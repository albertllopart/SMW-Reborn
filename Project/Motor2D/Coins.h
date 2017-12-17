#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Animation.h"
#include "Entity.h"

#define BOO_SIZE 16 //same hight/width

struct SDL_Texture;


class Coins : public Entity
{
public:

	Coins();
	virtual ~Coins();

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



	// Called before quitting
	bool				CleanUp();

	//move

private:

	SDL_Texture*		graphic = nullptr;

	//Animations
	Animation			idle;
	Animation*			current_animation = nullptr;
};
