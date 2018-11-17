#include "OfficerSkeleton.h"
#include "Scene.h"
#include "Render.h"
#include "EntityManager.h"
#include "DevRookiesApp.h"
//more
#include "p2Log.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Enemy.h"
#include "PathFinding.h"
#include "Player.h"
#include "Textures.h"


OfficerSkeleton::OfficerSkeleton() : Enemy(entityType::LAND_ENEMY)
{

}

OfficerSkeleton::OfficerSkeleton(iPoint pos) : Enemy(LAND_ENEMY, pos)
{

}

bool OfficerSkeleton::Start()
{
	skeleton_tex = App->textures->Load(skeleton_texture.GetString());
	return true;
}

bool OfficerSkeleton::Restart()
{
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,32,32 }, COLLIDER_ENEMY, this);
	return true;
}

bool OfficerSkeleton::Awake(pugi::xml_node & config) 
{
	skeleton_texture = config.child("texture").child_value();

	LoadAnimation(config.child("animations").child("idle").child("frame"), idle);
	idle.speed = config.child("animations").child("idle").attribute("speed").as_float();
	idle.loop = config.child("animations").child("idle").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("fly").child("frame"), walk);
	walk.speed = config.child("animations").child("fly").attribute("speed").as_float();
	walk.loop = config.child("animations").child("fly").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("die").child("frame"), dead);
	dead.speed = config.child("animations").child("die").attribute("speed").as_float();
	dead.speed = config.child("animations").child("die").attribute("loop").as_bool(false);
	return true;
}


OfficerSkeleton::~OfficerSkeleton()
{
}

bool OfficerSkeleton::PreUpdate()
{
	if (position.DistanceNoSqrt(App->entitymanager->player->position) < range_of_trigger)
	{
		iPoint iplayerpos = { (int)App->entitymanager->player->position.x, (int)App->entitymanager->player->position.y };
		iPoint ipos = { (int)position.x, (int)position.y };
		App->pathfinding->CreatePath(ipos, iplayerpos);
		Walk(App->pathfinding->GetLastPath());
	}
	else current_movement = IDLE_E;
	current_movement = LEFT_E;
	current_animation = &walk;
	return true;
}

bool OfficerSkeleton::Update(float dt)
{
	if (current_movement == IDLE_E)
	{
		speed.x = 0;
	}

	if (current_movement == LEFT_E)
	{
		sprite_flipX = false;
		speed.x = -3;
		speed.x = floor(speed.x*dt);

		float distance = App->collision->CollisionCorrectionLeft(collider->rect);
		if (-distance > speed.x)
		{
			speed.x = -distance;
		}
	}

	if (current_movement == RIGHT_E)
	{
		sprite_flipX = true;
		speed.x = 3;
		speed.x = floor(speed.x*dt);

		float distance = App->collision->CollisionCorrectionRight(collider->rect);
		if (distance < speed.x)
		{
			speed.x = distance;
		}
	}

	position.x += speed.x;
	collider->rect.x = position.x;

	speed.y += floor(acceleration.y*dt);
	if (speed.y > 0)
	{

		float distance = App->collision->CollisionCorrectionDown(collider->rect);
		if (distance < speed.y)
		{
			speed.y = distance;
			if (distance <= 1)current_state = ONFLOOR_E;
		}
	}
	App->render->Blit(skeleton_tex, position.x, position.y, &current_animation->GetCurrentFrame(), 1.0F, sprite_flipX, sprite_flipY);

	position.y += speed.y;
	collider->rect.y = position.y;

	return true;
}

bool OfficerSkeleton::PostUpdate() 
{
	return true;
}

void OfficerSkeleton::OnCollision(Collider * collider1, Collider * collider2)
{
	switch (collider1->type)
	{
	case COLLIDER_PLAYER://whenever the player collides with map limit he dies.
		break;
	default:
		break;
	}

}

bool OfficerSkeleton::Walk(const p2DynArray<iPoint> *path)
{
	return true;
}

bool OfficerSkeleton::CleanUp()
{
	App->textures->UnLoad(skeleton_tex);
	skeleton_tex = nullptr;
	return true;
}

bool OfficerSkeleton::LoadAnimation(pugi::xml_node &node, Animation &anim) {

	for (; node; node = node.next_sibling("frame")) {
		SDL_Rect frame_rect;
		frame_rect.x = node.attribute("x").as_int();
		frame_rect.y = node.attribute("y").as_int();
		frame_rect.w = node.attribute("width").as_int();
		frame_rect.h = node.attribute("height").as_int();
		anim.PushBack(frame_rect);
	}
	return true;
}