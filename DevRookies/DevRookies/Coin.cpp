#include "Coin.h"
#include "Collision.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "EntityManager.h"
#include "Map.h"

Coin::Coin(entityType type) :Entity(type)
{
}

Coin::~Coin() 
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Coin::Awake(pugi::xml_node& conf)
{
	bool ret = true;

	pugi::xml_node config = conf.child("Coin");
	coin_texture = config.child("texture").child_value();

	LoadAnimation(config.child("animations").child("flip").child("frame"), flip);
	flip.speed = config.child("animations").child("flip").attribute("speed").as_float();
	flip.loop = config.child("animations").child("flip").attribute("loop").as_bool();

	return ret;
}

bool Coin::Start(uint i)
{
	//FX
	return true;
}

bool Coin::Update(float dt)
{
	bool ret = true;

	current_animation = &flip;

	current = current_animation->GetCurrentFrame(dt);

	return ret;
}

bool Coin::PostUpdate()
{
	if (visibility)
		App->render->Blit(coin_tex, position.x, position.y, &current, 1.0f, flipX);
	return true;
}

bool Coin::CleanUp()
{
	App->textures->UnLoad(coin_tex);
	coin_tex = nullptr;
	collider->to_delete = true;
	visibility = false;
	return true;
}

bool Coin::Load(pugi::xml_node& node)
{
	bool ret = true;

	position.x = node.child("position").attribute("x").as_float(0);
	position.y = node.child("position").attribute("y").as_float(0);

	return ret;
}

bool Coin::Save(pugi::xml_node& node) const
{
	bool ret = true;

	if (coin_tex != nullptr) {
		pugi::xml_node pos = node.append_child("position");
		pos.append_attribute("x") = position.x;
		pos.append_attribute("y") = position.y;
	}

	return ret;
}

void Coin::OnCollision(Collider* collider1, Collider* collider2)
{
	if (collider1->type == COLLIDER_PLAYER) 
		CleanUp();
		
}

bool Coin::Restart(uint i)
{
	coin_tex = App->textures->Load(coin_texture.GetString());
	position = App->map->init_Coin_position.At(i - App->map->init_Coin_position.count() - 1)->data;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y,25,24 }, COLLIDER_COIN, App->entitymanager);
	flipX = false;
	visibility = true;
	return true;
}

bool Coin::LoadAnimation(pugi::xml_node &node, Animation &anim) {

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