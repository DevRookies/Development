#include "DevRookiesApp.h"
#include "Input.h"
#include "Render.h"
#include "Collision.h"
#include "EntityManager.h"
#include "Brofiler/Brofiler.h"

Collision::Collision()
{
	name.create("collision");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_FIRE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ICE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POISON] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BORDER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FINAL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
}

// Destructor
Collision::~Collision()
{}

bool Collision::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateCollision", Profiler::Color::Orange);

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	// Remove all colliders
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	//Check Collision
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{

		if (colliders[i] != nullptr) {
			c1 = colliders[i];

			for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
			{
				if (colliders[k] != nullptr) {
					
					c2 = colliders[k];

					if (c1->enable && c2->enable) {
						if (c1->CheckCollision(c2->rect) == true)
						{
							if (matrix[c1->type][c2->type] && c1->callback)
								c1->callback->OnCollision(c1, c2);

							if (matrix[c2->type][c1->type] && c2->callback)
								c2->callback->OnCollision(c2, c1);
						}
					}
				}
			}
		}
	}

	return true;
}

// Called before render is available
bool Collision::Update(float dt)
{
	BROFILER_CATEGORY("UpdateCollision", Profiler::Color::Aqua);


	if (debug != false) {

		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] != nullptr) {
				switch (colliders[i]->type)
				{
				case COLLIDER_NONE: // white
					App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, 80);
					break;
				case COLLIDER_PLAYER: // green
					App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, 80, true);
					break;
				case COLLIDER_ICE: // blue
					App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, 80);
					break;
				case COLLIDER_FIRE: // red
					App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, 80);
					break;
				case COLLIDER_POISON: // green
					App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, 80);
					break;
				case COLLIDER_BORDER: // black
					App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, 80);
					break;
				case COLLIDER_ENEMY: // black
					App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, 80);
					break;
				case COLLIDER_FINAL: // black
					App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, 80);
					break;
				}
			}
		}
	}

	return true;
}


// Called before quitting
bool Collision::CleanUp()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			if (type == COLLIDER_PLAYER) player_collider = colliders[i];
			break;
		}
	}

	return ret;
}


// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	bool ret = false;

	if (enable) {
		if ((r.x < rect.x + rect.w) && (rect.x < r.x + r.w)
			&& (r.y < rect.y + rect.h) && (rect.y < r.y + r.h)) {
			ret = true;
		}
	}

	return ret;
}

bool Collision::CheckCollision() const
{
	bool ret = false;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->type != COLLIDER_PLAYER)
		{
			if (player_collider->CheckCollision(colliders[i]->rect))
			{
				App->entitymanager->player->OnCollision(colliders[i]);

				ret = true;
			}
		}
	}

	return ret;
}
