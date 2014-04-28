#include "Utils.h"
#include <time.h>

/*
* \brief Checks if there is a collision between two rectangles.
* \param a The first rectangle.
* \param b The second rectangle.
* \returns True if the two rectangles are colliding.
*/
bool Utils::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;

	return true;
}

/*
* \brief Generates a random number between to numbers. Max is exclusive.
* \param min The minimum number.
* \param max The maximum number.
* \return The random number generated.
*/
int Utils::randomNumber(int min, int max)
{
	srand (time(NULL));
	return rand() % max + min;
}