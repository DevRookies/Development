#include "DevRookiesApp.h"
#include "Enemy.h"
#include "Collision.h"
#include "Render.h"

Enemy::Enemy(TYPE type)
{
}

Enemy::Enemy(TYPE type, iPoint pos)
{
	position.x = pos.x;
	position.y = pos.y;

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
}

void Enemy::Save(pugi::xml_node &data) const
{
	if (type == LAND_ENEMY)
	{
		pugi::xml_node OfficerSkeleton = data.append_child("OfficerSkeleton");;
		OfficerSkeleton.append_child("position").append_attribute("x") = position.x;
		OfficerSkeleton.child("position").append_attribute("y") = position.y;
	}
	else if (type == FLYING_ENEMY)
	{
		pugi::xml_node JrGargoyle = data.append_child("JrGargoyle");;
		JrGargoyle.append_child("position").append_attribute("x") = position.x;
		JrGargoyle.child("position").append_attribute("y") = position.y;
	}

}

void Enemy::Load(pugi::xml_node &data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();
}