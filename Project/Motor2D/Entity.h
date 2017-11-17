#pragma once
#include "j1App.h"
#include "p2Point.h"
#include "j1Collision.h"

struct SDL_Texture;

enum EState
{
	IDLE_RIGHT,
	IDLE_LEFT,
	SHORT_HOP_LEFT,
	SHORT_HOP_RIGHT,
	WALK_LEFT,
	WALK_RIGHT,
	RUN_LEFT,
	RUN_RIGHT
};

enum EDirection
{
	U,
	D,
	L,
	R
};

enum Type
{
	CHUCK,
	BOO
};

class Entity
{
public:

	Entity() {};
	virtual ~Entity() {};

	// Called before render is available
	virtual bool Awake()
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	//virtual load/save function
	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&)const
	{
		return true;
	}

	virtual void OnCollision(Collider*, Collider*){}

public:

	bool			active;
	Type			type;
	p2SString		name;
	fPoint			position;
	bool			flies;

	EState			state;
	EDirection		direction;

	Collider*		collision = nullptr;
};