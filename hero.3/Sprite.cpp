//
// Created by vio on 8/14/17.
//

#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite()
{
	vboID = 0;
}

Sprite::~Sprite()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}


void Sprite::init(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	// generate the buffer //
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	Vertex vertexData[6];

	// vertex in screen coordonates
	// first triangle
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//second triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}
	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 0;
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 255;

	// upload data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), (void *) vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0); // sending one attrib array - index 0 - pos

	// sets vertex attrib pointer
	// 2 - x, y, floats
	// position attr pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// send color
	// index 1, 4 bytes, unsigned bytes, not normalized
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}
