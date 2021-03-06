#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "Entity.h"
#include "j1EntityModule.h"
#include "j1Audio.h"
#include "j1FadeToBlack.h"
#include "j1EntityModule.h"
#include "j1Player.h"
#include "j1Gui.h"
#include "GuiElement.h"

j1Collision::j1Collision()
{
	name.create("Collision");
	for (uint i = 0; i < MAX_COLLIDERS; i++)
	{
		colliders[i] = nullptr;
	}

	matrix[COLLIDER_PLAYER][COLLIDER_CHUCK] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BOO] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HEAD_CHUCK] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_COIN] = false;

	matrix[COLLIDER_CHUCK][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CHUCK][COLLIDER_BOO] = false;
	matrix[COLLIDER_CHUCK][COLLIDER_COIN] = false;

	matrix[COLLIDER_BOO][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOO][COLLIDER_CHUCK] = false;
	matrix[COLLIDER_BOO][COLLIDER_COIN] = false;

	matrix[COLLIDER_HEAD_CHUCK][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_COIN][COLLIDER_PLAYER] = false;
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
		if (colliders[i] == nullptr)
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
			if (c1->CheckCollision(c2->rect) == true && c2->type == COLLIDER_COIN && c1->type != COLLIDER_CHUCK)
			{
				App->entitymodule->DeleteEntity(c2->callback);
				App->audio->PlayFx(9);
				App->entitymodule->player->player_coins++;
				App->entitymodule->player->player_score += 50;

			}
			if (c1->CheckCollision(c2->rect) == true && App->entitymodule->player->god_mode == false)
			{
				if (/*c1->type == COLLIDER_HEAD_CHUCK ||*/ c2->type == COLLIDER_HEAD_CHUCK && matrix[c1->type][c2->type])
				{
					App->entitymodule->player->jump = true;
					App->entitymodule->player->jump_height = App->entitymodule->player->position.y - 35;
					App->entitymodule->player->jump1_on = true;
					App->entitymodule->player->player_score += 200;
					/*uint points_chuck = 200;
					App->gui->CreateNumber(App->entitymodule->player->position.x + 3, App->entitymodule->player->position.y - 10, &points_chuck, { 255, 255, 255, 255 }, App->fonts->numbers, App->gui, true);
					*/
					App->entitymodule->DeleteEntity(c2->callback);						
					break;
											
				}
				else if (matrix[c1->type][c2->type])
				{
					if (App->entitymodule->player->dead == false)
					{
						App->audio->PlayFx(5);
						App->fadetoblack->FadeToBlack(NULL, NULL, 1.5f);
						App->entitymodule->player->dead = true;
						--App->entitymodule->player->player_lives;
					}
					
				}
				
			}
			else
			{
				//LOG("GOD MODE");
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

	if (debug == false)
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
				App->render->DrawQuad(colliders[i]->rect, 255, 35, 1, alpha); //red
				break;
			case COLLIDER_BOO:
				App->render->DrawQuad(colliders[i]->rect, 255, 35, 1, alpha); //red
				break;
			case COLLIDER_HEAD_CHUCK:
				App->render->DrawQuad(colliders[i]->rect, 75, 0, 130, alpha); //purple
				break;
			case COLLIDER_COIN:
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha); //yellow
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
				collider->to_delete = false;
				delete colliders[i];
				colliders[i] = nullptr;
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