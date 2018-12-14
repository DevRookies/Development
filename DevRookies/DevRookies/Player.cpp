#include "Player.h"
#include "DevRookiesApp.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "p2Log.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Map.h"
#include "Window.h"
#include "EntityManager.h"

Player::Player(entityType type):Entity(type)
{
}

Player::~Player() {}

bool Player::Awake(pugi::xml_node& conf)
{
	
	bool ret = true;
	pugi::xml_node config = conf.child("player");
	player_texture = config.child("texture").child_value();
	position = { config.child("position").attribute("x").as_float(),  config.child("position").attribute("y").as_float() };
	collider_box_width = config.child("collider").attribute("width").as_int();
	collider_box_height = config.child("collider").attribute("height").as_int();
	speed = { config.child("speed").attribute("x").as_float(),  config.child("speed").attribute("y").as_float() };
	acceleration = { config.child("acceleration").attribute("x").as_float(), config.child("acceleration").attribute("y").as_float() };
	max_speed = { config.child("max_speed").attribute("x").as_float() , config.child("max_speed").attribute("y").as_float() };
	jump_cont_start = config.child("jump_cont_start").attribute("value").as_int();
	hit_speed = config.child("hit_speed").attribute("value").as_int();
	jump_fx_name = config.child("jump_fx_name").attribute("source").as_string();
	dash_fx_name = config.child("dash_fx_name").attribute("source").as_string();
	dead_fx_name = config.child("dead_fx_name").attribute("source").as_string();
	victory_fx_name = config.child("victory_fx_name").attribute("source").as_string();

	//animations
	//fire
	LoadAnimation(config.child("animations").child("idle_fire").child("frame"), idlefire);
	idlefire.speed = config.child("animations").child("idle_fire").attribute("speed").as_float();
	idlefire.loop = config.child("animations").child("idle_fire").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("run_fire").child("frame"), runfire);
	runfire.speed = config.child("animations").child("run_fire").attribute("speed").as_float();
	runfire.loop = config.child("animations").child("run_fire").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("jump_fire").child("frame"), jumpfire);

	LoadAnimation(config.child("animations").child("die_fire").child("frame"), deadfire);
	deadfire.speed = config.child("animations").child("die_fire").attribute("speed").as_float();
	deadfire.loop = config.child("animations").child("die_fire").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("hit_fire").child("frame"), hitfire);
	hitfire.speed = config.child("animations").child("hit_fire").attribute("speed").as_float();
	hitfire.loop = config.child("animations").child("hit_fire").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("godmode").child("frame"), godmode_anim);
	godmode_anim.speed = config.child("animations").child("godmode").attribute("speed").as_float();
	godmode_anim.loop = config.child("animations").child("godmode").attribute("loop").as_bool();

	//ice
	LoadAnimation(config.child("animations").child("idle_ice").child("frame"), idleice);
	idleice.speed = config.child("animations").child("idle_ice").attribute("speed").as_float();
	idleice.loop = config.child("animations").child("idle_ice").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("run_ice").child("frame"), runice);
	runice.speed = config.child("animations").child("run_ice").attribute("speed").as_float();
	runice.loop = config.child("animations").child("run_ice").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("jump_ice").child("frame"), jumpice);

	LoadAnimation(config.child("animations").child("die_ice").child("frame"), deadice);
	deadice.speed = config.child("animations").child("die_ice").attribute("speed").as_float();
	deadice.loop = config.child("animations").child("die_ice").attribute("loop").as_bool();

	LoadAnimation(config.child("animations").child("hit_ice").child("frame"), hitice);
	hitice.speed = config.child("animations").child("hit_ice").attribute("speed").as_float();
	hitice.loop = config.child("animations").child("hit_ice").attribute("loop").as_bool();

	return ret;

}

bool Player::Start(uint i)
{
	App->audio->LoadFx(jump_fx_name.GetString());
	App->audio->LoadFx(dash_fx_name.GetString());
	App->audio->LoadFx(dead_fx_name.GetString());
	App->audio->LoadFx(victory_fx_name.GetString());	
	
	
	return true;
}

bool Player::PreUpdate()
{

	if (current_state != DEATH && App->scenemanager->current_step == App->scenemanager->none && App->render->start_time == 0)
		PreMove();
	
	return true;
}

