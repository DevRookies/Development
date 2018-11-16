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

//----------------------------------------------------
void Entity::OnCollision(Collider * collider1, Collider * collider2)
{

	collider->SetPos(position.x, position.y);
	if (!collider1->CheckCollision(collider2->rect))
	{
		return;
	}

}