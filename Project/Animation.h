#ifndef __ANIMATION_H_INCLUDED__
#define __ANIMATION_H_INCLUDED__

#include "Constants.h"
#include "Sprite.h"

class Animation: public Sprite
{
public:
	/*
	* \brief Sets up the animation clips and collider.
	* \param speed The rate the object moves.
	* \param widthFrame The width of every single sprite.
	* \param heightFrame The height of every single sprite.
	* \param maxCol The number of columns in the sprite sheet.
	* \param maxRow The number of rows in the sprite sheet.
	*/
	Animation(float speed, int widthFrame, int heightFrame, int maxCol, int maxRow);
	/*
	* \brief Deletes all pieces in memory this object takes.
	*/
	~Animation();

	/*
	* \brief Plays the animation only once.
	* \param The time it takes to switch between sprite clips.
	*/
	void play(Uint16 frequency);
	/*
	* \brief Plays the aniamtion and then loops back when done.
	* \param The time it takes to switch between sprite clips.
	*/
	void loop(Uint16 frequency);
	/*
	* \brief Draws the current sprite clip to the aniamtion.
	*/
	void render(Uint16 frequency, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/*
	* \brief Setter for the isLooping field.
	* \param Sets the isLooping to looping.
	*/
	void setLooping(bool looping);
	/*
	* \brief Getter for frameWidth.
	* \return The frame width.
	*/
	int getFrameWidth();
	/*
	* \brief Getter for frameHeight.
	* \return The frame height.
	*/
	int getFrameHeight();
	/*
	* \brief Getter for maxCol.
	* \return The maximum number of columns in the sprite sheet.
	*/
	int getMaxCol();
	/*
	* \brief Getter for maxRow.
	* \return The maximum number of rows in the sprite sheet.
	*/
	int getMaxRow();

private:
	//The number of frames the animation has.
	int numFrames;
	//The current frame the aniamtion is on.
	int onFrame;
	//The width of the sprite frame.
	int widthFrame;
	//The height of the sprite frame.
	int heightFrame;
	//The number of columns in the sprite sheet.
	int maxCol;
	//The number of rows in the sprite sheet.
	int maxRow;
	//Checks if the animation is looping.
	bool isLooping;
	//All the sprite clips of the animation.
	SDL_Rect* spriteClips;
	//The current sprite clip the animation is on.
	SDL_Rect* currentClip;

};

#endif