#include "JrGargoyle.h"
#include "Scene.h"
#include "Render.h"
#include "EntityManager.h"
#include "Player.h"
#include "Pathfinding.h"
#include "Textures.h"
//#include "DevRookiesApp.h"


JrGargoyle::JrGargoyle() : Enemy(entityType::FLYING_ENEMY)
{
}
JrGargoyle::JrGargoyle(entityType type) : Enemy(entityType::FLYING_ENEMY)
{
}
JrGargoyle::~JrGargoyle()
{
}


bool JrGargoyle::Awake(pugi::xml_node & conf)
{
	pugi::xml_node config = conf.child("JrGargoyle");
	gargoyle_texture = config.child("texture").child_value();

	LoadAnimation(config.child("animations").child("idle").child("frame"), idle);
	idle.speed = config.child("animations").child("idle").attribute("speed").as_float();
	idle.loop = config.child("animations").child("idle").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("fly").child("frame"), fly);
	fly.speed = config.child("animations").child("fly").attribute("speed").as_float();
	fly.loop = config.child("animations").child("fly").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("die").child("frame"), dead);
	dead.speed = config.child("animations").child("die").attribute("speed").as_float();
	dead.speed = config.child("animations").child("die").attribute("loop").as_bool(false);
	return true;
}

bool JrGargoyle::Start(uint i)
{
	gargoyle_tex = App->textures->Load(gargoyle_texture.GetString());
	return true;
}

bool JrGargoyle::PreUpdate()
{
	bool ret = true;
	if (position.DistanceManhattan(App->entitymanager->player->position) < distance)
	{
		iPoint playerpos = { (int)App->entitymanager->player->position.x, (int)App->entitymanager->player->position.y };
		iPoint pos = { (int)position.x, (int)position.y };
		App->pathfinding->CreatePath(pos, playerpos);
		Fly(App->pathfinding->GetLastPath());
		current_movement = LEFT;
	}
	else {
		current_movement = IDLE;
		//current_movement = LEFT;
		current_animation = &fly;
	}

	return ret;
}

bool JrGargoyle::Update(float dt)
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
	position.y += speed.y;
	collider->rect.x = position.x;
	collider->rect.y = position.y;

	return ret;
}

bool JrGargoyle::PostUpdate()
{
	App->render->Blit(gargoyle_tex, position.x, position.y, &current_animation->GetCurrentFrame(), 1.0f, flipX);
	
	return true;
}

bool JrGargoyle::CleanUp()
{
	App->textures->UnLoad(gargoyle_tex);
	gargoyle_tex = nullptr;
	return true;
}

void JrGargoyle::OnCollision(Collider * collider1)
{
	if (collider1->type == COLLIDER_PLAYER)
		Die();
}

bool JrGargoyle::LoadAnimation(pugi::xml_node &node, Animation &anim) {

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

void JrGargoyle::Fly(const p2DynArray<iPoint> *path)
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

bool JrGargoyle::Restart(uint i)
{
	position = App->map->init_JrGargoyle_position.At(i - 1)->data;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,60,80 }, COLLIDER_ENEMY, App->entitymanager);
	current_animation = &idle;
	return true;
}

void JrGargoyle::Die() {

	//App->entitymanager->DestroyEntity(this);
}