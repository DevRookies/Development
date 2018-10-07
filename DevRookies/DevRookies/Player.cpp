#include "Player.h"



Player::Player() {}

Player::Player(const float &x, const float &y)
{
	position.x = x;
	position.y = y;
}

Player::~Player() {}

fPoint Player::GetPosition()
{
	return fPoint();
}

void Player::SetPosition(const float & x, const float & y)
{
	position.x = x;
	position.y = y;
}

MOVEMENT Player::GetMovement()
{
	return MOVEMENT();
}

void Player::SetMovement(MOVEMENT &s)
{
	current_movement = &s;
}

STATE Player::GetState()
{
	return STATE();
}

void Player::SetState(STATE &s)
{
	current_state = &s;
}

ELEMENT Player::GetElement()
{
	return ELEMENT();
}

void Player::SetElement(ELEMENT &s)
{
	current_element = &s;
}