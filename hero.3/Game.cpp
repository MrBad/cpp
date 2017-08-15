//
// Created by vio on 8/14/17.
//
#include <string>
#include <GL/glew.h>
#include "Game.h"
#include "Error.h"

Game::Game(unsigned int width, unsigned int height, const std::string &title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->time = 0;
	state = GAME_PLAYING;
}

void Game::init()
{
	// game init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("Cannot init SDL: " + std::string(SDL_GetError()));
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(
			"Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			800, 600, SDL_WINDOW_OPENGL);
	if (window == 0) {
		fatalError("Cannot create window: " + std::string(SDL_GetError()));
	}

	glContext = SDL_GL_CreateContext(window);
	if(glContext == NULL) {
		fatalError("Cannot create glContext: %s\n" + std::string(SDL_GetError()));
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fatalError("Cannot init glew");
	}

	glClearColor(0, 0, 0.3, 1);

	sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	initShaders();
}


void Game::mainLoop()
{
	while (this->state == GAME_PLAYING) {
		processEvents();
		time += 0.01;
		draw();
		fpsTimer.Update(SDL_GetTicks());
	}
}

void Game::processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			this->state = GAME_OVER;
		} else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				this->state = GAME_OVER;
			}
		} else if (event.type == SDL_MOUSEMOTION) {
//			printf("Mouse: x: %d y: %d\n", event.motion.x, event.motion.y);
		}
	}
}

void Game::draw()
{
	glClearDepth(1.0);
//	glClearColor(0, 0, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer and depth buffer

	colorProgram.use();
	// send time to shader
	GLint timeLocation = colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, time);

	sprite.draw();

	colorProgram.unuse();

	SDL_GL_SwapWindow(window);
}

void Game::quit()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::initShaders()
{
	colorProgram.compileShaders("/home/develop/cpp/hero/shaders/colorShader");
	colorProgram.addAttribute("vertexPosition");
	colorProgram.addAttribute("vertexColor");
	colorProgram.linkShaders();
}
