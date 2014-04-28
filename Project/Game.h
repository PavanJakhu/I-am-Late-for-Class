#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "Constants.h"
#include "Sound.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "Player.h"
#include "Obstacles.h"
#include "Utils.h"

class Game
{
public:
	//The Game constructor.
	Game();
	//The Game object deconstructor, deltes the everything in the memory from the game.
	~Game();
	//Starts the game.
	void StartGame();

private:
	//The game states in the game.
	enum GameState { MainMenu, How, Credits, InGame, LossScreen };
	//The game state currently.
	GameState gameState;

	//The background music.
	Sound music;
	//The bell sound effect.
	Sound bell;

	//The scrolling background texture.
	Texture back;
	//The player sprite with animations.
	Player* p;
	//The obstacles sprites.
	Obstacles* o;
	//The player's score.
	Texture scoreText;
	
	//The background texture for the main menu.
	Texture startScreen;
	//The play button allowing the player to play the game.
	Sprite playButton;

	//The "How to Play" background texture displaying how to play the game.
	Texture howScreen;
	//The "How to Play" button in the main menu.
	Sprite howButton;
	//The back button to back to the main menu from either the "How to Play" or "Creadits" screen.
	Sprite backButton;

	//The "Credits" background texture displaying who made the game.
	Texture creditsScreen;
	//The credits button allowing the player to see the credits.
	Sprite creditsButton;

	//The lose screen background texture.
	Texture lossScreen;
	//The leaderboard textures displaying the high scores.
	Texture leaderboards[3];
	//The player's score texture they got on that round of playing.
	Texture playerScoreText;
	//The play again button.
	Sprite againButton;
	
	//The scrolling amount the background scorlls.
	int scrollingOffset;
	//The array that holds the top 3 scores.
	int score[3];

	//The temporary storage of the player's score that round of playing.
	int tempScore;
	//The position in the score array where the player's new high score is.
	int playerScore;
	//Checks if the XML has been updated.
	bool updatedXML;
	//The speed the obstacles move at.
	float obstacleSpeed;

	//Initializes the variables for the game.
	void Initialize();
	/*
	* \brief Load the media for the game like iamges, text and sounds.
	* \return True if the media was loaded successfully.
	*/
	bool LoadContent();
	//Delete the spaces in memory for each object when the game closes.
	void UnloadContent();
	//The global events that happen for the entire game.
	void Event(SDL_Event& e);
	/*
	* \brief Allows the game to run logic such as updating the world
	* like checking for collisions, gather input and play sounds.
	*/
	void Update();
	//The game renders its objects.
	void Draw();
};

#endif