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
	return true;
}

bool Entity::Save(pugi::xml_node & save_game) const
{
	return true;
}

void Entity::AddFX(const int channel, const int repeat) const
{
	App->audio->PlayFx(channel, repeat);
}

//LoadAnimation with LoadCollider structure
bool Entity::LoadAnimation(pugi::xml_node &node, Animation &anim) 
{
	return true;
}

void Entity::AddCollider() 
{
}


fPoint Entity::GetPosition()
{
	return fPoint();
}

void Entity::SetPosition(const float &x, const float &y)
{

}