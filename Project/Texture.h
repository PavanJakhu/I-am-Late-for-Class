#ifndef __Texture_H_INCLUDED__
#define __Texture_H_INCLUDED__

#include "Constants.h"

class Texture
{
public:
	/*
	* \brief Sets the fields to their default values.
	*/
	Texture();
	/*
	* \brief Deletes all spaces in memory where this object takes.
	*/
	~Texture();

	/*
	* \brief Loads a string to a texture.
	* \param message The message to store in texture.
	* \param color The colour the text is in.
	* \param The font the text is using.
	* \return True if the string loaded successfully into a texture.
	*/
	bool loadFromRenderedText(const std::string message, SDL_Color color, TTF_Font* font);
	/*
	* \brief Loads an image to a texture.
	* \param The file path to the iamge.
	* \return True if the image loaded successfully into a texture.
	*/
	bool loadFromFile(std::string path);
	/*
	* \brief Deletes the texture and sets width and height to zero.
	*/
	void free();
	/*
	* \brief Sets the colour to a RGB value.
	* \param red The red colour value multiplied into copy operations.
	* \param green The green colour value multiplied into copy operations.
	* \param blue The blue colour value multiplied into copy operations.
	*/
	void setColour(Uint8 red, Uint8 green, Uint8 blue);
	/*
	* \brief Sets the blend mode for the texture.
	* \param Used for texture blending.
	*/
	void setBlendMode(SDL_BlendMode blending);
	/*
	* \brief Sets the alpha for the texture.
	* \param The alpha value multiplied into copy operations.
	*/
	void setAlpha(Uint8);
	/*
	* \brief Draws the texture to screen.
	* \param x The x position to draw on the screen.
	* \param y The y position to draw on the screen.
	* \param clip The portion of the image to render. Default set to the whole image or text.
	* \param angle The angle to draw the image. Default set to 0 radians.
	* \param center The center point of the image. Default set to the middle of the image or text.
	* \param flip The reflection of the image. Default set to the orginal reflection of the image or text.
	*/
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/*
	* \brief The getter for mWidth.
	* \return The width of the texture.
	*/
	int getWidth();
	/*
	* \brief The getter for mHeight.
	* \return the height of the texture.
	*/
	int getHeight();

private:
	//The texture pointer.
	SDL_Texture* mTexture;
	//The width of the texture.
	int mWidth;
	//The height of the texture.
	int mHeight;
	//The message string of the texture.
	std::string messageString;

};

#endif