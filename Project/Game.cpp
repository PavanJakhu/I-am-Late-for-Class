#include "Game.h"

//The Game constructor.
Game::Game()
{
	//Initialize everything in the object.
	gameState = MainMenu;
	for (int i = 0; i < 3; i++) score[i] = 0;
	int scrollingOffset = 0;
	int tempScore = 0;
	int playerScore = 0;
	bool updatedXML = false;
	float obstacleSpeed = 0;
}

//The Game object deconstructor, deltes the everything in the memory from the game.
Game::~Game() 
{
	//Delete the objects in memory.
	UnloadContent();
	constants::close();
}

//Starts the game.
void Game::StartGame()
{
	//The game's start up sequence and event, update and draw loop.
	if (!constants::start()) std::getchar(); //If the SDL systems do not start, end the program.
	else
	{
		if (!LoadContent()) std::getchar(); //If the media does not load, end the program.
		else
		{
			Initialize(); //Initialize all the variables.
			//Main/event loop
			SDL_Event e;
			bool quit = false;
			while (!quit) //If the player has press the close button for the screen.
			{
				while (SDL_PollEvent(&e)) //Gets the event like mouse or key events.
				{
					if (e.type == SDL_QUIT) //If the player has pressed the close button in the program.
						quit = true;
					Event(e); //Runs through the events and checks if the player has done any.
				}
				Update(); //Updates the objects
				Draw(); //Renders the objects to the screen.
			}
		}
	}
}

//Initializes the variables for the game.
void Game::Initialize()
{
	p = new Player(10); //The player object.
	o = new Obstacles(10); //The obstacle object

	scrollingOffset = 0; //The background scrolling starts at the beginning.

	obstacleSpeed = 10; //The obstacles will go 10 pixels per frame at the beginning.

	tempScore = 0; //The player's score at the beginning.

	updatedXML = false; //The score XML has not been updated with the player's new score.

	//Sets the position for the buttons on screen.
	playButton.setPosX(constants::SCREEN_WIDTH / 2 - playButton.getWidth() / 2);
	playButton.setPosY(constants::SCREEN_HEIGHT / 2 - 20);

	howButton.setPosX(constants::SCREEN_WIDTH / 2 - howButton.getWidth() / 2);
	howButton.setPosY(playButton.collider.y + playButton.getHeight() + 5);

	creditsButton.setPosX(constants::SCREEN_WIDTH / 2 - creditsButton.getWidth() / 2);
	creditsButton.setPosY(howButton.collider.y + howButton.getHeight() + 5);

	againButton.setPosX(constants::SCREEN_WIDTH - againButton.getWidth() - 100);
	againButton.setPosY(constants::SCREEN_HEIGHT / 2 + 50);
}

/*
* \brief Load the media for the game like iamges, text and sounds.
* \return True if the media was loaded successfully.
*/
bool Game::LoadContent()
{
	SDL_Color black = {0, 0, 0}; //The black text colour.

	//TODO: Load media and error check.
	if (!music.loadMusic("Sounds/music.wav")) return false;
	if (!bell.loadChunk("Sounds/SchoolBell-Short.wav")) return false;

	if (!back.loadFromFile("Images/Paralax.png")) return false;
	if (!startScreen.loadFromFile("Images/Menu.png")) return false;
	if (!howScreen.loadFromFile("Images/How.png")) return false;
	if (!creditsScreen.loadFromFile("Images/Credits.png")) return false;
	if (!lossScreen.loadFromFile("Images/Lose.png")) return false;

	if (!playButton.loadFromRenderedText("Play", black, constants::buttonFont)) return false;
	if (!howButton.loadFromRenderedText("How to Play", black, constants::buttonFont)) return false;
	if (!creditsButton.loadFromRenderedText("Credits", black, constants::buttonFont)) return false;
	if (!backButton.loadFromRenderedText("Back", black, constants::buttonFont)) return false;
	if (!againButton.loadFromRenderedText("Play Again", black, constants::buttonFont)) return false;

	if (!playerScoreText.loadFromRenderedText("<-Your score", black, constants::leaderboardFont)) return false;

	return true;
}

