#include "DevRookiesApp.h"
#include "Input.h"
#include "Render.h"
#include "Collision.h"

Collision::Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GROUND] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_LIMIT] = true;
}

// Destructor
Collision::~Collision()
{}

bool Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

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

	return true;
}

// Called before render is available
bool Collision::Update(float dt)
{
	//if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) App->collision->GodMode();
	DebugDraw();

	return true;
}

void Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, true);
			break;
		case COLLIDER_GROUND: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_LIMIT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 100, 200, 10, alpha);
			break;
		}
	}
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
			break;
		}
	}

	return ret;
}

void Collision::GodMode()
{
	god = !god;
	god_used = true;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (enable) {
		if ((r.x < rect.x + rect.w) && (rect.x < r.x + r.w)
			&& (r.y < rect.y + rect.h) && (rect.y < r.y + r.h)) {
			return true;
		}
		return false;
	}
	else return false;
}