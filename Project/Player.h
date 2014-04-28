#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "Constants.h"
#include "AnimationManager.h"

class Player: public AnimationManager
{
public:
	/*
	* \brief Sets up the player and its aniamtion.
	* \param The rate the player moves.
	*/
	Player(float speed);
	/*
	* \brief Deletes all spaces in memory where this object takes.
	*/
	~Player();

	/*
	* \brief Handles all the events the player does.
	* \param The SDL_Event structure.
	*/
	void handleEvent(SDL_Event& e);
	/*
	* \brief Moves the player according to the player's events.
	*/
	void move();

private:
	//Checks if the player is grounded.
	bool isGrounded;

};

#endif