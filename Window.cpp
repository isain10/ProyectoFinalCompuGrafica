#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	carro = 0.0f;
	heli = 0.0f;
	heli2 = 0.0f;
	lint = 0.0f;
	faro = 0.0f;
	animacionAvatar = 0.0f;
	posBrazoY = 0.0f;
	posBrazoZ = 0.0f;
	spot = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	carro = 0.0f;
	heli = 0.0f;
	rotacarro = 0.0f;
	muevex = 2.0f;
	heli2 = 0.0f;
	lint = 0.0f;
	faro = 0.0f;
	animacionAvatar = 0.0f;
	posBrazoY = 0.0f;
	posBrazoZ = 0.0f;
	spot = 0.0f;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto Final", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}

	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas

							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow->muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow->muevex -= 1.0;
	}

	if (key == GLFW_KEY_C)
	{
		theWindow->carro += 0.5;
		theWindow->faro = 0.0;
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->carro -= 0.5;
		theWindow->faro = 1.0f;
	}
	if (key == GLFW_KEY_Z)
	{
		theWindow->heli += 0.5;
	}
	if (key == GLFW_KEY_X)
	{
		theWindow->heli -= 0.5;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->heli2 += 1.0;
	}
	if (key == GLFW_KEY_H)
	{
		theWindow->heli2 -= 1.0;
	}
	if (key == GLFW_KEY_B)
	{
		
		if (theWindow->animacionAvatar < 145.0f)
			theWindow->animacionAvatar += 5.0f;
		
		if (theWindow->posBrazoY < 0.08f)
			theWindow->posBrazoY += 0.005f;

		if (theWindow->posBrazoZ < 0.25f)
			theWindow->posBrazoZ += 0.009f;
	}
	if (key == GLFW_KEY_N)
	{
		
		if (theWindow->animacionAvatar > 0.0f)
			theWindow->animacionAvatar -= 5.0f;
			
		if (theWindow->posBrazoY > 0.0f)
			theWindow->posBrazoY -= 0.005f;

		if (theWindow->posBrazoZ > 0.0f)
			theWindow->posBrazoZ -= 0.009f;
	}
	if (key == GLFW_KEY_M)
	{
		theWindow->lint = 1.0f;
	}
	if (key == GLFW_KEY_L)
	{
		theWindow->lint = 0.0f;
	}
	if (key == GLFW_KEY_W)
	{
		//theWindow->animacionAvatar += 500.0;
	}
	if (key == GLFW_KEY_9)
	{
		theWindow->spot = 1.0f;
	}
	if (key == GLFW_KEY_0)
	{
		theWindow->spot = 0.0f;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}