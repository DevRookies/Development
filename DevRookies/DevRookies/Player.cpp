#include "Player.h"
#include "DevRookiesApp.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "p2Log.h"

Player::Player() {}

Player::Player(const float &x, const float &y)
{
	position.x = x;
	position.y = y;
}

Player::~Player() {}

bool Player::Awake(pugi::xml_node&)
{
	LOG("Loading Character");
	bool ret = true;

	idle.PushBack({ 19, 31, 46, 44 });

	run.PushBack({ 97, 30, 50, 45 });
	run.PushBack({ 176, 30, 50, 45 });
	run.PushBack({ 256, 31, 50, 45 });
	run.PushBack({ 336, 29, 50, 45 });
	run.PushBack({ 415, 29, 50, 45 });
	run.PushBack({ 495, 30, 50, 45 });
	run.PushBack({ 576, 31, 50, 45 });
	run.PushBack({ 653, 31, 50, 45 });
	run.speed = 0.2F;
	run.loop = true;

	collider = App->collision->AddCollider({ 0,0,46,44 }, COLLIDER_PLAYER, this);



	return ret;

}

bool Player::Start()
{
	speed = { 0, 0 };
	player_texture = App->tex->Load("textures/testcharacter.png");
	current_animation = &idle;
	return true;
}

bool Player::PreUpdate()
{
	current_movement = IDLE;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		App->player->current_movement = RIGHT;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		App->player->current_movement = LEFT;

	return true;
}

bool Player::Update(float dt)
{
	if (current_movement == IDLE)
	{
		current_animation = &idle;
		speed.x = 0;
	}
	else if (current_movement == RIGHT)
	{
		current_animation = &run;
		speed.x = speed_right;
	}
	else if (current_movement == LEFT)
	{
		current_animation = &run;
		speed.x = speed_left;
	}
	speed.y = gravity;

	position += speed;
	collider->SetPos(position.x, position.y);
	return true;
}

bool Player::PostUpdate()
{
	App->render->Blit(player_texture, position.x, position.y, &current_animation->GetCurrentFrame());
	return true;
}

bool Player::CleanUp()
{
	App->tex->UnLoad(player_texture);
	player_texture = nullptr;

	return true;
}

//Getters---------------------------------
fPoint Player::GetPosition()
{
	return fPoint();
}

//Setters------------------------------------
void Player::SetPosition(const float & x, const float & y)
{
	position.x = x;
	position.y = y;
}

//----------------------------------------------------
void Player::OnCollision(Collider * collider1, Collider * collider2)
{
	position.y -= speed.y;
	collider->SetPos(position.x, position.y);
	if (!collider1->CheckCollision(collider2->rect))
	{
		return;
	}
	position.y += (speed.y * 2);
	collider->SetPos(position.x, position.y);
	if (!collider1->CheckCollision(collider2->rect))
	{
		return;
	}
	position.y -= speed.y;
	position.x -= speed.x;
	collider->SetPos(position.x, position.y);
	if (!collider1->CheckCollision(collider2->rect))
	{
		return;
	}
	position.x += (speed.x * 2);
	collider->SetPos(position.x, position.y);
	if (!collider1->CheckCollision(collider2->rect))
	{
		return;
	}
	position.x -= speed.x;
	collider->SetPos(position.x, position.y);

}