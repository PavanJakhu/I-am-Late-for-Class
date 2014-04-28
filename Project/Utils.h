#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include "Constants.h"
#include "Animation.h"

class Utils
{
public:
	/*
	* \brief Checks if there is a collision between two rectangles.
	* \param a The first rectangle.
	* \param b The second rectangle.
	* \returns True if the two rectangles are colliding.
	*/
	static bool checkCollision(SDL_Rect a, SDL_Rect b);
	/*
	* \brief Generates a random number between to numbers. Max is exclusive.
	* \param min The minimum number.
	* \param max The maximum number.
	* \return The random number generated.
	*/
	static int randomNumber(int min, int max);

private:

};

#endif