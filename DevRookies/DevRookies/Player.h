#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Collision.h"


enum MOVEMENT { IDLE, LEFT, RIGHT, JUMP, DEAD };
enum STATE { ONFLOOR, AIR, DEATH };
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

	uint		gravity = 1;
	uint		speed_jump = 5;
	uint		speed_right = 3;
	int			speed_left = -3;

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

	MOVEMENT	current_movement = IDLE;
	STATE		current_state = ONFLOOR;
	ELEMENT		current_element = FIRE;

	fPoint		position, lastPosition, speed;

	
};

#endif // __PLAYER_H__