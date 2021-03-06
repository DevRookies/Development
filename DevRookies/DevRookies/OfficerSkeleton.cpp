#include "OfficerSkeleton.h"
#include "Scene.h"
#include "Render.h"
#include "EntityManager.h"
#include "Audio.h"
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

	speed = { config.child("speed").attribute("x").as_float(),  config.child("speed").attribute("y").as_float() };
	acceleration = { config.child("acceleration").attribute("x").as_float(), config.child("acceleration").attribute("y").as_float() };
	max_speed = { config.child("max_speed").attribute("x").as_float() , config.child("max_speed").attribute("y").as_float() };

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
	return true;
}

bool OfficerSkeleton::PreUpdate()
{
	bool ret = true;
	if (visibility) {
		if (position.DistanceManhattan(App->entitymanager->player->position) < distance)
		{
			iPoint playerpos = { (int)App->entitymanager->player->position.x, (int)App->entitymanager->player->position.y };
			iPoint pos = { (int)position.x, (int)position.y };
			App->pathfinding->CreatePath(App->map->WorldToMap(pos.x, pos.y), App->map->WorldToMap(playerpos.x, playerpos.y));
			Walk(App->pathfinding->GetLastPath());
		}
		else {
			current_movement = IDLE;
			current_animation = &idle;
		}
	}
	

	return ret;
}

bool OfficerSkeleton::Update(float dt)
{
	bool ret = true;
	speed.y = floor((acceleration.y * max_speed.y + (1 - acceleration.y) * speed.y) * dt);
	float distance = App->collision->CollisionCorrectionDown(collider->rect);
	if (distance <= speed.y)
	{
		speed.y = distance;
	}
	else 
		current_movement = DOWN;
	
	if (current_movement == IDLE)
	{
		speed.x = 0;
		speed.y = 0;
		current_animation = &idle;
	}
	else if (current_movement == LEFT)
	{
		flipX = false;
		speed.x = acceleration.x * -max_speed.x + (1 - acceleration.x) * -speed.x;
		current_animation = &walk;
	}
	else if (current_movement == RIGHT)
	{
		flipX = true;
		speed.x = acceleration.x * max_speed.x + (1 - acceleration.x) * speed.x;
		current_animation = &walk;
	}
	
	speed.x = floor(speed.x * dt);
	if(App->render->start_time == 0)
		position += speed;
	collider->rect.x = position.x;
	collider->rect.y = position.y;
	current = current_animation->GetCurrentFrame(dt);

	return true;
}

bool OfficerSkeleton::PostUpdate() 
{
	if(visibility)
		App->render->Blit(skeleton_tex, position.x, position.y, &current, 1.0f, flipX);

	return true;
}

bool OfficerSkeleton::CleanUp()
{
	App->textures->UnLoad(skeleton_tex);
	skeleton_tex = nullptr;
	collider->to_delete = true;
	visibility = false;
	return true;
}

bool OfficerSkeleton::Load(pugi::xml_node& node)
{
	bool ret = true;

	position.x = node.child("position").attribute("x").as_float(0);
	position.y = node.child("position").attribute("y").as_float(0);

	return ret;
}

bool OfficerSkeleton::Save(pugi::xml_node& node) const
{
	bool ret = true;

	if (skeleton_tex != nullptr) {
		pugi::xml_node pos = node.append_child("position");
		pos.append_attribute("x") = position.x;
		pos.append_attribute("y") = position.y;
	}
		
	return ret;
}

void OfficerSkeleton::OnCollision(Collider * collider1, Collider* collider2)
{
	if (collider1->type == COLLIDER_PLAYER) {
		CleanUp();
		AddFX(6, 0);
		App->entitymanager->player->score += 200;
		LOG("SCORE ENEMY: %i", App->entitymanager->player->score);
	}
	else if (collider1->type == COLLIDER_POISON) {
		CleanUp();
	}
	
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
		if (path->At(1) != nullptr) {
			iPoint pos = App->map->MapToWorld(path->At(1)->x, path->At(1)->y);
			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos_debug = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				App->render->Blit(App->scene->debug_tex, pos.x, pos.y);
			}
			if (position.x > pos.x)
				current_movement = LEFT;
			else if (position.x < pos.x)
				current_movement = RIGHT;
		}
		
	}
}


bool OfficerSkeleton::Restart(uint i)
{
	skeleton_tex = App->textures->Load(skeleton_texture.GetString());
	position = App->map->init_Skeleton_position.At(i - App->map->init_JrGargoyle_position.count() - 1)->data;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,80,90 }, COLLIDER_ENEMY, App->entitymanager);
	if (App->scene->scene_actual == 0)
		flipX = true;
	else
		flipX = false;
	visibility = true;
	return true;
}
