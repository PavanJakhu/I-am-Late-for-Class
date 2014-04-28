#include "AnimationManager.h"

/*
* \brief Sets the speed to the Sprite class' speed.
* \param The rate the object moves.
*/
AnimationManager::AnimationManager(float speed) : Sprite(speed)
{
}

/*
* \brief Deletes all pieces of memory this object takes.
*/
AnimationManager::~AnimationManager()
{
	free();
}

/*
* \brief Adds an animation to the map and sets the collider width and height to the frame width and height.
* \param name The key to the according animation.
* \param ani The animation to store in the map.
*/
void AnimationManager::AddAnimation(std::string name, Animation* ani)
{
	aManager.insert(std::make_pair(name, ani));
	//Sets the colliders to the width and height of the sprite clip.
	collider.w = ani->collider.w / ani->getMaxCol(); 
	collider.h = ani->collider.h / ani->getMaxRow();
	currentAni = name;
}

/*
* \brief Deletes all the animations stored in the map.
*/
void AnimationManager::free()
{
	for (std::map<std::string, Animation*>::iterator i = aManager.begin(); i != aManager.end(); i++)
		i->second->free();
}

/*
* \brief Draws the current animation to the screen.
* \param The time it takes to switch between sprite clips.
*/
void AnimationManager::render(Uint16 frequency)
{
	if (getAnimation() != nullptr)
		getAnimation()->render(frequency);
}

/*
* \brief Getter for currentAni.
* \return The key for the current animation playing.
*/
std::string AnimationManager::getCurrentAni()
{
	return currentAni;
}

/*
* \brief Getter for the current animation.
* \return The current animation.
*/
Animation* AnimationManager::getAnimation()
{
	for (std::map<std::string, Animation*>::iterator i = aManager.begin(); i != aManager.end(); i++)
	{
		if (i->first == currentAni) //Gets the animation for the current animation.
			return i->second;
	}
	return nullptr;
}