bool Player::Update(float dt)
{
	if (current_state != DEATH && App->scenemanager->current_step == App->scenemanager->none && App->render->start_time == 0) {
		Move();
	}

	if (current_animation->GetCurrentFrameIndex() == 3 && (current_state == DEATH)) {
		if (lifes > 0) {
			App->scene->Restart();
		}
		else if (lifes == 0) {
			App->scene->scene_actual = 0;
			App->scene->Restart();
		}
			
	}

	speed.y = floor(speed.y * dt);
	float distance = App->collision->CollisionCorrectionDown(collider->rect) + 0.5f;
	if (distance <= speed.y)
	{
		speed.y = distance;
	}
	speed.x = floor(speed.x * dt);

	if (App->scene->scene_actual == 0)
		speed.x = 0;

	position += speed;
	
	current = current_animation->GetCurrentFrame(dt);
	collider->SetPos(position.x, position.y + heigth_animation - collider_box_height);

	return true;
}

bool Player::PostUpdate()
{
	if (visibility) {
		App->render->Blit(texture, position.x, position.y, &current, 1.0f, flipX);
	}
	return true;
}

bool Player::CleanUp()
{
	App->textures->UnLoad(texture);
	texture = nullptr;
	

	return true;
}

bool Player::Load(pugi::xml_node& node)
{
	bool ret = true;
	
	position.x = node.child("position").attribute("x").as_float(0);
	position.y = node.child("position").attribute("y").as_float(0);
	godmode = node.child("godmode").attribute("value").as_bool(false);
	current_element = (ELEMENT)node.child("element").attribute("value").as_int(0);
	flipX = node.child("flipX").attribute("value").as_bool(false);
	
	return ret;
}

bool Player::Save(pugi::xml_node& node) const
{
	bool ret = true;
	pugi::xml_node pos = node.append_child("position");
	pos.append_attribute("x") = position.x;
	pos.append_attribute("y") = position.y;
	node.append_child("godmode").append_attribute("value") = godmode;
	node.append_child("element").append_attribute("value") = (int)current_element;
	node.append_child("flipX").append_attribute("value") = flipX;

	return ret;
}

//Getters---------------------------------
fPoint Player::GetPosition() const
{
	return fPoint();
}

//Setters------------------------------------
void Player::SetPosition(const float & x, const float & y)
{
	position.x = x;
	position.y = y;
}

//Collider-----------------
void Player::AddColliderPlayer() {
	collider = App->collision->AddCollider({ 0, 0,collider_box_width, collider_box_height }, COLLIDER_PLAYER, App->entitymanager);
}

//----------------------------------------------------
void Player::OnCollision(Collider * collider1)
{
	if (App->scene->scene_actual != 0) 
	{
		if (collider1->type == COLLIDER_FINAL)
			Win();

		if (!godmode) {
			if (collider1->type == COLLIDER_ICE) {
				current_state = FLOOR;
				SetPosition(position.x, collider1->rect.y - collider_box_height);
				if (current_element == FIRE)
					Die();
			}
			else if (collider1->type == COLLIDER_FIRE) {
				current_state = FLOOR;
				SetPosition(position.x, collider1->rect.y - collider_box_height);
				if (current_element == ICE)
					Die();
			}
			else if (collider1->type == COLLIDER_POISON) {
				current_state = FLOOR;
				Die();
			}
			else if (collider1->type == COLLIDER_ENEMY)
				if (current_movement != LEFT_HIT && current_movement != RIGHT_HIT)
					Die();
				else
					App->entitymanager->OnCollision(App->entitymanager->player->collider, collider1);
			else if (collider1->type == COLLIDER_COIN) {
				App->entitymanager->OnCollision(App->entitymanager->player->collider, collider1);
				++coin_counter;
				App->scene->HUDUpdate();
				LOG("COINS: %i", coin_counter);
			}

			if (App->render->camera.x <= -position.x || collider1->type == COLLIDER_BORDER) {
				Die();
			}
		}
	}
	
}

void Player::AddFX(const int channel , const int repeat) const
{
	App->audio->PlayFx(channel, repeat);
}

