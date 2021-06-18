#include "Cuboid.h"

Cuboid::Cuboid(Container & container) : 
	Cuboid(container.getLeftX(), container.getDownY(), container.getFrontZ(), container.getRightX(), container.getUpY(), container.getBottomZ()) {
	cout << "T: " << container.getLeftX() << endl;
	cout << "T: " << container.getDownY() << endl;
	cout << "T: " << container.getFrontZ() << endl;
	cout << "T: " << container.getRightX() << endl;
	cout << "T: " << container.getUpY() << endl;
	cout << "T: " << container.getBottomZ() << endl;
	cout << endl << endl;
}

Cuboid::Cuboid(float startX, float startY, float startZ, float endX, float endY, float endZ) {
	float red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	initVertices(startX, startY, startZ, endX, endY, endZ, red, green, blue);
	initVAO();
}

Cuboid::Cuboid(
	float startX,
	float startY,
	float startZ,
	float endX,
	float endY,
	float endZ,
	float red,
	float green,
	float blue
  ) {
	initVertices(startX, startY, startZ, endX, endY, endZ, red, green, blue);
	initVAO();
}

Cuboid::~Cuboid() {
	glDeleteVertexArrays(1, &VAO);
}

GLuint Cuboid::getVAO() {
	return this->VAO;
}

size_t Cuboid::getVerticesSize() {
	return this->vertices.size();
}

void Cuboid::draw() {
	glBindVertexArray(this->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, this->getVerticesSize());
	glBindVertexArray(0);

}

void Cuboid::initVAO() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texture coordinates
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Cuboid::initVertices(
	float startX,
	float startY,
	float startZ,
	float endX,
	float endY,
	float endZ,
	float red = 0.0f,
	float green = 0.0f,
	float blue = 0.0f
) {
	this->vertices = {
		// position				// color			// texture
		// front
		startX, startY, startZ, red, green, blue,	0.0f, 0.0f,
		startX, endY, startZ,	red, green, blue,	0.0f, 1.0f,
		endX, endY, startZ,		red, green, blue,	1.0f, 1.0f,

		startX, startY, startZ, red, green, blue,	0.0f, 0.0f,
		endX, endY, startZ,		red, green, blue,	1.0f, 1.0f,
		endX, startY, startZ,	red, green, blue,	1.0f, 0.0f,

		// bottom
		startX, startY, startZ, red, green, blue,	0.0f, 0.0f,
		startX, startY, endZ,	red, green, blue,	0.0f, 1.0f,
		endX, startY, startZ,	red, green, blue,	1.0f, 0.0f,

		endX, startY, startZ,	red, green, blue,	1.0f, 0.0f,
		endX, startY, endZ,		red, green, blue,	1.0f, 1.0f,
		startX, startY, endZ,	red, green, blue,	0.0f, 1.0f,

		// right
		endX, startY, startZ,	red, green, blue,	0.0f, 0.0f,
		endX, endY, startZ,		red, green, blue,	1.0f, 0.0f,
		endX, startY, endZ,		red, green, blue,	0.0f, 1.0f,

		endX, startY, endZ,		red, green, blue,	0.0f, 1.0f,
		endX, endY, endZ,		red, green, blue,	1.0f, 1.0f,
		endX, endY, startZ,		red, green, blue,	1.0f, 0.0f,

		// left
		startX, startY, startZ, red, green, blue,	0.0f, 0.0f,
		startX, endY, startZ,	red, green, blue,	1.0f, 0.0f,
		startX, startY, endZ,	red, green, blue,	0.0f, 1.0f,

		startX, startY, endZ,	red, green, blue,	0.0f, 1.0f,
		startX, endY, endZ,		red, green, blue,	1.0f, 1.0f,
		startX, endY, startZ,	red, green, blue,	1.0f, 0.0f,

		// up
		startX, endY, startZ,	red, green, blue,	0.0f, 0.0f,
		startX, endY, endZ,		red, green, blue,	0.0f, 1.0f,
		endX, endY, startZ,		red, green, blue,	1.0f, 0.0f,

		endX, endY, startZ,		red, green, blue,	1.0f, 0.0f,
		endX, endY, endZ,		red, green, blue,	1.0f, 1.0f,
		startX, endY, endZ,		red, green, blue,	0.0f, 1.0f,

		//back
		startX, startY, endZ,	red, green, blue,	0.0f, 0.0f,
		startX, endY, endZ,		red, green, blue,	0.0f, 1.0f,
		endX, endY, endZ,		red, green, blue,	1.0f, 1.0f,

		startX, startY, endZ,	red, green, blue,	0.0f, 0.0f,
		endX, endY, endZ,		red, green, blue,	1.0f, 1.0f,
		endX, startY, endZ,		red, green, blue,	1.0f, 0.0f,
	};
}