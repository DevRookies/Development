#include "EntityManager.h"
#include "Entity.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Audio.h"


Entity::Entity()
{
}

Entity::Entity(entityType type) : type(type)
{
}

Entity::~Entity()
{
}

bool Entity::Load(pugi::xml_node & save_game)
{
	return false;
	position.x = save_game.child("position").attribute("x").as_float();
	position.y = save_game.child("position").attribute("y").as_float();
	speed.x = save_game.child("speed").attribute("x").as_float();
	speed.y = save_game.child("speed").attribute("y").as_float();
	return true;
}

bool Entity::Save(pugi::xml_node & save_game) const
{
	return false;
	pugi::xml_node position_node = save_game.append_child("position");
	position_node.append_attribute("x") = position.x;
	position_node.append_attribute("y") = position.y;
	pugi::xml_node velocity_node = save_game.append_child("speed");
	velocity_node.append_attribute("x") = speed.x;
	velocity_node.append_attribute("y") = speed.y;
	return true;
}

void Entity::AddFX(const int channel, const int repeat) const
{
	App->audio->PlayFx(channel, repeat);
}

//LoadAnimation with LoadCollider structure
bool Entity::LoadAnimation(pugi::xml_node &node, Animation &anim) {

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

void Entity::AddCollider() 
{
}

//void Entity::OnCollision(Collider * collider1, Collider * collider2)
//{
//
//	collider->SetPos(position.x, position.y);
//	if (!collider1->CheckCollision(collider2->rect))
//	{
//		return;
//	}
//
//}

fPoint Entity::GetPosition()
{
	return fPoint();
}

void Entity::SetPosition(const float &x, const float &y)
{

}