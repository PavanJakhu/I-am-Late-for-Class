#include "Player.h"

/*
* \brief Sets up the player and its aniamtion.
* \param The rate the player moves.
*/
Player::Player(float speed) : AnimationManager(speed)
{
	isGrounded = false;

	//Adds each animation the player character has.
	Animation* walk = new Animation(10, 188, 150, 22, 1);
	if (!walk->loadFromFile("Images/Running.png")) printf("\nLoading running image: ");
	AddAnimation("Walk", walk);

	Animation* slide = new Animation(10, 115,75, 10, 1);
	if(!slide->loadFromFile("Images/Sliding.png")) printf("\nLoading slidding image: ");
	AddAnimation("Slide", slide);

	Animation* block = new Animation(10, 92, 75, 12, 1);
	if(!block->loadFromFile("Images/Blocking.png")) printf("\nLoading blocking image: ");
	AddAnimation("Block", block);

	Animation* jump = new Animation(10, 157,150, 12, 1);
	if(!jump->loadFromFile("Images/Jumping.png")) printf("\nLoading jumping image: ");
	AddAnimation("Jump", jump);

	currentAni = "Walk"; //Sets the default to the walking animation.
	posX = 100;
	posY = constants::SCREEN_HEIGHT - 160;
}

/*
* \brief Deletes all spaces in memory where this object takes.
*/
Player::~Player()
{
	AnimationManager::~AnimationManager();
}

/*
* \brief Handles all the events the player does.
* \param The SDL_Event structure.
*/
void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //If the any key is down.
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			if (isGrounded) //Only jumps if the player is on the ground.
			{
				velY = -20;
				isGrounded = false;
				currentAni = "Jump"; //Switches animations.
			}
			break;
		case SDLK_s:
		case SDLK_DOWN:
			posY = constants::SCREEN_HEIGHT - 75; //Moves the character down so the character is at the ground.
			collider.y = posY;
			getAnimation()->setPosY(posY);
			currentAni = "Slide";
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			posY = constants::SCREEN_HEIGHT - 105;
			collider.y = posY;
			getAnimation()->setPosY(posY);
			currentAni = "Block";
			break;
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			break;
		case SDLK_s:
		case SDLK_DOWN:
			posY = constants::SCREEN_HEIGHT - 150; //Moves the player back up when let go of the key.
			getAnimation()->setPosY(posY);
			collider.y = posY;
			currentAni = "Walk"; //Switches back to default animation.
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			posY = constants::SCREEN_HEIGHT - 150;
			getAnimation()->setPosY(posY);
			collider.y = posY;
			currentAni = "Walk";
		default:
			break;
		}
	}
}

/*
* \brief Moves the player according to the player's events.
*/
void Player::move()
{
	posX += 0;
	getAnimation()->setPosX(posX);
	collider.x = posX;

	if (isGrounded)
	{
		getAnimation()->setPosY(posY);
		collider.y = posY;
	}
	else
	{	
		velY += gravity; //Always moves the character down if it is not grounded.
		if (velY >= 10) velY = 10; //Moves the character up if the player pressed the up arrow or w key.
		posY += velY;
		getAnimation()->setPosY(posY);
		collider.y = posY; //Sets collider accordingly.
		if (posY + getAnimation()->getFrameHeight() > constants::SCREEN_HEIGHT) //When grounded switches back to default walking animation.
		{
			isGrounded = true;
			currentAni = "Walk";
		}
	}

}