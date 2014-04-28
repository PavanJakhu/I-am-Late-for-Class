#include "Sound.h"

/*
* \brief Initialize all the fields to nullptr.
*/
Sound::Sound()
{
	music = nullptr;
	chunk = nullptr;

	playing = false;
	paused = false;
}

/*
* \brief Loads music.
* \param The file path for the music.
* \return True if the music loaded successfully.
*/
bool Sound::loadMusic(std::string path)
{
	music = nullptr;
	chunk = nullptr;
	music = Mix_LoadMUS(path.c_str());
	if (music == nullptr)
	{
		std::cout << "Fail to load music. " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

/*
* \brief Loads a sound chunk.
* \param The file path for the sound chunk.
* \return True if the sound chunk loaded successfully.
*/
bool Sound::loadChunk(std::string path)
{
	music = nullptr;
	chunk = nullptr;
	chunk = Mix_LoadWAV(path.c_str());
	if (chunk == nullptr)
	{
		std::cout << "Fail to load chunk. " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

/*
* \brief Plays the music or sound chunk according to the number of loops.
* \param The number of times to loop.
*/
void Sound::play(int loops)
{
	if (music != nullptr) //If there is music loaded.
	{
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(music, loops);
		playing = true;
	}
	else if (chunk != nullptr) //If there is a sound chunk loaded.
	{
		Mix_PlayChannel(-1, chunk, loops);
		playing = true;
	}
}

/*
* \brief Puases the music if there is any playing.
*/
void Sound::pause()
{
	if (music != nullptr) //Only pause if there is music loaded.
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
			paused = false;
		}
		else
		{
			Mix_PauseMusic();
			paused = true;
		}
	}
}

/*
* \brief Stops the music if there is any playing.
*/
void Sound::stop()
{
	if (music != nullptr) //Only stop if there is music loaded.
	{
		if (playing)
		{
			Mix_HaltMusic();
			playing = false;
		}
	}
}

/*
* \brief Getter for playing.
* \return True if the music is playing.
*/
bool Sound::getPlaying()
{
	return playing;
}

/*
* \brief Getter for paused.
* \return True if the music is paused.
*/
bool Sound::getPaused()
{
	return paused;
}