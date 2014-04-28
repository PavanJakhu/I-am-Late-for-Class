#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include "tinyxml2.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <stdio.h>
using namespace tinyxml2;

namespace constants
{
	//The screen's width.
	const int SCREEN_WIDTH = 1024;
	//The screen's height.
	const int SCREEN_HEIGHT = 600;
	//The window's name.
	const std::string SCREEN_NAME = "Fuck, I'm Late for Class";

	//The window.
	extern SDL_Window* window;
	//The renderer.
	extern SDL_Renderer* renderer;
	//The score font used for the score in game.
	extern TTF_Font* scoreFont;
	//The leaderboard font used for the leaderboard scores.
	extern TTF_Font* leaderboardFont;
	//The button font used for the button textures.
	extern TTF_Font* buttonFont;
	//The XML document object.
	extern XMLDocument doc;

	/*
	* \brief Starts all the SDL systems.
	*/
	extern bool start();
	/*
	* \brief Deletes and destorys all the SDL systems.
	*/
	extern void close();
	/*
	* \brief Prints the SDL errors.
	* \param msg The message the method prints.
	* \param os The output the method prints out to.
	*/
	extern void logSDLError(const std::string& msg, std::ostream& os = std::cout);
};

#endif