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
	victory_fx_name = config.child("victory_fx_name").attribute("source").as_string();
	volume_fx = config.child("volume_fx").attribute("value").as_uint();

	//animations
	//fire
	LoadAnimation(config.child("animations").child("idle_fire").child("frame"), idlefire);
	idlefire.speed = config.child("animations").child("idle_fire").attribute("speed").as_float();
	idlefire.loop = config.child("animations").child("idle_fire").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("run_fire").child("frame"), runfire);
	runfire.speed = config.child("animations").child("run_fire").attribute("speed").as_float();
	runfire.loop = config.child("animations").child("run_fire").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("jump_fire").child("frame"), jumpfire);

	LoadAnimation(config.child("animations").child("die_fire").child("frame"), deadfire);
	deadfire.speed = config.child("animations").child("die_fire").attribute("speed").as_float();
	deadfire.speed = config.child("animations").child("die_fire").attribute("loop").as_bool(false);

	//ice
	LoadAnimation(config.child("animations").child("idle_ice").child("frame"), idleice);
	idleice.speed = config.child("animations").child("idle_ice").attribute("speed").as_float();
	idleice.loop = config.child("animations").child("idle_ice").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("run_ice").child("frame"), runice);
	runice.speed = config.child("animations").child("run_ice").attribute("speed").as_float();
	runice.loop = config.child("animations").child("run_ice").attribute("loop").as_bool(true);

	LoadAnimation(config.child("animations").child("jump_ice").child("frame"), jumpice);

	LoadAnimation(config.child("animations").child("die_ice").child("frame"), deadice);
	deadice.speed = config.child("animations").child("die_ice").attribute("speed").as_float();
	deadice.speed = config.child("animations").child("die_ice").attribute("loop").as_bool(false);


	/*current_animation = &idlefire;*/

	return ret;

}

bool Player::Start(ELEMENT element)
{
	App->audio->LoadFx(jump_fx_name.GetString());
	App->audio->LoadFx(dead_fx_name.GetString());
	App->audio->LoadFx(victory_fx_name.GetString());
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
				AddFX(1, 0, volume_fx);
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

bool Player::Load(pugi::xml_node& node)
{
	bool ret = true;
	position.x = node.child("position").attribute("x").as_float(0);
	position.y = node.child("position").attribute("y").as_float(0);
	speed.x = node.child("speed").attribute("x").as_float(0);
	speed.y = node.child("speed").attribute("y").as_float(0);
	acceleration.x = node.child("acceleration").attribute("x").as_float(0);
	acceleration.y = node.child("acceleration").attribute("y").as_float(0);
	jump_speed = node.child("jump_speed").attribute("value").as_int(0);

	return ret;
}

bool Player::Save(pugi::xml_node& node) const
{
	bool ret = true;

	pugi::xml_node pos = node.append_child("position");

 	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;

	pugi::xml_node vel = node.append_child("speed");

	vel.append_attribute("x") = speed.x;
	vel.append_attribute("y") = speed.y;

	pugi::xml_node accel = node.append_child("acceleration");

	accel.append_attribute("x") = acceleration.x;
	accel.append_attribute("y") = acceleration.y;

	pugi::xml_node jump_speed = node.append_child("jump_speed");

	jump_speed.append_attribute("value") = jump_speed;

	return ret;
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
		current_state = FLOOR;
		if (current_element == FIRE) 
			Die();
			
	}

	if (collider2->type == COLLIDER_FIRE){
		current_state = FLOOR;
		if (current_element == ICE) 
			Die();
			
	}
	
	if (collider2->type == COLLIDER_FINAL)
		Win();

	if (collider2->type == COLLIDER_POISON) {
		current_state = FLOOR;
		Die();
	}
		

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
		AddFX(2, 0, volume_fx);
		if (current_element == FIRE) {
			current_animation = &deadfire;
		}
		else {
			current_animation = &deadice;
		}
			
		if (App->scene->active) 
			App->scenemanager->FadeToBlack(App->scene, App->scene);
		else if (App->scene2->active) {
			App->scenemanager->FadeToBlack(App->scene2, App->scene2);
		}
		
			
	}
}

void Player::Win() {

	AddFX(3, 0, volume_fx);
	if (current_element == FIRE) {
		current_animation = &idlefire;
	}
	else {
		current_animation = &idleice;
	}

	if (App->scene->active) {
		App->scenemanager->FadeToBlack(App->scene, App->scene2);
	}
	else if (App->scene2->active) {
		App->scenemanager->FadeToBlack(App->scene2, App->scene);
	}

}

void Player::AddFX(int channel, int repeat, uint volume)
{
	App->audio->PlayFx(channel, repeat, volume);
}

//LoadAnimation with LoadCollider structure
bool Player::LoadAnimation(pugi::xml_node &node, Animation &anim) {
	
	for (; node; node = node.next_sibling("frame")) {
	//pugi::xml_node frame;

	//for(frame = node.child("frame"); frame; frame = frame.next_sibling("frame"))
	//{
		SDL_Rect frame_rect;
		frame_rect.x = node.attribute("x").as_int();
		frame_rect.y = node.attribute("y").as_int();
		frame_rect.w = node.attribute("width").as_int();
		frame_rect.h = node.attribute("height").as_int();
		anim.PushBack(frame_rect);
	}
	return true;
}
