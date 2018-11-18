#include "OfficerSkeleton.h"
#include "Scene.h"
#include "Render.h"
#include "EntityManager.h"
#include "Player.h"
#include "Pathfinding.h"
#include "Textures.h"



OfficerSkeleton::OfficerSkeleton() : Enemy(entityType::LAND_ENEMY)
{

}
OfficerSkeleton::OfficerSkeleton(entityType type) : Enemy(entityType::LAND_ENEMY)
{

}
OfficerSkeleton::~OfficerSkeleton()
{
}

bool OfficerSkeleton::Awake(pugi::xml_node & conf)
{
	pugi::xml_node config = conf.child("OfficerSkeleton");
	skeleton_texture = config.child("texture").child_value();

	LoadAnimation(config.child("animations").child("idle").child("frame"), idle);
	idle.speed = config.child("animations").child("idle").attribute("speed").as_float();
	idle.loop = config.child("animations").child("idle").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("walk").child("frame"), walk);
	walk.speed = config.child("animations").child("walk").attribute("speed").as_float();
	walk.loop = config.child("animations").child("walk").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("die").child("frame"), dead);
	dead.speed = config.child("animations").child("die").attribute("speed").as_float();
	dead.speed = config.child("animations").child("die").attribute("loop").as_bool(false);
	return true;
}

bool OfficerSkeleton::Start(uint i)
{
	skeleton_tex = App->textures->Load(skeleton_texture.GetString());
	return true;
}

bool OfficerSkeleton::PreUpdate()
{
	bool ret = true;
	if (position.DistanceManhattan(App->entitymanager->player->position) < distance)
	{
		iPoint playerpos = { (int)App->entitymanager->player->position.x, (int)App->entitymanager->player->position.y };
		iPoint pos = { (int)position.x, (int)position.y };
		App->pathfinding->CreatePath(App->map->WorldToMap(pos.x, pos.y), App->map->WorldToMap(playerpos.x, playerpos.y));
		Walk(App->pathfinding->GetLastPath());
		current_movement = LEFT;
	}
	else {
		current_movement = IDLE;
		/*current_movement = LEFT;*/
		current_animation = &walk;
	}

	return ret;
}

bool OfficerSkeleton::Update(float dt)
{
	bool ret = true;

	if (current_movement == IDLE)
	{
		speed.x = 0;
	}

	if (current_movement == LEFT)
	{
		flipX = false;
		speed.x = -3;
		speed.x = floor(speed.x*dt);
	}

	if (current_movement == RIGHT)
	{
		flipX = true;
		speed.x = 3;
		speed.x = floor(speed.x*dt);
		
	}

	if (current_movement == UP)
	{
		speed.y = 3;
		speed.y = floor(speed.x*dt);
	}
	if (current_movement == DOWN)
	{
		speed.y = 3;
		speed.y = floor(speed.x*dt);

	}

	position.x += speed.x;
	collider->rect.x = position.x;

	/*speed.y += floor(acceleration.y*dt);
	if (speed.y > 0)
	{

		
	}*/

	position.y += speed.y;
	collider->rect.y = position.y;

	return true;
}

bool OfficerSkeleton::PostUpdate() 
{
	App->render->Blit(skeleton_tex, position.x, position.y, &current_animation->GetCurrentFrame(), 1.0f, flipX);

	return true;
}

bool OfficerSkeleton::CleanUp()
{
	App->textures->UnLoad(skeleton_tex);
	skeleton_tex = nullptr;
	collider->to_delete = true;
	return true;
}


void OfficerSkeleton::OnCollision(Collider * collider1)
{
	if (collider1->type == COLLIDER_PLAYER)
		CleanUp();
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


void OfficerSkeleton::Walk(const p2DynArray<iPoint> *path)
{
	if (path->Count() > 0)
	{
		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			App->render->Blit(App->scene->debug_tex, pos.x, pos.y);
		}
	}
}


bool OfficerSkeleton::Restart(uint i)
{
	skeleton_tex = App->textures->Load(skeleton_texture.GetString());
	position = App->map->init_Skeleton_position.At(i - App->map->init_JrGargoyle_position.count() - 1)->data;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,80,90 }, COLLIDER_ENEMY, App->entitymanager);
	current_animation = &idle;
	return true;
}
