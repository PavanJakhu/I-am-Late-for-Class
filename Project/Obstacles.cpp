#include "Obstacles.h"
#include "Utils.h"

/*
* \brief Sets up which obstacle to output randomly.
* \param The rate the object moves.
*/
Obstacles::Obstacles(float speed) : Sprite(speed)
{
	posX = constants::SCREEN_WIDTH;
	switch(Utils::randomNumber(0, 3)) //Randomly chooses which object to pick.
	{
	case Block:
		posY = constants::SCREEN_HEIGHT - 150;
		if (!loadFromFile("Images/Person.png"))
			printf("\nLoading Red image");
		whichObst = Block;
		break;
	case Jump:
		posY = constants::SCREEN_HEIGHT - 63;
		if (!loadFromFile("Images/Books.png"))
			printf("\nLoading Green image");
		whichObst = Jump;
		break;
	case Slide:
		posY = constants::SCREEN_HEIGHT - 150;
		if (!loadFromFile("Images/Plane.png"))
			printf("\nLoading Black image");
		whichObst = Slide;
		break;
	default:
		printf("Something bad happened");
		break;
	}

	setCollider();
}

/*
* \brief Deletes all spaces in memory where this object takes.
*/
Obstacles::~Obstacles()
{
	Sprite::~Sprite();
}

/*
* \brief Moves the obstacle to the left and sets collider.
*/
void Obstacles::move()
{
	posX -= (int)spriteSpeed;
	collider.x = posX;
	collider.y = posY;
}

/*
* \brief Gets the enumeration the object is.
*/
Obstacle Obstacles::getObstacle()
{
	return whichObst;
}