//Delete the spaces in memory for each object when the game closes.
void Game::UnloadContent()
{
	//TODO: Free textures, images, fonts and stop timers.
	back.free();

	lossScreen.free();
	againButton.free();

	howScreen.free();
	howButton.free();
	backButton.free();

	creditsScreen.free();
	creditsButton.free();
	
	startScreen.free();
	playButton.free();
	
	scoreText.free();
	playerScoreText.free();
	for (int i = 0; i < 3; i++) leaderboards[i].free();
	o->free();
	p->free();
}

//The global events that happen for the entire game.
void Game::Event(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) //If the mouse button is down.
	{
		int x, y;
		SDL_GetMouseState(&x, &y); //Get the mouse's position on screen.
		
		//Check if the mouse is over the buttons and clicked to do according action.
		if (gameState == MainMenu)
		{
			if (x > playButton.collider.x && x < playButton.collider.x + playButton.collider.w && y > playButton.collider.y && y < playButton.collider.y + playButton.collider.h)
				gameState = InGame;
			else if (x > howButton.collider.x && x < howButton.collider.x + howButton.collider.w && y > howButton.collider.y && y < howButton.collider.y + howButton.collider.h)
				gameState = How;
			else if (x > creditsButton.collider.x && x < creditsButton.collider.x + creditsButton.collider.w && y > creditsButton.collider.y && y < creditsButton.collider.y + creditsButton.collider.h)
				gameState = Credits;
		}
		else if ((gameState == How || gameState == Credits) && x > backButton.collider.x && x < backButton.collider.x + backButton.collider.w && y > backButton.collider.y && y < backButton.collider.y + backButton.collider.h)
			gameState = MainMenu;
		else if (gameState == LossScreen && x > againButton.collider.x && x < againButton.collider.x + againButton.collider.w && y > againButton.collider.y && y < againButton.collider.y + againButton.collider.h)
		{
			Initialize();
			gameState = InGame;
		}
	}

	p->handleEvent(e); //Do the player's events.
}

