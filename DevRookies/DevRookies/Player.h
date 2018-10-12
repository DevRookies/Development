#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Collision.h"


enum MOVEMENT { IDLE, LEFT, RIGHT, JUMP, DEAD };
enum STATE { FLOOR, AIR, DEATH };
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
	Animation	idleice;
	Animation	runice;
	Animation	jumpice;
	Animation	deadice;
	Collider*	collider = nullptr;

	int			jumpSpeed, maxJumpSpeed;
	fPoint		position, lastPosition, speed, acceleration, maxSpeed;
	p2SString   texture;
	p2SString	jump_fx_name;
	p2SString	dead_fx_name;

	bool		GodMode = false;

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

	fPoint		GetPosition();
	void		SetPosition(const float &x, const float &y);
	void		OnCollision(Collider* collider1, Collider* collider2);
	void		AddColliderPlayer();
	void		Die();

	void AddFX(int channel, int repeat);

	MOVEMENT	current_movement = IDLE;
	STATE		current_state = FLOOR;
	ELEMENT		current_element = FIRE;

	

	
};

#endif // __PLAYER_H__