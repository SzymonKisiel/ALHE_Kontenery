#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <windows.h>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cuboid.h"

const GLuint WIDTH = 800, HEIGHT = 600;

const GLfloat cameraSpeed = 0.05f;
const GLfloat cameraAngularSpeed = 0.07f;
const GLfloat cameraMouseSensitivity = 0.15f;

glm::vec3 cameraPos = glm::vec3(2.5f, 5.0f, 30.0f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

float lastX;
float lastY;
bool firstMouse = true;

struct CameraMovement {
	bool w = false;
	bool s = false;
	bool a = false;
	bool d = false;
	bool z = false;
	bool x = false;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	CameraMovement* cm = (CameraMovement*)glfwGetWindowUserPointer(window);

	//dol - gora
	if (key == GLFW_KEY_Z) {
		if (action == GLFW_PRESS)
			cm->z = true;
		else if (action == GLFW_RELEASE)
			cm->z = false;
	}
	if (key == GLFW_KEY_X) {
		if (action == GLFW_PRESS)
			cm->x = true;
		else if (action == GLFW_RELEASE)
			cm->x = false;
	}
	//przod - tyl
	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
			cm->w = true;
		else if (action == GLFW_RELEASE)
			cm->w = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS)
			cm->s = true;
		else if (action == GLFW_RELEASE)
			cm->s = false;
	}
	//lewo - prawo
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
			cm->a = true;
		else if (action == GLFW_RELEASE)
			cm->a = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
			cm->d = true;
		else if (action == GLFW_RELEASE)
			cm->d = false;
	}

	//obrot lewo - prawo
	if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS)
			cm->left = true;
		else if (action == GLFW_RELEASE)
			cm->left = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS)
			cm->right = true;
		else if (action == GLFW_RELEASE)
			cm->right = false;
	}
	//obrot gora - dol
	if (key == GLFW_KEY_UP) {
		if (action == GLFW_PRESS)
			cm->up = true;
		else if (action == GLFW_RELEASE)
			cm->up = false;
	}
	if (key == GLFW_KEY_DOWN) {
		if (action == GLFW_PRESS)
			cm->down = true;
		else if (action == GLFW_RELEASE)
			cm->down = false;
	}
}

void cameraControl(CameraMovement& cm) {
	//dol - gora
	if (cm.z)
		cameraPos.y -= cameraSpeed;
	if (cm.x)
		cameraPos.y += cameraSpeed;

	//przod - tyl
	if (cm.w)
		cameraPos += cameraDirection * cameraSpeed;
	if (cm.s)
		cameraPos -= cameraDirection * cameraSpeed;

	//lewo - prawo
	if (cm.a) {
		cameraPos -= cameraRight * cameraSpeed;
	}
	if (cm.d) {
		cameraPos += cameraRight * cameraSpeed;
	}

	//obrot lewo - prawo
	if (cm.left) {
		glm::mat4 m;
		m = glm::rotate(m, glm::radians(1.0f * cameraAngularSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraDirection = glm::normalize(glm::vec3((m * glm::vec4(cameraDirection, 1.0f))) * cameraAngularSpeed);

		m = glm::mat4(1.0f);
		m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraRight = glm::vec3((m * glm::vec4(cameraDirection, 1.0f)));
		cameraRight = glm::normalize(glm::vec3(cameraRight.x, 0.0f, cameraRight.z));
	}
	if (cm.right) {
		glm::mat4 m;
		m = glm::rotate(m, glm::radians(-1.0f * cameraAngularSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraDirection = glm::normalize(glm::vec3(m * glm::vec4(cameraDirection, 1.0f)));

		m = glm::mat4(1.0f);
		m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraRight = glm::vec3((m * glm::vec4(cameraDirection, 1.0f)));
		cameraRight = glm::normalize(glm::vec3(cameraRight.x, 0.0f, cameraRight.z));
	}

	//obrot gora - dol
	if (cm.up) {
		if (cameraDirection.y >= 0.99f) //maksymalny obrot ok. 90 stopni do gory
			cameraDirection.y = 0.99f;
		else {
			glm::mat4 m;
			m = glm::rotate(m, glm::radians(1.0f * cameraAngularSpeed), cameraRight);
			cameraDirection = glm::vec3(m * glm::vec4(cameraDirection, 1.0f));
		}
	}
	if (cm.down) {
		if (cameraDirection.y <= -0.99f) //minimalny obrot ok. 90 stopni do dolu
			cameraDirection.y = -0.99f;
		else {
			glm::mat4 m;
			m = glm::rotate(m, glm::radians(-1.0f * cameraAngularSpeed), cameraRight);
			cameraDirection = glm::vec3(m * glm::vec4(cameraDirection, 1.0f));
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	//obrot lewo - prawo
	glm::mat4 m;
	m = glm::rotate(m, glm::radians(-xoffset * 1.0f * cameraMouseSensitivity), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraDirection = glm::normalize(glm::vec3((m * glm::vec4(cameraDirection, 1.0f))) * cameraAngularSpeed);

	m = glm::mat4(1.0f);
	m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRight = glm::vec3((m * glm::vec4(cameraDirection, 1.0f)));
	cameraRight = glm::normalize(glm::vec3(cameraRight.x, 0.0f, cameraRight.z));

	//obrot gora - dol
	if (cameraDirection.y > 0.95f)
		cameraDirection.y = 0.95f;
	else if (cameraDirection.y < -0.95f)
		cameraDirection.y = -0.95f;
	else {
		glm::mat4 m;
		m = glm::rotate(m, glm::radians(yoffset * cameraAngularSpeed), cameraRight);
		cameraDirection = glm::normalize(glm::vec3(m * glm::vec4(cameraDirection, 1.0f)));
	}
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ALHE Kontenery", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		CameraMovement cm;
		glfwSetWindowUserPointer(window, (void*)&cm);
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		ShaderProgram theProgram("shader.vert", "shader.frag");
		


		// Init containers
		Cuboid testContainer(0.0f, 8.0f, 0.0f, 12.0f, 10.0f, 20.0f, 1.0f, 1.0f, 1.0f);



		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// vertex texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
		

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			cameraControl(cm);
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);

			
			glm::mat4 view = glm::lookAt(cameraPos, cameraDirection + cameraPos, cameraUp);
			glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 1.0f, 150.0f);
			
			GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
			
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


			glm::mat4 trans;
			static GLfloat rot_angle = 0.0f;
			trans = glm::rotate(trans, -glm::radians(rot_angle), glm::vec3(1.0, 0.0, 0.0));
	/*		rot_angle += 0.05f;
			if (rot_angle >= 360.0f)
				rot_angle -= 360.0f;*/
			GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			// Draw our first triangle
			theProgram.Use();

			testContainer.draw();

			// Swap the screen buffers
			glfwSwapBuffers(window);
			Sleep(1);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
