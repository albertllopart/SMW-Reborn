#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "Entity.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		colliders[i] = nullptr;
	}

	matrix[COLLIDER_PLAYER][COLLIDER_CHUCK] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BOO] = true;

	matrix[COLLIDER_CHUCK][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CHUCK][COLLIDER_BOO] = false;

	matrix[COLLIDER_BOO][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOO][COLLIDER_CHUCK] = false;
}

j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

bool j1Collision::Update(float dt)
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		//skip empty colliders
		if (colliders[i] = nullptr)
		{
			continue;
		}

		c1 = colliders[i];

		//avoid checking collisions already checked
		for (uint j = i + 1; j < MAX_COLLIDERS; j++)
		{
			//skip empty colliders
			if (colliders[j] == nullptr)
			{
				continue;
			}

			c2 = colliders[j];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type])
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type])
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool j1Collision::PostUpdate()
{
	DebugDraw();
	return true;
}

void j1Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_UP)
	{
		debug = !debug;
	}

	if (debug = false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
			case COLLIDER_NONE:
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha); //white
				break;
			case COLLIDER_PLAYER:
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha); //green
				break;
			case COLLIDER_CHUCK:
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha); //red
				break;
			case COLLIDER_BOO:
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha); //red
				break;
		}
	}
}

bool j1Collision::CleanUp()
{
	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Entity* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool j1Collision::EraseCollider(Collider* collider)
{
	if (collider != nullptr)
	{
		// we still search for it in case we received a dangling pointer
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == collider)
			{
				collider->to_delete = true;
				break;
			}
		}
	}


	return false;
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}