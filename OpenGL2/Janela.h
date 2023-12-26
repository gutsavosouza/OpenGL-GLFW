#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Janela
{
public:
	Janela();

	Janela(GLint wWidht, GLint wHeight);

	int init();

	GLint getBufferWidht() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	bool* getKeys() { return keys; }
	GLfloat getMudancaX();
	GLfloat getMudancaY();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Janela();

private:
	GLFWwindow* mainWindow;
	 
	GLint widht, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat ultimoX, ultimoY;
	GLfloat mudancaX, mudancaY;
	bool mousePrimeiroMovimento;

	void criarCallbacks();

	static void keyHandler(GLFWwindow* window, int key, int code, int action, int mode);
	static void mouseHandler(GLFWwindow* window, double xPos, double yPos);
};

