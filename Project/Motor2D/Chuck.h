#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Animation.h"
#include "Entity.h"

#define HEAD_DISTANCE 1
#define CHUCK_HEAD_HIGHT 5
#define CHUCK_HIGHT 27
#define CHUCK_WIDTH 26
#define CHASE_RANGE 120

struct SDL_Texture;

class Chuck : public Entity
{
public:
	Chuck();
	virtual ~Chuck();

	// Called before render is available
	bool				 Awake();

	// Called before the first frame
	bool				Start();

	// Called before all Updates
	bool				PreUpdate();

	// Called each loop iteration
	bool				Update(float dt);

	void				Draw();

	// Called before all Updates
	bool				PostUpdate();
	
	fPoint				Getposition() const;

	// Called before quitting
	bool				CleanUp();

	void				ChuckPoints();
	//move when the player is near
	void				Move(float dt);
	fPoint				GetPositionINT() const;

	bool				Falling();
	bool				chuck_dead = false;

	iPoint				chuck_quadrant_1;
	iPoint				chuck_quadrant_2;

private:

	//Draw
	SDL_Texture*		graphic = nullptr;

	//Animations
	Animation			idle;
	Animation			walk_left;
	Animation			walk_right;
	Animation			jump_left;
	Animation			jump_right;
	Animation*			current_animation;

	//Move
	float				count;
	float				walking_sound_timer = 0;

};