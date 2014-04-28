#include "Constants.h"

namespace constants
{
	//The window.
	SDL_Window* window;
	//The renderer.
	SDL_Renderer* renderer;
	//The score font used for the score in game.
	TTF_Font* scoreFont;
	//The leaderboard font used for the leaderboard scores.
	TTF_Font* leaderboardFont;
	//The button font used for the button textures.
	TTF_Font* buttonFont;
	//The XML document object.
	XMLDocument doc;

	/*
	* \brief Starts all the SDL systems.
	*/
	inline bool start()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			logSDLError("SDL_Init");
			return false;
		}
		if (TTF_Init() != 0)
		{
			logSDLError("TTF_Init");
			return false;
		}
		scoreFont = TTF_OpenFont("Fonts/cour.ttf", 28);
		if (scoreFont == nullptr)
		{
			std::cout << "Fail to load cour.ttf at 28 size. " << TTF_GetError() << std::endl;
			return false;
		}
		leaderboardFont = TTF_OpenFont("Fonts/cour.ttf", 18);
		if (leaderboardFont == nullptr)
		{
			std::cout << "Fail to load cour.ttf at 18 size. " << TTF_GetError() << std::endl;
			return false;
		}
		buttonFont = TTF_OpenFont("Fonts/courbd.ttf", 28);
		if (buttonFont == nullptr)
		{
			std::cout << "Fail to load courbd.ttf at 28 size. " << TTF_GetError() << std::endl;
			return false;
		}
		int imgFlags = IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags))
		{
			logSDLError("IMG_Init");
			return false;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Fail to load Mix_OpenAudio: " << Mix_GetError() << std::endl;
			return false;
		}
		window = SDL_CreateWindow(constants::SCREEN_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			logSDLError("CreateWindow");
			return false;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			logSDLError("CreateRenderer");
			return false;
		}
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		return true;
	}

	/*
	* \brief Deletes and destorys all the SDL systems.
	*/
	inline void close()
	{
		TTF_CloseFont(scoreFont);
		scoreFont = nullptr;
		TTF_CloseFont(leaderboardFont);
		leaderboardFont = nullptr;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		Mix_CloseAudio();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	/*
	* \brief Prints the SDL errors.
	* \param msg The message the method prints.
	* \param os The output the method prints out to.
	*/
	inline void logSDLError(const std::string &msg, std::ostream &os)
	{
		os << msg << " error: " << SDL_GetError() << std::endl;
	}
};