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

	idlefire.PushBack({ 2021, 0, 55, 56 });
	idlefire.speed = 0.2F;
	idlefire.loop = true;

	runfire.PushBack({ 0, 0, 0, 0 });
	runfire.speed = 0.2F;
	runfire.loop = true;

	jumpfire.PushBack({ 0, 0, 0, 0 });
	jumpfire.speed = 0.2F;
	jumpfire.loop = false;

	deadfire.PushBack({ 0, 0, 0, 0 });
	deadfire.speed = 0.2F;
	deadfire.loop = false;

	

	AddColliderPlayer();

	return ret;

}

bool Player::Start()
{
	speed = { 0, 0 };
	player_texture = App->tex->Load("textures/character.png");
	current_animation = &idlefire;
	return true;
}

bool Player::PreUpdate()
{
	current_movement = IDLE;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		App->player->current_movement = LEFT;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		App->player->current_movement = RIGHT;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->player->current_movement = JUMP;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		App->player->current_element = FIRE;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->player->current_element = ICE;

	return true;
}

bool Player::Update(float dt)
{
	switch (current_element)
	{
	case FIRE:
		switch (current_movement)
		{
		case IDLE:
			current_animation = &idlefire;
			speed.x = 0;
			break;
		case LEFT:
			current_animation = &runfire;
			speed.x = speed_left;
			break;
		case RIGHT:
			current_animation = &runfire;
			speed.x = speed_right;
			break;
		case JUMP:
			current_animation = &jumpfire;
			speed.y = speed_jump;
			break;
		case DEAD:
			current_animation = &deadfire;
			break;
		default:
			break;
		}
		break;
	case ICE:
		switch (current_movement)
		{
		case IDLE:
			current_animation = &idleice;
			speed.x = 0;
			break;
		case LEFT:
			current_animation = &runice;
			speed.x = speed_left;
			break;
		case RIGHT:
			current_animation = &runice;
			speed.x = speed_right;
			break;
		case JUMP:
			current_animation = &jumpice;
			speed.y = speed_jump;
			break;
		case DEAD:
			current_animation = &deadice;
			break;
		default:
			break;
		}
		break;
	default:
		break;
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

void Player::AddColliderPlayer()  {
	collider = App->collision->AddCollider({ 0,0,55, 56 }, COLLIDER_PLAYER, this);
}

