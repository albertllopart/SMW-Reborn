#ifndef _j1PLAYER_H_
#define _j1PLAYER_H_

#include	"PugiXml/src/pugixml.hpp"
#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"j1Animation.h"

#define		SPEED_X 100.0f
#define		SPEED_Y 1.0f
#define		GRAVITY -2.0f

#define		TILE_WIDTH	16
#define		MARIO_WIDTH 14
#define		MARIO_HIGHT 28

struct SDL_texture;
struct SDL_Rect;

enum PLAYER_STATE
{
	IDLE_R,
	IDLE_L,
	SHORT_HOP_L,
	SHORT_HOP_R,
	WALK_L,
	WALK_R,
	RUN_L,
	RUN_R

};

enum Direction
{
	NM, //Not moving
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();
	bool Start();
	bool CleanUp();
	bool Awake(pugi::xml_node& config);
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

	bool level_complete = false;

	Direction			dir;
	bool				dead = false;

private:
	p2SString			name = nullptr;
	unsigned int		width = 0;
	unsigned int		height = 0;
	SDL_Texture*		graphic = nullptr;
	SDL_Rect*			test;
	PLAYER_STATE		state;
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
};

#endif