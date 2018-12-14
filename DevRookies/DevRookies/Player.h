#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Entity.h"

struct player_info;

enum GODMOVE {IDLEGOD, DOWNGOD, UPGOD};
enum ELEMENT { FIRE, ICE };

class Player : public Entity
{
private:

	Animation	idlefire, runfire, jumpfire, deadfire, hitfire;
	Animation	idleice, runice, jumpice, deadice, hitice;
	Animation	godmode_anim;

	int			hit_speed, jump_cont, jump_cont_start;
	int			collider_box_width, collider_box_height;
	fPoint		lastPosition;
	p2SString   player_texture, jump_fx_name, dash_fx_name, dead_fx_name, victory_fx_name;

	uint		heigth_animation = 53;
	
	
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
	
	//Destructor
	~Player();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start(uint i);

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
	void		OnCollision(Collider* collider1);
	void		AddColliderPlayer();
	void		Restart(ELEMENT element);
	bool		isDead();
	
	void		AddFX(const int channel, const int repeat) const;
	bool		LoadAnimation(pugi::xml_node &node, Animation &anim);

	GODMOVE		current_godmove = IDLEGOD;
	STATE		current_state = FLOOR;
	ELEMENT		current_element = FIRE;

	bool		godmode = false;
	bool		visibility = true;
	int			coin_counter =0;
	int			lifes = 3;
};

#endif // __PLAYER_H__