#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Object.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>


class Game
{
public:
	Game();
	~Game();
	void Start(const char* title, int xpos, int ypos, int width, int height);
	void HandleEvents();
	void update();
	void render();
	void clean();
	void WaiveOf_FallingObject();
	void GameIsPauseMessage();
	bool running();
	
	static SDL_Renderer* GameRenderer;
private:
	void checkCollision();
	void ScoreKeeping();

	SDL_Window* mGameWindow;
				
	const int SCREEN_WIDTH = 1027;
	const int SCREEN_HEIGHT = 768;
	bool m_isRunning;
	bool isGamePause = false;
	int P_pressedCounter = 0;

	int audio_rate = 22050;			//Frequency of audio playback
	int audio_channels = 2;			//2 channels = stereo
	int audio_buffers = 4096;		//Size of the audio buffers in memory
	Uint16 audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing

	Mix_Music* Game_Music = NULL;	//Pointer to our sound, in memory
	Mix_Chunk* Apple_Sound = NULL;
	Mix_Chunk* HitByLog_Sound = NULL;
	Mix_Chunk* FootStep_Sound = NULL;
};

#endif 