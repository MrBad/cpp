//
// Created by vio on 8/14/17.
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Sprite.h"
#include "GLSLProgram.h"

class Game {
public:
	Game(unsigned int width, unsigned int height, const std::string &title);
	void init();
	void mainLoop();
	void quit();

private:
	void initShaders();
	void processEvents();
	void draw();

	enum {
		GAME_PLAYING,
		GAME_OVER,
	};

	unsigned int width, height;
	std::string title;

	SDL_Window *window;
	SDL_GLContext glContext;
	int state;
	Timer fpsTimer;

	Sprite sprite;
	GLSLProgram colorProgram;

	float time;
};


#endif //GAME_H
