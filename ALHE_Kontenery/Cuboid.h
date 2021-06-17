#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <vector>

class Cuboid {
	std::vector<GLfloat> vertices;
	GLuint VAO;

	std::vector<GLfloat> getCuboidVertices(
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
public:
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