/*
* Allows the game to run logic such as updating the world
* like checking for collisions, gather input and play sounds.
*/
void Game::Update()
{
	SDL_Color black = {0, 0, 0}; //Black font colour.

	switch (gameState) //Check what gamestate the game is in.
	{
	case MainMenu:
		if (!music.getPlaying()) //If the music is not playing then play the music.
			music.play(6);
		break;
	case How:
		//Set the position for the back button in the "How to Play" screen.
		backButton.setPosX(constants::SCREEN_WIDTH / 2 - backButton.getWidth() / 2);
		backButton.setPosY(constants::SCREEN_HEIGHT / 2 + 60);
		break;
	case Credits:
		//Set the position for the back button in the "Credits" screen.
		backButton.setPosX(constants::SCREEN_WIDTH / 2 - backButton.getWidth() / 2 + 150);
		backButton.setPosY(constants::SCREEN_HEIGHT / 2 + 60);
		break;
	case InGame:
		scrollingOffset -= 5; //Move the background every 5 pixels per frame
		if (scrollingOffset < -back.getWidth()) //If the background is totally off screen then go back to it's starting position.
			scrollingOffset = 0;
	
		p->move(); //Move the player.
		o->move(); //Move the obstacle.

		if (o->collider.x + o->collider.w < 0) //If the obstacle is off screen then spawn a new obstacle, up the score by one and make the obstacle go faster next time.
		{
			tempScore++;
			if (obstacleSpeed <= 1.0f) obstacleSpeed = 1.0f;
			else obstacleSpeed -= 0.1f;
			o = new Obstacles(obstacleSpeed);
		}

		if (Utils::checkCollision(p->collider, o->collider)) //If the obstacle and player is colliding then check if it is using the block animation with the person obstacle, if not then the player loses.
		{
			if (p->getCurrentAni() == "Block" && o->getObstacle() == Block)
			{
				std::cout << "Blocked" << std::endl;
			}
			else
			{
				gameState = LossScreen; //Switch the game state to the loses screen.
				bell.play(0); //Play the bell ringing sound effect.
			}
		}
		else //If the player is not colliding but doing the right animation with the appropriate obstacle then they pass, else they lose.
		{
			if (p->getCurrentAni() == "Jump" && o->getObstacle() == Jump)
			{
				std::cout << "Jumped" << std::endl;
			}
			else if (p->getCurrentAni() == "Slide" && o->getObstacle() == Slide)
			{
				std::cout << "Slided" << std::endl;
			}
		}

		//Update the score text with the new score.
		if (!scoreText.loadFromRenderedText("Score: " + std::to_string(tempScore), black, constants::scoreFont)) std::cout << "Socre text did not load." << std::endl;
		break;
	case LossScreen:
		if (!updatedXML) //Updates the XML once.
		{
			if (constants::doc.LoadFile("XML/scores.xml") != 0) //Loads the scores XML to check if the player's new score is higher than any of the ones in the XML then stores that number in the scores array.
				std::cout << "scores.xml did not load" << std::endl;
			else
			{
				int i = 0;
				XMLElement* element = constants::doc.FirstChildElement("Score");
				for (XMLElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
				{
					const char* scoreNum = child->GetText();
					if (!(std::istringstream(scoreNum) >> score[i])) score[i] = -1;
					else if (score[i] <= tempScore) { score[i] = tempScore; playerScore = i; break; }
					i++;
				}

				if (constants::doc.LoadFile("XML/empty.xml") != 0) //Uses an empty XML with only the first line of a XML so the XML does not append the new scores to the end of the scores.xml.
					std::cout << "empty.xml did not load" << std::endl;
				else
				{
					//Saves the xml with the new score.
					XMLElement* scoreNode = constants::doc.NewElement("Score"); //Start first node
					XMLElement* scoreNumNode[3];
					XMLText* scoreNumText[3];
					const char* nodeNum;

					for (int i = 0; i < 3; i++)
					{
						if (i == 0) nodeNum = "First";
						else if (i == 1) nodeNum = "Second";
						else nodeNum = "Third";
						scoreNumNode[i] = constants::doc.NewElement(nodeNum); //Start score node
						scoreNumText[i] = constants::doc.NewText(std::to_string(score[i]).c_str()); //Score number
						scoreNumNode[i]->InsertEndChild(scoreNumText[i]); //Ending score node
						scoreNode->InsertEndChild(scoreNumNode[i]);
					}

					constants::doc.InsertEndChild(scoreNode);
					constants::doc.SaveFile("XML/scores.xml");
				}
			}

			int i = 0;
			XMLElement* element = constants::doc.FirstChildElement("Score");
			for (XMLElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
			{
				//Stores the scores in the XMl to a Texture array so it can be printed.
				std::string scoreNum = "";
				scoreNum.append(child->Value()); scoreNum.append(": "); scoreNum.append(child->GetText());
				leaderboards[i].loadFromRenderedText(scoreNum, black, constants::leaderboardFont);
				i++;
			}

			updatedXML = true;
		}
		break;
	default:
		break;
	}
	
}

//The game renders its objects.
void Game::Draw()
{
	SDL_SetRenderDrawColor(constants::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(constants::renderer);
	switch (gameState) //Draws only the the things needed for the game state accordinng to the variable gameState.
	{
	case MainMenu:
		startScreen.render(0, 0);
		playButton.render();
		howButton.render();
		creditsButton.render();
		break;
	case How:
		howScreen.render(0, 0);
		backButton.render();
		break;
	case Credits:
		creditsScreen.render(0, 0);
		backButton.render();
		break;
	case InGame:
		//Draws twice so when the first background gets to the edge of the width of the screen there is another background there, but then resets.
		back.render(scrollingOffset, 0);
		back.render(scrollingOffset + back.getWidth(), 0);

		scoreText.render(20, 20);

		p->render(5);

		o->render();
		break;
	case LossScreen:
		lossScreen.render(0,0);
		againButton.render();
		if (updatedXML)
		{
			for (int i = 0; i < 3; i++)
				leaderboards[i].render(constants::SCREEN_WIDTH / 2 - leaderboards[i].getWidth() / 2, i * (leaderboards[i].getHeight() + 2) + constants::SCREEN_HEIGHT / 2 + 30);
			//playerScoreText.render(constants::SCREEN_WIDTH / 2 - leaderboards[playerScore].getWidth() / 2 + leaderboards[playerScore].getWidth() + 5,  playerScore * (leaderboards[playerScore].getHeight() + 2) + constants::SCREEN_HEIGHT / 2 + 30);
		}
		break;
	default:
		break;
	}
	SDL_RenderPresent(constants::renderer);
}