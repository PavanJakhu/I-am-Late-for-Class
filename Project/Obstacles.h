#ifndef __OBSTACLES_H_INCLUDED__
#define __OBSTACLES_H_INCLUDED__

#include "Constants.h"
#include "AnimationManager.h"

/*
* \brief The enumartion for which obstacle to output.
*/
enum Obstacle
{
	Block, Jump, Slide
};

class Obstacles : public Sprite
{
public:
	/*
	* \brief Sets up which obstacle to output randomly.
	* \param The rate the object moves.
	*/
	Obstacles(float speed);
	/*
	* \brief Deletes all spaces in memory where this object takes.
	*/
	~Obstacles();

	/*
	* \brief Moves the obstacle to the left and sets collider.
	*/
	void move();
	/*
	* \brief Gets the enumeration the object is.
	*/
	Obstacle getObstacle();

private:
	//Which obstacle the object is.
	Obstacle whichObst;

};

#endif