#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Container.h"


const GLfloat warehouseDepth = 0.1f;
const GLfloat warehouseOffset = 0.2f;
const GLfloat warehouseColorRed = 0.5f;
const GLfloat warehouseColorGreen = 0.5f;
const GLfloat warehouseColorBlue = 0.2f;

const size_t cuboidVerticesSize = 288;
const size_t warehouseVerticesSize = 288*5;


GLuint getCuboidVAO(float startX, float startY, float startZ, float endX, float endY, float endZ, float red, float green, float blue);
GLuint getCuboidVAO(float startX, float startY, float startZ, float endX, float endY, float endZ);
GLuint getCuboidVAO(Container& container);
GLuint getWarehouseVAO(Container& warehouse);

vector<GLfloat> getCuboidVertices(float startX, float startY, float startZ, float endX, float endY, float endZ, float red = 0.0f, float green = 0.0f, float blue = 0.0f);
