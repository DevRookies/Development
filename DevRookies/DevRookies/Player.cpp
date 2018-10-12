#include "Player.h"
#include "DevRookiesApp.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "p2Log.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Scene2.h"

Player::Player() {
	name.create("player");
}

Player::Player(const float &x, const float &y)
{
	position.x = x;
	position.y = y;
	name.create("player");
}

Player::~Player() {}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Character");
	bool ret = true;

	texture = config.child("texture").child_value();
	speed = { config.child("speed").attribute("x").as_float(),  config.child("speed").attribute("y").as_float() };
	acceleration = { config.child("acceleration").attribute("x").as_float(), config.child("acceleration").attribute("y").as_float() };
	max_speed = { config.child("max_speed").attribute("x").as_float() , config.child("max_speed").attribute("y").as_float() };
	jump_speed = config.child("jump_speed").attribute("value").as_int();
	max_jump_speed = config.child("max_jump_speed").attribute("value").as_int();
	jump_fx_name = config.child("jump_fx_name").attribute("source").as_string();
	dead_fx_name = config.child("dead_fx_name").attribute("source").as_string();

	//FIRE
	idlefire.PushBack({ 2021, 0, 55, 56 });
	idlefire.PushBack({ 2077, 0, 56, 56 });
	idlefire.PushBack({ 2133, 0, 55, 56 });
	idlefire.PushBack({ 2189, 0, 55, 56 });
	idlefire.speed = 0.1f;
	idlefire.loop = true;

	runfire.PushBack({ 2065, 58, 59, 55 });
	runfire.PushBack({ 2125, 58, 59, 55 });
	runfire.PushBack({ 2184, 58, 60, 57 });
	runfire.PushBack({ 2125, 58, 59, 55 });
	runfire.speed = 0.2f;
	runfire.loop = true;

	jumpfire.PushBack({ 2184, 58, 60, 57 });

	deadfire.PushBack({ 2191, 384, 53, 63 });
	deadfire.PushBack({ 2131, 384, 59, 63 });
	deadfire.PushBack({ 2070, 384, 60, 63 });
	deadfire.PushBack({ 2009, 384, 60, 63 });
	deadfire.speed = 0.2f;
	deadfire.loop = false;

	//ICE
	idleice.PushBack({ 1797, 0, 55, 56 });
	idleice.PushBack({ 1853, 0, 56, 56 });
	idleice.PushBack({ 1909, 0, 55, 56 });
	idleice.PushBack({ 1965, 0, 55, 56 });
	idleice.speed = 0.1f;
	idleice.loop = true;

	runice.PushBack({ 1885, 58, 59, 56 });
	runice.PushBack({ 1945, 58, 59, 56 });
	runice.PushBack({ 2004, 58, 60, 57 });
	runice.PushBack({ 1945, 58, 59, 56 });
	runice.speed = 0.2f;
	runice.loop = true;

	jumpice.PushBack({ 2004, 58, 60, 57 });

	deadice.PushBack({ 1954, 384, 53, 63 });
	deadice.PushBack({ 1894, 384, 59, 63 });
	deadice.PushBack({ 1834, 384, 60, 63 });
	deadice.PushBack({ 1773, 384, 60, 63 });
	deadice.speed = 0.1f;
	deadice.loop = false;


	return ret;

}

bool Player::Start(ELEMENT element)
{
	App->audio->LoadFx(jump_fx_name.GetString());
	App->audio->LoadFx(dead_fx_name.GetString());
	current_state = AIR;
	player_texture = App->tex->Load(texture.GetString());
	current_element = element;
	if(element == FIRE)current_animation = &idlefire;
	else current_animation = &idleice;
	
	return true;
}

bool Player::PreUpdate()
{
	if (current_state != DEATH) {
		current_movement = IDLE;

		if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
			GodMode = !GodMode;


		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (current_movement != RIGHT)App->player->current_movement = LEFT;
			else current_movement = IDLE;
		}


		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (current_movement != LEFT)App->player->current_movement = RIGHT;
			else current_movement = IDLE;
		}


		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			if (current_state == FLOOR)
			{
				App->player->current_movement = JUMP;
				AddFX(1, 0);
			}
		}


		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			App->player->current_element = FIRE;

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			App->player->current_element = ICE;
	}
	

	return true;
}

bool Player::Update(float dt)
{
	if (current_state != DEATH) {
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
				speed.x = acceleration.x * -max_speed.x + (1 - acceleration.x) * speed.x;
				flipX = true;
				break;
			case RIGHT:
				current_animation = &runfire;
				speed.x = acceleration.x * max_speed.x + (1 - acceleration.x) * speed.x;
				flipX = false;
				break;
			case JUMP:
				current_animation = &jumpfire;
				speed.y = jump_speed * -max_jump_speed + (1 - jump_speed) * speed.y;
				current_state = AIR;
				
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
				speed.x = acceleration.x * -max_speed.x + (1 - acceleration.x) * speed.x;
				flipX = true;
				break;
			case RIGHT:
				current_animation = &runice;
				speed.x = acceleration.x * max_speed.x + (1 - acceleration.x) * speed.x;
				flipX = false;
				break;
			case JUMP:
				current_animation = &jumpice;
				speed.y = jump_speed * -max_jump_speed + (1 - jump_speed) * speed.y;
				current_state = AIR;
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

		if (current_state == AIR)
		{
			speed.y = acceleration.y * max_speed.y + (1 - acceleration.y) * speed.y;
		}

		position += speed;
	}
	
	collider->SetPos(position.x, position.y + 48);
	return true;
}

bool Player::PostUpdate()
{
	App->render->Blit(player_texture, position.x, position.y, &current_animation->GetCurrentFrame(), 1.0f, flipX);
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
	

	if (collider2->type == COLLIDER_ICE){
		if (current_element == FIRE) 
			Die();
		else 
			current_state = FLOOR;
	}

	if (collider2->type == COLLIDER_FIRE){
		if (current_element == ICE) 
			Die();
		else 
			current_state = FLOOR;
	}
	
	if (collider2->type == COLLIDER_FINAL)
		Win();

	if (collider2->type == COLLIDER_POISON)
		Die();

	if (App->render->camera.x <= -position.x) {
		Die();
	}
	

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
		speed.x = 0;
		return;
	}
	position.x += (speed.x * 2);
	collider->SetPos(position.x, position.y);
	if (!collider1->CheckCollision(collider2->rect))
	{
		speed.x = 0;
		return;
	}
	position.x -= speed.x;
	collider->SetPos(position.x, position.y);

}

void Player::AddColliderPlayer()  {
	collider = App->collision->AddCollider({ 0,0,55, 8 }, COLLIDER_PLAYER, this);
}

void Player::Die() {

	if (!GodMode) {
		position.y -= 7; //because the collider is 7 pixels less than dead animation
		current_state = DEATH;
		AddFX(2, 0);
		if (current_element == FIRE) {
			current_animation = &deadfire;
		}
		else {
			current_animation = &deadice;
		}
			
		if (App->scene->active) 
			App->scenemanager->FadeToBlack(App->scene, App->scene);
		else
			App->scenemanager->FadeToBlack(App->scene2, App->scene2);

		
			
	}
}

void Player::Win() {

	AddFX(2, 0);
	if (current_element == FIRE) {
		current_animation = &idlefire;
	}
	else {
		current_animation = &idleice;
	}
	App->scenemanager->FadeToBlack(App->scene, App->scene2);

}

void Player::AddFX(int channel, int repeat)
{
	App->audio->PlayFx(channel, repeat);
}

