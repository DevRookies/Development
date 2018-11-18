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

const Collider* Enemy::GetCollider() const
{
	return collider;
}

bool Enemy::Save(pugi::xml_node &data) const
{
	return false;
}


bool Enemy::Load(pugi::xml_node &data)
{
	return false;
}