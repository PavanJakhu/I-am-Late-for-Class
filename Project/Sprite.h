#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

#include "Constants.h"
#include "Texture.h"

class Sprite: public Texture
{
public:
	//The collider rectangle for the sprite.
	SDL_Rect collider;

	/*
	* \brief Initializes every field to default value with speed equal to zero.
	*/
	Sprite();
	/*
	* \brief Initializes every field to default value.
	* \param The rate the sprite moves at.
	*/
	Sprite(float speed);
	/*
	* \brief Deletes all spaces in memory where this object takes.
	*/
	~Sprite();

	/*
	* \brief Handles events for the sub classes.
	* \param The SDL_Event structure.
	*/
	virtual void handleEvent(SDL_Event&) {}
	/*
	* \brief Moves the sprite according to its speed or other values for sub classes.
	*/
	virtual void move() {}

	/*
	* \brief Loads a string to a texture and sets collider to width and height of the string.
	* \param message The message to store in texture.
	* \param color The colour the text is in.
	* \param The font the text is using.
	* \return True if the string loaded successfully into a texture.
	*/
	bool loadFromRenderedText(const std::string message, SDL_Color color, TTF_Font* font);
	/*
	* \brief Loads a image to a texture and sets collider to width and height of the image.
	* \param The file path to the iamge.
	* \return True if the image loaded successfully into a texture.
	*/
	bool loadFromFile(std::string path);
	/*
	* \brief Draws the texture to the screen.
	* \param clip The portion of the image to render. Default set to the whole image or text.
	* \param angle The angle to draw the image. Default set to 0 radians.
	* \param center The center point of the image. Default set to the middle of the image or text.
	* \param flip The reflection of the image. Default set to the orginal reflection of the image or text.
	*/
	void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/*
	* \brief Setter for posX.
	*/
	void setPosX(int positionX);
	/*
	* \brief Setter for posY.
	*/
	void setPosY(int positionY);
	/*
	* \brief Setter for flip.
	*/
	void setFlip(SDL_RendererFlip flips);
	/*
	* \brief Sets the collider to the image width and height.
	*/
	void setCollider();

protected:
	//The x position on screen.
	int posX;
	//The y position on screen.
	int posY;
	//The x velocity of the sprite.
	int velX; 
	//The y velocity of the sprite.
	int velY;
	//The rate the sprite moves.
	float spriteSpeed;
	//The amount of gravity in the y direction.
	int gravity;
	//Checks if the sprite is facing right.
	bool facingRight;

	//The reflection of the image.
	SDL_RendererFlip flip;
};

#endif