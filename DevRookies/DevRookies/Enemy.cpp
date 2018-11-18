#include "DevRookiesApp.h"
#include "Enemy.h"
#include "Collision.h"
#include "Render.h"

Enemy::Enemy(entityType type) : Entity(type)
{
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Enemy::Start()
{
	return false;
}

bool Enemy::PreUpdate()
{
	return false;
}

bool Enemy::Update(float dt)
{
	return false;
}

bool Enemy::PostUpdate()
{
	return false;
}

bool Enemy::CleanUp()
{
	return false;
}

void Enemy::Die()
{

}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

bool Enemy::Save(pugi::xml_node &data) const
{
	bool ret = true;
	if (type == entityType::LAND_ENEMY)
	{
		pugi::xml_node OfficerSkeleton = data.append_child("OfficerSkeleton");;
		OfficerSkeleton.append_child("position").append_attribute("x") = position.x;
		OfficerSkeleton.child("position").append_attribute("y") = position.y;
	}
	else if (type == entityType::FLYING_ENEMY)
	{
		pugi::xml_node JrGargoyle = data.append_child("JrGargoyle");;
		JrGargoyle.append_child("position").append_attribute("x") = position.x;
		JrGargoyle.child("position").append_attribute("y") = position.y;
	}
	return ret;
}


bool Enemy::Load(pugi::xml_node &data)
{
	bool ret = true;
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();
	return ret;
}