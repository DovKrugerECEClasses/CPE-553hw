#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using namespace glm;

class GLWin {
public:
	class Color {
	public:
		float r,g,b;
		Color(float r, float g, float b) : r(r), g(g), b(b) {}
	};
private:
	GLFWwindow* win;
	GLuint programID;
	GLuint vertexbuffer;
	GLuint vertexArrayID;
	GLuint texture;
	GLuint textureID;
	GLuint uvbuffer;
	GLuint matrixID;
	glm::mat4 MVP;
	Color bg;
	
	static bool initialized;
	static void classInit();
	GLuint readShader(const char filename[], GLuint shaderType);
public:	
	GLWin(int w, int h, const char title[],
				const char vertexShader[], const char fragShader[],
				const Color& bg);
	void init();
	void project4to3();
	
	void setup();
	void waitLoop();
	void draw();
	GLuint loadShaders(const char vertexShaderPath[],
										 const char fragmentShaderPath[]);
	GLuint loadBMP(const char filename[]);
	GLuint loadDDS(const char filename[]);

	~GLWin();
};

