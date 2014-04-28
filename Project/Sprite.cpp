#include "Sprite.h"

/*
* \brief Initializes every field to default value with speed equal to zero.
*/
Sprite::Sprite() : Texture()
{
	spriteSpeed = 0;
	gravity = 0;

	posX = 0;
	posY = 0;
	collider.x = posX;
	collider.y = posY;

	velX = 0;
	velY = 0;

	flip = SDL_FLIP_NONE;
	facingRight = false;
}

/*
* \brief Initializes every field to default value.
* \param The rate the sprite moves at.
*/
Sprite::Sprite(float speed) : Texture()
{
	spriteSpeed = speed;
	gravity = 1;

	posX = 0;
	posY = 0;
	collider.x = posX;
	collider.y = posY;

	velX = 0;
	velY = 0;

	flip = SDL_FLIP_NONE;
	facingRight = false;
}

/*
* \brief Deletes all spaces in memory where this object takes.
*/
Sprite::~Sprite()
{
	Texture::~Texture();
}

/*
* \brief Loads a string to a texture and sets collider to width and height of the string.
* \param message The message to store in texture.
* \param color The colour the text is in.
* \param The font the text is using.
* \return True if the string loaded successfully into a texture.
*/
bool Sprite::loadFromRenderedText(const std::string message, SDL_Color color, TTF_Font* font)
{
	bool succues = Texture::loadFromRenderedText(message, color, font);
	collider.w = getWidth();
	collider.h = getHeight();
	return succues;
}

/*
* \brief Loads a image to a texture and sets collider to width and height of the image.
* \param The file path to the iamge.
* \return True if the image loaded successfully into a texture.
*/
bool Sprite::loadFromFile(std::string path)
{
	bool succues = Texture::loadFromFile(path);
	collider.w = getWidth();
	collider.h = getHeight();
	return succues;
}

/*
* \brief Draws the texture to the screen.
* \param clip The portion of the image to render. Default set to the whole image or text.
* \param angle The angle to draw the image. Default set to 0 radians.
* \param center The center point of the image. Default set to the middle of the image or text.
* \param flip The reflection of the image. Default set to the orginal reflection of the image or text.
*/
void Sprite::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	Texture::render(posX, posY, clip, angle, center, Sprite::flip);
}

/*
* \brief Setter for posX.
*/
void Sprite::setPosX(int positionX)
{
	posX = positionX;
	collider.x = posX;
}

/*
* \brief Setter for posY.
*/
void Sprite::setPosY(int positionY)
{
	posY = positionY;
	collider.y = posY;
}

/*
* \brief Setter for flip.
*/
void Sprite::setFlip(SDL_RendererFlip flips)
{
	flip = flips;
}

/*
* \brief Sets the collider to the image width and height.
*/
void Sprite::setCollider()
{
	collider.w = getWidth();
	collider.h = getHeight();
}