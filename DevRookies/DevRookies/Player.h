#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Collision.h"


enum MOVEMENT { IDLE, LEFT, RIGHT, JUMP, DEAD, LEFT_HIT, RIGHT_HIT };
enum STATE { FLOOR, AIR, DEATH};
enum ELEMENT { FIRE, ICE };

class Player :
	public Module
{
private:
	SDL_Texture * player_texture;
	
	Animation*	current_animation = nullptr;
	Animation	idlefire;
	Animation	runfire;
	Animation	jumpfire;
	Animation	deadfire;
	Animation	hitfire;
	Animation	idleice;
	Animation	runice;
	Animation	jumpice;
	Animation	deadice;
	Animation	hitice;
	Collider*	collider = nullptr;

	bool		flipX = false;
	int			jump_speed, hit_speed;
	fPoint		position, lastPosition, speed, acceleration, max_speed;
	p2SString   texture;
	p2SString	jump_fx_name;
	p2SString	dead_fx_name;
	p2SString	victory_fx_name;

	bool		god_mode = false;
	bool		aux_god_mode = false;
	uint		heigth_animation = 48;
	uint		heigth_dead_animation = 7;
	uint		scene = 1;

	void		PreMove();
	void		Move();
	void		Jump();
	void		Walk();
	void		Hit();
	void		Die();
	void		Win();

public:

	Player();
	Player(const float &x, const float &y);
	
	//Destructor
	~Player();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Save and Load
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	fPoint		GetPosition();
	void		SetPosition(const float &x, const float &y);
	void		OnCollision(Collider* collider1, Collider* collider2);
	void		AddColliderPlayer();
	
	void		AddFX(const int channel, const int repeat) const;
	bool		LoadAnimation(pugi::xml_node &node, Animation &anim);

	MOVEMENT	current_movement = IDLE;
	STATE		current_state = FLOOR;
	ELEMENT		current_element = FIRE;

};

#endif // __PLAYER_H__