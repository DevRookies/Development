#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

enum MOVEMENT { IDLE, RIGHT, LEFT, UP, DOWN };
enum STATE { ONFLOOR, AIR, DEATH };
enum ELEMENT { FIRE, ICE };

class Player :
	public Module
{
private:
	fPoint position, lastPosition;
	fPoint speed;

	MOVEMENT* current_movement = nullptr;
	STATE* current_state = nullptr;
	ELEMENT* current_element = nullptr;

	Animation* current_animation = nullptr;
	Animation idle;
	Animation run;

public:
	Player();
	Player(const float &x, const float &y);
	~Player();

	fPoint GetPosition();
	void SetPosition(const float &x, const float &y);

	MOVEMENT GetMovement();
	void SetMovement(MOVEMENT &s);

	STATE GetState();
	void SetState(STATE &s);

	ELEMENT GetElement();
	void SetElement(ELEMENT &s);

};

#endif // __PLAYER_H__