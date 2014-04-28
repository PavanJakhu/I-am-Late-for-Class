#include "Texture.h"

/*
* \brief Sets the fields to their default values.
*/
Texture::Texture()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

/*
* \brief Deletes all spaces in memory where this object takes.
*/
Texture::~Texture()
{
	free();
}

/*
* \brief Loads a string to a texture.
* \param message The message to store in texture.
* \param color The colour the text is in.
* \param The font the text is using.
* \return True if the string loaded successfully into a texture.
*/
bool Texture::loadFromRenderedText(const std::string message, SDL_Color color, TTF_Font* font)
{
	messageString = message.c_str();
	//Uses surface first before converting to texture so it can use TTF's libraries to make a string into a texture.
	SDL_Surface* textSurf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (textSurf == nullptr)
	{
		printf("Loading surface for font error. Message: %s. %s", message, TTF_GetError());
		return false;
	}

	mTexture = SDL_CreateTextureFromSurface(constants::renderer, textSurf);
	if (mTexture == nullptr)
	{
		printf("Coverting surface to texture error. %s", SDL_GetError());
		return false;
	}

	mWidth = textSurf->w;
	mHeight = textSurf->h;

	SDL_FreeSurface(textSurf);
	return true;
}

/*
* \brief Loads an image to a texture.
* \param The file path to the iamge.
* \return True if the image loaded successfully into a texture.
*/
bool Texture::loadFromFile(std::string path)
{
	free();

	//Uses surface first so it can use IMG_Load to load most image file types.
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Surface did not load. Path: %s - %s", path, IMG_GetError());
		return false;
	}
	mTexture = SDL_CreateTextureFromSurface(constants::renderer, loadedSurface); //Converts the surface to texture.
	if (mTexture == nullptr)
	{
		printf("Surface did not convert to texture. %s", SDL_GetError());
		return false;
	}
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
	return true;
}

/*
* \brief Deletes the texture and sets width and height to zero.
*/
void Texture::free()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

/*
* \brief Sets the colour to a RGB value.
* \param red The red colour value multiplied into copy operations.
* \param green The green colour value multiplied into copy operations.
* \param blue The blue colour value multiplied into copy operations.
*/
void Texture::setColour(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

/*
* \brief Sets the blend mode for the texture.
* \param Used for texture blending.
*/
void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

/*
* \brief Sets the alpha for the texture.
* \param The alpha value multiplied into copy operations.
*/
void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

/*
* \brief Draws the texture to screen.
* \param x The x position to draw on the screen.
* \param y The y position to draw on the screen.
* \param clip The portion of the image to render. Default set to the whole image or text.
* \param angle The angle to draw the image. Default set to 0 radians.
* \param center The center point of the image. Default set to the middle of the image or text.
* \param flip The reflection of the image. Default set to the orginal reflection of the image or text.
*/
void Texture::render(int x, int y, SDL_Rect* clip, double angle , SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(constants::renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

/*
* \brief The getter for mWidth.
* \return The width of the texture.
*/
int Texture::getWidth()
{
	return mWidth;
}

/*
* \brief The getter for mHeight.
* \return the height of the texture.
*/
int Texture::getHeight()
{
	return mHeight;
}