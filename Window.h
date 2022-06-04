#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getposBrazoY() { return posBrazoY; }
	GLfloat getposBrazoZ() { return posBrazoZ; }
	GLfloat getcarro() { return carro; }
	GLfloat getheli() { return heli; }
	GLfloat getheli2() { return heli2; }
	GLfloat getlint() { return lint; }
	GLfloat getfaro() { return faro; }
	GLfloat getrotacarro() { return rotacarro; }
	GLfloat getanimacionAvatar() { return animacionAvatar; }
	GLfloat getspot() { return spot; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat carro;
	GLfloat heli;
	GLfloat heli2;
	GLfloat rotacarro;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat muevey;
	GLfloat posBrazoY;
	GLfloat posBrazoZ;
	GLfloat lint;
	GLfloat faro;
	GLfloat animacionAvatar;
	GLfloat spot;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};