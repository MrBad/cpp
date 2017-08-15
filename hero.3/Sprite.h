//
// Created by vio on 8/14/17.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>

class Sprite {

public:
	Sprite();

	virtual ~Sprite();

	void init(float x, float y, float width, float height);

	void draw();

private:
	float x;
	float y;
	float width;
	float height;

	GLuint vboID;
};


#endif //SPRITE_H