//LoadAnimation with LoadCollider structure
bool Player::LoadAnimation(pugi::xml_node &node, Animation &anim) {
	
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

void Player::PreMove() {

	

	if (current_animation->GetCurrentFrameIndex() == 11 || (current_animation != &hitfire && current_animation != &hitice)) {
		
		if (App->collision->CheckCollision()) {
			if (current_state != DEATH)
				current_state = FLOOR;
		}
		else
			current_state = AIR;

		current_movement = IDLE;
		current_godmove = IDLEGOD;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			if (current_movement != RIGHT) 
				current_movement = LEFT;
			else 
				current_movement = IDLE;
		
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			if (current_movement != LEFT) 
				current_movement = RIGHT;
			else 
				current_movement = IDLE;

		if (godmode) {
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
				if (current_godmove != UPGOD)
					current_godmove = DOWNGOD;
				else
					current_godmove = IDLEGOD;

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
				if (current_godmove != DOWNGOD)
					current_godmove = UPGOD;
				else
					current_godmove = IDLEGOD;
		}
		else{
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				if (current_element == FIRE)
					current_element = ICE;
				else
					current_element = FIRE;

			if (current_state == FLOOR) {
				if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
					current_movement = UP;

				if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN && flipX) {
					current_movement = LEFT_HIT;
					hitfire.setCurrentFrameIndex(0);
					hitice.setCurrentFrameIndex(0);
					AddFX(3, 0);
				}

				if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN && !flipX) {
					current_movement = RIGHT_HIT;
					hitfire.setCurrentFrameIndex(0);
					hitice.setCurrentFrameIndex(0);
					AddFX(3, 0);
				}
			}
			
		}
	
	}


	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		godmode = !godmode;
		
}

void Player::Move() {

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
		case RIGHT:
			current_animation = &runfire;
			Walk();
			break;
		case LEFT_HIT:
		case RIGHT_HIT:
			current_animation = &hitfire;
			Hit();
			break;
		case UP:
			current_animation = &jumpfire;
			Jump();
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
		case RIGHT:
			current_animation = &runice;
			Walk();
			break;
		case LEFT_HIT:
		case RIGHT_HIT:
			current_animation = &hitice;
			Hit();
			break;
		case UP:
			current_animation = &jumpice;
			Jump();
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
	
	
	if (!godmode) {
		if (current_state == AIR) {
			if (current_element == FIRE)
				current_animation = &jumpfire;
			else
				current_animation = &jumpice;

			if (jump_cont > 0) {
				speed.y = acceleration.y * -max_speed.y + (1 - acceleration.y) * -speed.y;
				jump_cont--;
			}
			else
				speed.y = acceleration.y * max_speed.y + (1 - acceleration.y) * speed.y;
		}
	}
	else {
		current_animation = &godmode_anim;
		GodMove();
	}
}

void Player::Walk()
{
	if (current_movement == LEFT)
	{
		speed.x = acceleration.x * -max_speed.x + (1 - acceleration.x) * -speed.x;
		flipX = true;
	}
	else
	{
		speed.x = acceleration.x * max_speed.x + (1 - acceleration.x) * speed.x;
		flipX = false;
	}
}

void Player::Hit()
{
	if (current_movement == LEFT_HIT) {
		speed.x = acceleration.x * -hit_speed + (1 - acceleration.x) * -speed.x;
		flipX = true;
	}
	else{
		speed.x = acceleration.x * hit_speed + (1 - acceleration.x) * speed.x;
		flipX = false;
	}
}

void Player::Jump() 
{
	jump_cont = jump_cont_start;
	current_state = AIR;
	AddFX(2, 0);
}

void Player::GodMove()
{
	if (current_godmove == DOWNGOD)
		speed.y = acceleration.y * max_speed.y + (1 - acceleration.y) * speed.y;
	else if (current_godmove == UPGOD)
		speed.y = acceleration.y * -max_speed.y + (1 - acceleration.y) * -speed.y;
	else
		speed.y = 0;
}

//When player dies--------
void Player::Die() {

	if (!godmode) {
		AddFX(4, 0);
		current_state = DEATH;
		if (current_element == FIRE) {
			current_animation = &deadfire;
		}
		else {
			current_animation = &deadice;
		}
		--lifes;
		App->scene->HUDUpdate();
		LOG("LIFES: %i", lifes);
	}
}

//When player wins--------
void Player::Win() {

	AddFX(5, 0);
	current_state = WIN;
	if (current_element == FIRE)
		current_animation = &idlefire;
	else
		current_animation = &idleice;

	if (App->scene->scene_actual == 1)
		App->scene->scene_actual = 2;
	else
		App->scene->scene_actual = 1;

	App->scene->Restart();
}

void Player::Restart(ELEMENT element)
{
	texture = App->textures->Load(player_texture.GetString());
	current_state = FLOOR;
	current_movement = IDLE;
	current_element = element;

	if (element == FIRE)
		current_animation = &idlefire;
	else
		current_animation = &idleice;

	AddColliderPlayer();
	SetPosition(App->map->init_player_position.x, App->map->init_player_position.y);
	speed.x = 0;
	speed.y = 0;
	flipX = false;
	visibility = true;
	deadfire.Reset();
	deadice.Reset();
}

bool Player::isDead()
{
	bool ret = false;
	if (current_state == DEATH)
		ret = true;
	return ret;
}