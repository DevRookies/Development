#include "JrGargoyle.h"
#include "Scene.h"
#include "Render.h"
#include "EntityManager.h"
#include "Pathfinding.h"
#include "Textures.h"
//#include "DevRookiesApp.h"


JrGargoyle::JrGargoyle() : Enemy(entityType::FLYING_ENEMY)
{

}
JrGargoyle::JrGargoyle(entityType type) : Enemy(entityType::FLYING_ENEMY)
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

JrGargoyle::~JrGargoyle()
{
}

bool JrGargoyle::Update(float dt)
{

	return true;
}

bool JrGargoyle::Start()
{
	gargoyle_tex = App->textures->Load(gargoyle_texture.GetString());
	position = App->map->init_JrGargoyle_position;
	//collider = App->collision->AddCollider({ (int)position.x, (int)position.y,32,32 }, COLLIDER_ENEMY, this);
	return true;
}

bool JrGargoyle::Fly()
{
	return true;
}

bool JrGargoyle::CleanUp()
{
	App->textures->UnLoad(gargoyle_tex);
	gargoyle_tex = nullptr;
	return true;
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