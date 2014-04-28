#ifndef __ANIMATIONMANAGER_H_INCLUDED__
#define __ANIMATIONMANAGER_H_INCLUDED__

#include "Sprite.h"
#include "Animation.h"
#include <map>

class AnimationManager: public Sprite
{
public:
	/*
	* \brief Sets the speed to the Sprite class' speed.
	* \param The rate the object moves.
	*/
	AnimationManager(float speed);
	/*
	* \brief Deletes all pieces of memory this object takes.
	*/
	~AnimationManager();

	/*
	* \brief Adds an animation to the map and sets the collider width and height to the frame width and height.
	* \param name The key to the according animation.
	* \param ani The animation to store in the map.
	*/
	void AddAnimation(std::string name, Animation* ani);
	/*
	* \brief Deletes all the animations stored in the map.
	*/
	void free();
	/*
	* \brief Draws the current animation to the screen.
	* \param The time it takes to switch between sprite clips.
	*/
	void render(Uint16 frequency);
	/*
	* \brief Getter for currentAni.
	* \return The key for the current animation playing.
	*/
	std::string getCurrentAni();
	/*
	* \brief Getter for the current animation.
	* \return The current animation.
	*/
	Animation* getAnimation();

private:
	//The map where all the Animations are stored with a string key.
	std::map<std::string, Animation*> aManager;
protected: 
	//The current animation to be played.
	std::string currentAni;

};

#endif