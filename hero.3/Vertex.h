//
// Created by vio on 8/15/17.
//

#ifndef HERO_VERTEX_H
#define HERO_VERTEX_H

#include <GL/glew.h>

struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r, g, b, a;
} color;

struct Vertex {
	Position position;
	Color color;
};

#endif //HERO_VERTEX_H
