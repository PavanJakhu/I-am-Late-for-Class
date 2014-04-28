#include "Animation.h"

/*
* \brief Sets up the animation clips and collider.
* \param speed The rate the object moves.
* \param widthFrame The width of every single sprite.
* \param heightFrame The height of every single sprite.
* \param maxCol The number of columns in the sprite sheet.
* \param maxRow The number of rows in the sprite sheet.
*/
Animation::Animation(float speed, int widthFrame, int heightFrame, int maxCol, int maxRow) : Sprite(speed)
{
	numFrames = maxCol * maxRow;
	onFrame = 0;
	isLooping = true;
	spriteClips = new SDL_Rect[numFrames];
	Animation::widthFrame = widthFrame;
	Animation::heightFrame = heightFrame;
	Animation::maxCol = maxCol;
	Animation::maxRow = maxRow;

	int col = 0, row = 0;
	for (int i = 0; i < numFrames; i++)
	{
		if (col >= maxCol)
		{
			col = 0;
			row++;
		}
		if (row > maxRow) break;
		spriteClips[i].x = col * widthFrame;
		spriteClips[i].y = row * heightFrame;
		spriteClips[i].w = widthFrame;
		spriteClips[i].h = heightFrame;
		col++;
	}
	
	collider.x = collider.y = 0;
	collider.w = spriteClips[0].w;
	collider.h = spriteClips[0].h;
}

/*
* \brief Deletes all pieces of memory this object takes.
*/
Animation::~Animation()
{
	Sprite::~Sprite();
}

/*
* \brief Plays the animation only once.
* \param The time it takes to switch between sprite clips.
*/
void Animation::play(Uint16 frequency)
{
	if (onFrame / frequency <= numFrames)
	{
		if (isLooping)
			onFrame = 0;

		currentClip = &spriteClips[onFrame / frequency];

		onFrame++;
	}
}

/*
* \brief Plays the aniamtion and then loops back when done.
* \param The time it takes to switch between sprite clips.
*/
void Animation::loop(Uint16 frequency)
{
	if (!isLooping)
		onFrame = 0;

	currentClip = &spriteClips[onFrame / frequency];

	onFrame++;
	if (onFrame / frequency >= numFrames)
		onFrame = 0;
}

/*
* \brief Draws the current sprite clip to the aniamtion.
*/
void Animation::render(Uint16 frequency, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (isLooping)
		loop(frequency);
	else
		play(frequency);
	Sprite::render(currentClip, angle, center, flip);
}

/*
* \brief Setter for the isLooping field.
* \param Sets the isLooping to looping.
*/
void Animation::setLooping(bool loop)
{
	isLooping = loop;
}

/*
* \brief Getter for frameWidth.
* \return The frame width.
*/
int Animation::getFrameWidth()
{
	return widthFrame;
}

/*
	* \brief Getter for frameHeight.
	* \return The frame height.
	*/
int Animation::getFrameHeight()
{
	return heightFrame;
}

/*
* \brief Getter for maxCol.
* \return The maximum number of columns in the sprite sheet.
*/
int Animation::getMaxCol()
{
	return maxCol;
}

/*
* \brief Getter for maxRow.
* \return The maximum number of rows in the sprite sheet.
*/
int Animation::getMaxRow()
{
	return maxRow;
}