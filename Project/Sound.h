#ifndef __SOUND_H_INLCUDED__
#define __SOUND_H_INLCUDED__

#include "Constants.h"

class Sound
{
public:
	/*
	* \brief Initialize all the fields to nullptr.
	*/
	Sound();

	/*
	* \brief Loads music.
	* \param The file path for the music.
	* \return True if the music loaded successfully.
	*/
	bool loadMusic(std::string path);
	/*
	* \brief Loads a sound chunk.
	* \param The file path for the sound chunk.
	* \return True if the sound chunk loaded successfully.
	*/
	bool loadChunk(std::string path);
	/*
	* \brief Plays the music or sound chunk according to the number of loops.
	* \param The number of times to loop.
	*/
	void play(int loops);
	/*
	* \brief Puases the music if there is any playing.
	*/
	void pause();
	/*
	* \brief Stops the music if there is any playing.
	*/
	void stop();
	/*
	* \brief Getter for playing.
	* \return True if the music is playing.
	*/
	bool getPlaying();
	/*
	* \brief Getter for paused.
	* \return True if the music is paused.
	*/
	bool getPaused();

private:
	//Checks if sound is playing.
	bool playing;
	//Checks if the sound is paused.
	bool paused;
	//The music sound.
	Mix_Music* music;
	//The sound chunk sound.
	Mix_Chunk* chunk;

};

#endif // !__SOUND_H_INLCUDED__
