#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <vector>
#include <ctime>

#include "Container.h"

class Cuboid {
	std::vector<GLfloat> vertices;
	GLuint VAO;
	GLuint VBO;

	void initVertices(
		float startX,
		float startY,
		float startZ,
		float endX,
		float endY,
		float endZ,
		float red,
		float green,
		float blue
	);
	void initVAO();
public:
	Cuboid(Container & container);
	Cuboid(float startX, float startY, float startZ, float endX, float endY, float endZ);
	Cuboid(
		float startX,
		float startY,
		float startZ,
		float endX,
		float endY,
		float endZ,
		float red,
		float green,
		float blue
	);
	~Cuboid();
	GLuint getVAO();
	size_t getVerticesSize();
	void draw();
};