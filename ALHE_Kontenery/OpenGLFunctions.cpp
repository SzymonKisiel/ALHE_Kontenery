#include "OpenGLFunctions.h"

GLuint getCuboidVAO(
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
	auto vertices = getCuboidVertices(startX, startY, startZ, endX, endY, endZ, red, green, blue);
	GLuint VAO, VBO;

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

	return VAO;
}

GLuint getCuboidVAO(float startX, float startY, float startZ, float endX, float endY, float endZ) {
	float red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return getCuboidVAO(startX, startY, startZ, endX, endY, endZ, red, green, blue);
}

GLuint getCuboidVAO(Container& container) {
	return getCuboidVAO(container.getLeftX(), container.getDownY(), container.getFrontZ(), container.getRightX(), container.getUpY(), container.getBottomZ());
}



size_t getCuboidVerticesSize() {
	return 288;
}
size_t getWarehouseVerticesSize() {
	return 288 * 5;
}

vector<GLfloat> getCuboidVertices(
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
	vector<GLfloat> vertices = {
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
	return vertices;
}


GLuint getWarehouseVAO(Container& warehouse) {
	vector<GLfloat> vertices;
	vector<GLfloat> tempVertices;
	//ground
	tempVertices = getCuboidVertices(warehouse.getLeftX() - warehouseOffset, warehouse.getDownY(), warehouse.getFrontZ() - warehouseOffset,
		warehouse.getRightX() + warehouseOffset, warehouse.getDownY() - warehouseDepth, warehouse.getBottomZ() + warehouseOffset,
		warehouseColorRed, warehouseColorGreen, warehouseColorBlue
	);
	vertices.insert(vertices.end(), tempVertices.begin(), tempVertices.end());
	//left-front pole
	tempVertices = getCuboidVertices(warehouse.getLeftX(), warehouse.getUpY(), warehouse.getFrontZ(),
		warehouse.getLeftX() - warehouseOffset, warehouse.getDownY(), warehouse.getFrontZ() - warehouseOffset,
		warehouseColorRed, warehouseColorGreen, warehouseColorBlue
	);
	vertices.insert(vertices.end(), tempVertices.begin(), tempVertices.end());
	//right-front pole
	tempVertices = getCuboidVertices(warehouse.getRightX(), warehouse.getUpY(), warehouse.getFrontZ(),
		warehouse.getRightX() + warehouseOffset, warehouse.getDownY(), warehouse.getFrontZ() - warehouseOffset,
		warehouseColorRed, warehouseColorGreen, warehouseColorBlue
	);
	vertices.insert(vertices.end(), tempVertices.begin(), tempVertices.end());
	//left-back pole
	tempVertices = getCuboidVertices(warehouse.getLeftX(), warehouse.getUpY(), warehouse.getBottomZ(),
		warehouse.getLeftX() - warehouseOffset, warehouse.getDownY(), warehouse.getBottomZ() + warehouseOffset,
		warehouseColorRed, warehouseColorGreen, warehouseColorBlue
	);
	vertices.insert(vertices.end(), tempVertices.begin(), tempVertices.end());
	//right-back pole
	tempVertices = getCuboidVertices(warehouse.getRightX(), warehouse.getUpY(), warehouse.getBottomZ(),
		warehouse.getRightX() + warehouseOffset, warehouse.getDownY(), warehouse.getBottomZ() + warehouseOffset,
		warehouseColorRed, warehouseColorGreen, warehouseColorBlue
	);
	vertices.insert(vertices.end(), tempVertices.begin(), tempVertices.end());


	GLuint VAO, VBO;

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

	return VAO;
}
