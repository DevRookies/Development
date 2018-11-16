#include "OfficerSkeleton.h"
#include "Scene.h"
#include "Render.h"
#include "EntityManager.h"
//#include "DevRookiesApp.h"


OfficerSkeleton::OfficerSkeleton() : Enemy(entityType::LAND_ENEMY)
{

}

OfficerSkeleton::OfficerSkeleton(iPoint pos) : Enemy(LAND_ENEMY, pos)
{
	/*texture = config.child("texture").child_value();

	LoadAnimation(config.child("animations").child("idle").child("frame"), idle);
	idle.speed = config.child("animations").child("idle").attribute("speed").as_float();
	idle.loop = config.child("animations").child("idle").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("fly").child("frame"), walk);
	walk.speed = config.child("animations").child("fly").attribute("speed").as_float();
	walk.loop = config.child("animations").child("fly").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("die").child("frame"), dead);
	dead.speed = config.child("animations").child("die").attribute("speed").as_float();
	dead.speed = config.child("animations").child("die").attribute("loop").as_bool(false);*/
}


OfficerSkeleton::~OfficerSkeleton()
{
}

bool OfficerSkeleton::Update(float dt)
{
	return true;
}

bool OfficerSkeleton::Start()
{
	/*skeleton_texture = App->textures->Load(texture.GetString());*/
	return true;
}

bool OfficerSkeleton::Walk()
{
	return true;
}

bool OfficerSkeleton::CleanUp()
{
	return true;
}

//This should go in Enemy.h and .cpp
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