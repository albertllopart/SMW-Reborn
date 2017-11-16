#pragma once
#include	"PugiXml/src/pugixml.hpp"
#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"j1Animation.h"
#include	"j1Collision.h"
#include	"Entity.h"

#define		SPEED_X 100.0f
#define		SPEED_Y 1.0f
#define		GRAVITY -2.0f

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
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void Input(float dt);
	void Draw();
	bool Jump();
	bool Falling();

	fPoint				position;
	iPoint				player_quadrant_1;
	iPoint				player_quadrant_2;

	bool				level_complete = false;

	bool				dead = false;

private:
	unsigned int		width = 0;
	unsigned int		height = 0;
	SDL_Texture*		graphic = nullptr;
	SDL_Rect*			test;
	fPoint				velocity;
	float				gravity = 9.8;
	bool				jump;
	int					jump_height;
	bool				jump1_on = false;
	bool				jump2_on = false;

	//Animations
	Animation			idle_left;
	Animation			idle_right;
	Animation			walk_left;
	Animation			walk_right;
	Animation			short_hop_left;
	Animation			short_hop_right;
	Animation*			current_animation;

	Collider*			collision = nullptr;
};

