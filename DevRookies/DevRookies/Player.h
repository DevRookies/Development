#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Collision.h"
#include "Entity.h"
#include "EntityManager.h"


enum MOVEMENT { IDLE, LEFT, RIGHT, JUMP, DEAD, LEFT_HIT, RIGHT_HIT };
enum GODMOVE {IDLEGOD, DOWN, UP};
enum STATE { FLOOR, AIR, DEATH, WIN};
enum ELEMENT { FIRE, ICE };

class Player : public Entity
{
private:
	SDL_Texture * player_tex = nullptr;
	SDL_Texture*  godmode_tex = nullptr;
	SDL_Texture*  pause_tex = nullptr;
	Animation*	current_animation = nullptr;
	Animation	idlefire, runfire, jumpfire, deadfire, hitfire;
	Animation	idleice, runice, jumpice, deadice, hitice;
	Animation	godmode_anim;
	Collider*	collider = nullptr;

	bool		flipX = false;
	int			jump_speed, hit_speed;
	int			collider_box_width, collider_box_height;
	fPoint		position, lastPosition, speed, acceleration, max_speed, godmode_pos, pause_pos;
	p2SString   player_texture, godmode_texture, pause_texture, jump_fx_name, dead_fx_name, victory_fx_name;

	bool		godmode = false;
	uint		heigth_animation = 53;
	uint		scene = 1;
	
	void		PreMove();
	void		Move();
	void		Walk();
	void		Hit();
	void		Jump();
	void		GodMove();
	void		Die();
	void		Win();

public:

	Player(entityType type);
	Player(entityType type, const float &x, const float &y);
	
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

	fPoint		GetPosition() const;
	void		SetPosition(const float &x, const float &y);
	void		OnCollision(Collider* collider1, Collider* collider2);
	void		AddColliderPlayer();
	void		Restart(ELEMENT element);
	
	void		AddFX(const int channel, const int repeat) const;
	bool		LoadAnimation(pugi::xml_node &node, Animation &anim);

	MOVEMENT	current_movement = IDLE;
	GODMOVE		current_godmove = IDLEGOD;
	STATE		current_state = FLOOR;
	ELEMENT		current_element = FIRE;

	bool		visibility = true;

};

#endif // __PLAYER_H__