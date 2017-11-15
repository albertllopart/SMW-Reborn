#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Animation.h"
#include "Entity.h"

#define CHUCK_HIGHT 27
#define CHUCK_WIDTH 26

struct SDL_Texture;

class Chuck : public Entity
{
public:
	Chuck();
	virtual ~Chuck();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt, Chuck Entity1);

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

	//move when the player is near
	void Move(Chuck Entity);

private:

	EDirection direction;
	SDL_Texture* graphic = nullptr;

	//Animations
	Animation			idle;
	Animation			walk_left;
	Animation			walk_right;
	Animation			jump_left;
	Animation			jump_right;
	Animation*			current_animation;

public:
};