#pragma once
#include	"PugiXml/src/pugixml.hpp"
#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"j1Animation.h"
#include	"j1Collision.h"
#include	"Entity.h"

#define		SPEED_X 100
#define		SPEED_Y 1
#define		GRAVITY -2

#define		TILE_WIDTH	16
#define		MARIO_WIDTH 14
#define		MARIO_HIGHT 28

struct SDL_texture;
struct SDL_Rect;

class j1Player : public Entity
{
public:
	j1Player();
	~j1Player();
	bool Start();
	bool CleanUp();
	bool Awake();
	bool Update(float dt);
	bool PostUpdate();
	bool Load();
	bool Save() const;
	void Input(float dt);
	void Draw();
	bool Jump();
	bool Falling();
	bool GodMode();
	
	iPoint				player_quadrant_1;
	iPoint				player_quadrant_2;
	uint				player_lives = 0;
	uint				player_coins = 0;
	uint				player_score = 0;
	uint				player_hours = 0;
	uint				player_minutes = 0;
	uint				player_seconds = 0;

	bool				level_complete = false;
	
private:
	unsigned int		width = 0;
	unsigned int		height = 0;
	SDL_Texture*		graphic = nullptr;
	SDL_Rect*			test = nullptr;
	fPoint				velocity;
	float				gravity = 9.8;
	
	
	bool				jump2_on = false;

	//Animations
	Animation			idle_left;
	Animation			idle_right;
	Animation			walk_left;
	Animation			walk_right;
	Animation			short_hop_left;
	Animation			short_hop_right;
	Animation*			current_animation;

	//timer
	float				accumulatted_time;

};

