/*
Semestre 2022-2
Proyecto Computación Gráfica e Interacción Humano-Computadora
Arenas Sánchez Ulises Isain
Romo Gonzalez Alejandro
Valdovinos Antonio Fernando
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <irrKlang.h>
using namespace irrklang;

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;

float movCarroX = 61.784; //variable para movimiento del carro sobre eje X
float movCarroZ = 6.896;
float movCarroY = 0; //variable para movimiento del carro sobre eje Z
float rotCarroY = 90;
float rotCarroZ = 0;//variable para rotacion de carro sobre eje Y y simular movimiento
bool recorridoCarro = true; //Bandera para accionar el recorrido del carro
bool recorridoCarro1 = true; //Bandera para cordinar el recorrido 1 del carro
bool recorridoCarro2 = false; //Bandera para cordinar el recorrido 2 del carro
bool recorridoCarro3 = false; //Bandera para cordinar el recorrido 3 del carro
bool recorridoCarro4 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro5 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro6 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro7 = false; //Bandera para cordinar el recorrido 1 del carro
bool recorridoCarro8 = false; //Bandera para cordinar el recorrido 2 del carro
bool recorridoCarro9 = false; //Bandera para cordinar el recorrido 3 del carro
bool recorridoCarro10 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro11 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro12 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro13 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro14 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro15 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro16 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro17 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro18 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro19 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro20 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro21 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro22 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro23 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro24 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro25 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro26 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro27 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro28 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro29 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro30 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro31 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro32 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro33 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro34 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro35 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro36 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro37 = false; //Bandera para cordinar el recorrido 6 del carro

// Audio
ISoundEngine* SoundEngine = createIrrKlangDevice();

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture Dado8Texture;
Texture PistaTexture;
Texture LamparaTexture;
Texture PersonajeTexture;
Texture PaletaColores;
Texture Personaje2Texture;
Texture Personaje3Texture;
Texture Personaje4Texture;



Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;
Model Fiestast;
Model Lamp;
Model Troca;
Model Pista;
Model Avatar;
Model Brazo;
Model Pierna;
Model Lamp1;
Model Personaje2;
Model Personaje3;
Model Personaje4;

Skybox skybox;
Skybox skybox2;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";
void animacionCarro()
{
	if (recorridoCarro)
	{
		if (recorridoCarro1)
		{
			movCarroZ += 0.12;
			if (movCarroZ > 42)
			{
				recorridoCarro1 = false;
				recorridoCarro2 = true;
			}
		}

		if (recorridoCarro2)
		{
			movCarroX -= 0.12;
			movCarroZ += 0.12;
			rotCarroY += 1.8;
			if (rotCarroY > 180)
			{
				recorridoCarro2 = false;
				recorridoCarro3 = true;
			}
		}

		if (recorridoCarro3)
		{
			movCarroX -= 0.12;
			if (movCarroX < 6)
			{
				recorridoCarro3 = false;
				recorridoCarro4 = true;
			}
		}

		if (recorridoCarro4)
		{
			movCarroX -= 0.12;
			movCarroY += 0.06;
			rotCarroZ -= 1.2;
			if (rotCarroZ < -34)
			{
				recorridoCarro4 = false;
				recorridoCarro5 = true;

			}
		}

		if (recorridoCarro5)
		{
			movCarroX -= 0.12;
			movCarroY += 0.06;
			if (movCarroX < -8)
			{
				recorridoCarro5 = false;
				recorridoCarro6 = true;
			}
		}


		if (recorridoCarro6)
		{
			movCarroX -= 0.12;
			movCarroY -= 0.06;
			rotCarroZ += 1.2;
			if (rotCarroZ > 34)
			{
				recorridoCarro6 = false;
				recorridoCarro7 = true;
			}
		}

		if (recorridoCarro7)
		{
			movCarroX -= 0.12;
			movCarroY -= 0.06;
			rotCarroZ -= 1.2;
			if (rotCarroZ < 0)
			{
				recorridoCarro7 = false;
				recorridoCarro8 = true;
			}
		}

		if (recorridoCarro8)
		{
			movCarroX -= 0.12;
			movCarroY -= 0.06;
			if (movCarroY < 0)
			{
				recorridoCarro8 = false;
				recorridoCarro9 = true;
			}
		}
		if (recorridoCarro9)
		{
			movCarroX -= 0.12;
			if (movCarroX < -38)
			{
				recorridoCarro9 = false;
				recorridoCarro10 = true;
			}
		}
		if (recorridoCarro10)
		{
			movCarroX -= 0.12;
			movCarroZ += 0.12;
			rotCarroY -= 1.08;
			if (rotCarroY < 90)
			{
				recorridoCarro10 = false;
				recorridoCarro11 = true;
			}
		}

		if (recorridoCarro11)
		{
			movCarroX += 0.12;
			movCarroZ += 0.12;
			rotCarroY -= 1.08;
			if (rotCarroY < 0)
			{
				recorridoCarro11 = false;
				recorridoCarro12 = true;
			}
		}

		if (recorridoCarro12)
		{
			movCarroX += 0.12;
			if (movCarroX > -17)
			{
				recorridoCarro12 = false;
				recorridoCarro13 = true;
			}
		}

		if (recorridoCarro13)
		{
			movCarroX += 0.12;
			movCarroZ -= 0.12;
			rotCarroY -= 1.08;
			if (rotCarroY < -90)
			{
				recorridoCarro13 = false;
				recorridoCarro14 = true;
			}
		}

		if (recorridoCarro14)
		{
			movCarroZ -= 0.12;
			if (movCarroZ < 5)
			{
				recorridoCarro14 = false;
				recorridoCarro15 = true;
			}
		}

		if (recorridoCarro15)
		{
			movCarroX += 0.12;
			movCarroZ -= 0.12;
			rotCarroY += 1.2;
			if (rotCarroY > 0)
			{
				recorridoCarro15 = false;
				recorridoCarro16 = true;
			}
		}

		if (recorridoCarro16)
		{
			movCarroX += 0.12;
			if (movCarroX > 17)
			{
				recorridoCarro16 = false;
				recorridoCarro17 = true;
			}
		}

		if (recorridoCarro17)
		{
			movCarroX += 0.12;
			movCarroZ += 0.12;
			rotCarroY += 1.08;
			if (rotCarroY > 90)
			{
				recorridoCarro17 = false;
				recorridoCarro18 = true;
			}
		}

		if (recorridoCarro18)
		{
			movCarroX -= 0.12;
			movCarroZ += 0.12;
			rotCarroY += 1.08;
			if (rotCarroY > 180)
			{
				recorridoCarro18 = false;
				recorridoCarro19 = true;
			}
		}
		if (recorridoCarro19)
		{
			movCarroX -= 0.12;
			movCarroY += 0.024;
			rotCarroZ -= 0.48;
			if (rotCarroZ < -34)
			{
				recorridoCarro19 = false;
				recorridoCarro20 = true;

			}
		}

		if (recorridoCarro20)
		{
			movCarroX -= 0.12;
			movCarroY += 0.072;
			rotCarroZ += 0.24;
			if (rotCarroZ > 0)
			{
				recorridoCarro20 = false;
				recorridoCarro21 = true;

			}
		}

		if (recorridoCarro21)
		{
			movCarroX -= 0.12;
			movCarroY -= 0.066;
			rotCarroZ += 0.24;
			if (rotCarroZ > 34)
			{
				recorridoCarro21 = false;
				recorridoCarro22 = true;

			}
		}

		if (recorridoCarro22)
		{
			movCarroX -= 0.12;
			movCarroY -= 0.0312;
			rotCarroZ -= 0.48;
			if (rotCarroZ < 0)
			{
				recorridoCarro22 = false;
				recorridoCarro23 = true;

			}
		}

		if (recorridoCarro23)
		{
			movCarroX -= 0.12;
			movCarroY = 0;
			if (movCarroX < -70)
			{
				recorridoCarro23 = false;
				recorridoCarro24 = true;

			}
		}

		if (recorridoCarro24)
		{
			movCarroX -= 0.12;
			movCarroZ -= 0.12;
			rotCarroY += 1.08;
			if (rotCarroY > 270)
			{
				recorridoCarro24 = false;
				recorridoCarro25 = true;
			}
		}

		if (recorridoCarro25)
		{
			movCarroZ -= 0.12;
			if (movCarroZ < -40)
			{
				recorridoCarro25 = false;
				recorridoCarro26 = true;
			}
		}

		if (recorridoCarro26)
		{
			movCarroX += 0.12;
			movCarroZ -= 0.12;
			rotCarroY += 1.08;
			if (rotCarroY > 360)
			{
				recorridoCarro26 = false;
				recorridoCarro27 = true;
			}
		}

		if (recorridoCarro27)
		{
			movCarroX += 0.12;
			if (movCarroX > -6)
			{
				recorridoCarro27 = false;
				recorridoCarro28 = true;
				rotCarroY = 0;
			}
		}

		if (recorridoCarro28)
		{
			movCarroX += 0.12;
			movCarroZ -= 0.12;
			rotCarroY -= 1.08;
			if (rotCarroY < -90)
			{
				recorridoCarro28 = false;
				recorridoCarro29 = true;
			}
		}


		if (recorridoCarro29)
		{
			movCarroX += 0.12;
			movCarroZ -= 0.12;
			rotCarroY += 1.08;
			if (rotCarroY > 0)
			{
				recorridoCarro29 = false;
				recorridoCarro30 = true;
			}
		}

		if (recorridoCarro30)
		{
			movCarroX += 0.12;
			if (movCarroX > 70)
			{
				recorridoCarro30 = false;
				recorridoCarro31 = true;
			}
		}

		if (recorridoCarro31)
		{
			movCarroX += 0.12;
			movCarroZ += 0.12;
			rotCarroY += 1.08;
			if (rotCarroY > 90)
			{
				recorridoCarro31 = false;
				recorridoCarro32 = true;
			}
		}

		if (recorridoCarro32)
		{
			movCarroZ += 0.12;
			if (movCarroZ > -45)
			{
				recorridoCarro32 = false;
				recorridoCarro33 = true;
			}
		}
		if (recorridoCarro33)
		{
			movCarroX -= 0.12;
			movCarroZ += 0.12;
			rotCarroY += 1.32;
			if (rotCarroY > 180)
			{
				recorridoCarro33 = false;
				recorridoCarro34 = true;
			}
		}

		if (recorridoCarro34)
		{
			movCarroX -= 0.12;
			movCarroZ += 0.12;
			rotCarroY -= 1.08;
			if (rotCarroY < 90)
			{
				recorridoCarro34 = false;
				recorridoCarro35 = true;
			}
		}

		if (recorridoCarro35)
		{
			movCarroX = 61.784;
			movCarroZ += 0.12;
			if (movCarroZ > 6.896)
			{
				recorridoCarro35 = false;
				recorridoCarro1 = true;
			}
		}
	}
}




void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1920, 1080); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	//CrearDado();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	Dado8Texture = Texture("Textures/dado8.png");
	Dado8Texture.LoadTextureA();
	PistaTexture = Texture("Textures/textura_pista.png");
	PistaTexture.LoadTextureA();
	LamparaTexture = Texture("Textures/lampara.png");
	LamparaTexture.LoadTextureA();
	PersonajeTexture = Texture("Textures/personaje.png");
	PersonajeTexture.LoadTextureA();
	PaletaColores = Texture("Textures/TextureCarro2.png");
	PaletaColores.LoadTextureA();
	Personaje2Texture = Texture("Textures/TexturaPersonaje2.png");
	Personaje2Texture.LoadTextureA();
	Personaje3Texture = Texture("Textures/TexturaPersonaje3.png");
	Personaje3Texture.LoadTextureA();
	Personaje4Texture = Texture("Textures/TexturaPersonaje4.png");
	Personaje4Texture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");
	Fiestast = Model();
	Fiestast.LoadModel("Models/Carro2.fbx"); //fiestastcolor
	Lamp = Model();
	Lamp.LoadModel("Models/lamparaV.obj"); //StreetLamp
	Troca = Model();
	Troca.LoadModel("Models/troca.obj");
	Pista = Model();
	Pista.LoadModel("Models/Race_Track.fbx");
	Avatar = Model();
	Avatar.LoadModel("Models/Personaje2.fbx");
	Brazo = Model();
	Brazo.LoadModel("Models/brazo1.fbx");
	Pierna = Model();
	Pierna.LoadModel("Models/pierna.fbx");
	Lamp1 = Model();
	Lamp1.LoadModel("Models/lamparita.obj"); //StreetLamp
	Personaje2 = Model();
	Personaje2.LoadModel("Models/Personaje5.fbx");
	Personaje3 = Model();
	Personaje3.LoadModel("Models/Personaje3.fbx");
	Personaje4 = Model();
	Personaje4.LoadModel("Models/Personaje4.fbx");

	SoundEngine->play2D("sound/TokyoDrift.mp3", true);

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/rightDay.tga");
	skyboxFaces.push_back("Textures/Skybox/leftDay.tga");
	skyboxFaces.push_back("Textures/Skybox/bottomDay.tga");
	skyboxFaces.push_back("Textures/Skybox/topDay.tga");
	skyboxFaces.push_back("Textures/Skybox/backDay.tga");
	skyboxFaces.push_back("Textures/Skybox/frontDay.tga");

	/*skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");*/

	skybox = Skybox(skyboxFaces);
	std::vector<std::string> skyboxFaces2;
	skyboxFaces2.push_back("Textures/Skybox/rightNight.tga");
	skyboxFaces2.push_back("Textures/Skybox/leftNight.tga");
	skyboxFaces2.push_back("Textures/Skybox/bottomNight.tga");
	skyboxFaces2.push_back("Textures/Skybox/topNight.tga");
	skyboxFaces2.push_back("Textures/Skybox/backNight.tga");
	skyboxFaces2.push_back("Textures/Skybox/frontNight.tga");
	skybox2 = Skybox(skyboxFaces2);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;

	movCoche = 0.0f;
	movOffset = 0.2f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	float alturah = 0.0f;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	float control = 0.0f;
	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		animacionCarro();
		

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		/*glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());*/

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		if (((int)now / 30) % 2 == 0)  //pares 
		{

			//luz direccional, sólo 1 y siempre debe de existir            
			mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
				0.5f, 0.3f, // se cambio componente ambienta, la primera estaba en .3 la otra es componente difusa .15 dia
				0.0f, 0.0f, -1.0f); // la luz ilumina en z neg

			spotLights[2] = SpotLight(0.0f, 1.0f, 1.0f,
				0.5f, 1.0f,
				-135.0f, 5.0f, -55.0f,  // // hacia carritos, altura,- hacia casa-------------------------------------------------------------------
				-1.0f, -1.0f, -1.0f,
				1.0f, 0.0f, 0.0f,
				40.0f);
			spotLightCount++;


			spotLights[3] = SpotLight(0.0f, 1.0f, 0.0f,
				0.5f, 1.0f,
				-195.0f, 5.0f, -85.0f, // // hacia carritos, altura,- hacia casa ----------------------------------------------------  verde 
				1.0f, -1.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				40.0f);
			spotLightCount++;


			spotLights[4] = SpotLight(1.0f, 0.0f, 0.0f,
				0.5f, 1.0f,
				-135.0f, 5.0f, -115.0f,  // // hacia carritos, altura,- hacia casa-------------------------------------------------------------------
				-1.0f, -1.0f, 1.0f,
				1.0f, 0.0f, 0.0f,
				40.0f);
			spotLightCount++;

		}
		if (((int)now / 30) % 2 != 0) { // non
			//luz direccional, sólo 1 y siempre debe de existir            32 33 34 35 36 37           91 92 93 94 95 96 97 98 
			mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
				0.15f, 0.3f, // se cambio componente ambienta, la primera estaba en .3 la otra es componente difusa .15 noche
				0.0f, 0.0f, -1.0f); // la luz ilumina en z neg

			glfwPollEvents();
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			skybox2.DrawSkybox(camera.calculateViewMatrix(), projection);
			shaderList[0].UseShader();
			uniformModel = shaderList[0].GetModelLocation();
			uniformProjection = shaderList[0].GetProjectionLocation();
			uniformView = shaderList[0].GetViewLocation();
			uniformEyePosition = shaderList[0].GetEyePositionLocation();
			uniformColor = shaderList[0].getColorLocation();

			//información en el shader de intensidad especular y brillo
			uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
			uniformShininess = shaderList[0].GetShininessLocation();

			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
			glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

			// luz ligada a la cámara de tipo flash
			/*glm::vec3 lowerLight = camera.getCameraPosition();
			lowerLight.y -= 0.3f;
			spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());*/

			//información al shader de fuentes de iluminación
			shaderList[0].SetDirectionalLight(&mainLight);
			shaderList[0].SetPointLights(pointLights, pointLightCount);
			shaderList[0].SetSpotLights(spotLights, spotLightCount);


			if ((int)now % 2 == 0) {
				spotLights[2] = SpotLight(0.0f, 1.0f, 1.0f,
					0.5f, 1.0f,
					-135.0f, 5.0f, -55.0f,  // // hacia carritos, altura,- hacia casa-------------------------------------------------------------------
					-1.0f, -1.0f, -1.0f,
					1.0f, 0.0f, 0.0f,
					40.0f);
				spotLightCount++;


				spotLights[3] = SpotLight(0.0f, 1.0f, 0.0f,
					0.5f, 1.0f,
					-195.0f, 5.0f, -85.0f, // // hacia carritos, altura,- hacia casa ----------------------------------------------------  verde 
					1.0f, -1.0f, 0.0f,
					1.0f, 0.0f, 0.0f,
					40.0f);
				spotLightCount++;


				spotLights[4] = SpotLight(1.0f, 0.0f, 0.0f,
					0.5f, 1.0f,
					-135.0f, 5.0f, -115.0f,  // // hacia carritos, altura,- hacia casa-------------------------------------------------------------------
					-1.0f, -1.0f, 1.0f,
					1.0f, 0.0f, 0.0f,
					40.0f);
				spotLightCount++;
			}
			else {
				spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f,
					0.5f, 1.0f,
					-185.0f, 5.0f, -110.0f,  // // hacia carritos, altura,- hacia casa-------------------------------------------------------------------
					1.0f, -1.0f, 1.0f,
					1.0f, 0.0f, 0.0f,
					40.0f);
				spotLightCount++;
				spotLights[3] = SpotLight(1.0f, 1.0f, 0.0f,
					0.5f, 1.0f,
					-120.0f, 5.0f, -85.0f, // // hacia carritos, altura,- hacia casa ----------------------------------------------------
					-1.0f, -1.0f, 0.0f,
					1.0f, 0.0f, 0.0f,
					40.0f);
				spotLightCount++;
				spotLights[4] = SpotLight(1.0f, 0.0f, 0.0f,
					0.5f, 1.0f,
					-185.0f, 5.0f, -57.0f,  // // hacia carritos, altura,- hacia casa-------------------------------------------------------------------
					1.0f, -1.0f, -1.0f,
					1.0f, 0.0f, 0.0f,
					40.0f);
				spotLightCount++;

			}


		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		/*pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);*/

		//meshList[2]->RenderMesh();


		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.5f));

		//modelaux = model;
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Kitt_M.RenderModel();
		//

		// helicopter---------------------------------------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -1.0));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(mainWindow.getheli2(), mainWindow.getcarro(), mainWindow.getheli()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Blackhawk_M.RenderModel();

		//pista---------------------------------------------------------------------------------------------------------------------------------------------------------

		model = glm::mat4(1.0);
		glm::vec3 color3 = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.0f)); // en 10 altura
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PistaTexture.UseTexture();
		Pista.RenderModel();

		//lamparas------------------------------------------------iluminnacion---------------------------------------------------------------------------------------------------------
		glm::mat4 maux(1.0);


		model = glm::mat4(1.0);
		//model = maux;
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 3.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-2.5f, -0.75f, 7.0f));  // coches, arriba, casa
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LamparaTexture.UseTexture();
		Lamp.RenderModel();

		spotLights[0] = SpotLight(0.0f, 1.0f, 1.0f,
			0.5f, 1.0f,
			27.0f, 20.0f, 5.0f, // hacia carritos, altura,- hacia casa
			-0.0f, -1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			30.0f);
		spotLightCount++;


		model = glm::translate(model, glm::vec3(33.0f, 0.0f, 0.0f)); // 
		maux = model;
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamp.RenderModel();

		model = maux;
		//model = glm::mat4(1.0);
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -50.0f)); // 
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamp.RenderModel();

		model = glm::translate(model, glm::vec3(-56.5f, -0.0f, 29.0f)); // model = glm::translate(model, glm::vec3(-31.0f, -0.0f, 7.0f));
		maux = model;
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamp.RenderModel();


		pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
			6.0f, 5.0f,
			-30.0f, 7.0f, 57.5f,
			0.3f, 0.2f, 0.1f); // c,b,a chicharronera
		pointLightCount++;

		pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
			4.0f, 3.0f,
			-80.0f, 5.0f, -50.0f,
			0.3f, 0.2f, 0.1f); // c,b,a chicharronera
		pointLightCount++;

		pointLights[2] = PointLight(1.0f, 1.0f, 0.0f,
			4.0f, 3.0f,
			10.0f, 5.0f, -65.0f,  // hacia carritos, altura,- hacia casa 60.0f, 5.0f, 1.5f
			0.3f, 0.2f, 0.1f); // c,b,a chicharronera


		if (mainWindow.getlint() == 1.0f) {
			pointLightCount = 0;
		}
		else
			pointLightCount = 3;


		model = maux;
		/*model = glm::mat4(1.0);
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));*/
		model = glm::translate(model, glm::vec3(78.0f, 4.4f, -9.0f));  // coches, arriba, casa
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamp1.RenderModel();

		spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f, // luz de la casa
			1.0f, 1.0f,
			-46.0f, 25.0f, -100.0f, // // hacia carritos, altura,- hacia casa
			0.0f, -1.0f, 1.0f,
			1.0f, 0.0f, 0.0f,
			30.0f);
		spotLightCount++;


		if (mainWindow.getspot() == 1.0f) {
			spotLightCount = 0;
		}
		else
			spotLightCount = 5;


		//avatar---------------------------------------------------------------------------------------------------------------------------------------------------------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, -1.75f, -7.0f));  // coches, arriba, casa   0,1,56
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//maux = model; // no heredar  funciona
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Personaje2Texture.UseTexture();
		Personaje2.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, -0.0f, -100.0f));  // coches, arriba, casa   0,1,56
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//maux = model; // no heredar  funciona
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Personaje3Texture.UseTexture();
		Personaje3.RenderModel();
		//--------------------------------------------------------------------------------------------------




		//---------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, -1.5f, 8.0f));  // coches, arriba, casa   0,1,56
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//maux = model; // no heredar  funciona
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Personaje4Texture.UseTexture();
		Personaje4.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(camera.getCameraPosition().x + 4.0f, camera.getCameraPosition().y, camera.getCameraPosition().z));  // coches, arriba, casa   0,1,56 camera.getCameraPosition() +1.0f (7.0f, -1.5f, 8.0f
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, camera.getCameraDirection());
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//maux = model; // no heredar  funciona
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PersonajeTexture.UseTexture();
		Avatar.RenderModel();


		// brazo derecho------------------------------------------------------------------------------------
		//model = maux; funciona
		maux = model;
		//model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-mainWindow.getanimacionAvatar() * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));

		model = maux; // no heredar funciona
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -0.2f));  // coches, arriba, casa
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 20.0f, -0.0f));  // coches, arriba, casa
		maux = model; //funciona
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PersonajeTexture.UseTexture();
		Brazo.RenderModel();

		// brazo izquierdo ------------------------------------------------------------------------------------

		//maux = model;// no heredar
		//model = glm::rotate(model, glm::radians(-mainWindow.getanimacionAvatar() * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = maux;// funcinoa
		model = glm::translate(model, glm::vec3(0.0f, 0.37f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -mainWindow.getanimacionAvatar() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -mainWindow.getposBrazoY(), -mainWindow.getposBrazoZ()));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PersonajeTexture.UseTexture();
		Brazo.RenderModel();

		// pierna derecha ------------------------------------------------------------------------------------
		model = maux;//heredar
		model = glm::translate(model, glm::vec3(0.2f, 0.07f, -0.47f));  // coches, arriba, casa
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PersonajeTexture.UseTexture();
		Pierna.RenderModel();

		// pierna izquierda------------------------------------------------------------------------------------

		model = glm::translate(model, glm::vec3(0.0f, 0.1f, -0.0f));  // coches, arriba, casa
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PersonajeTexture.UseTexture();
		Pierna.RenderModel();


		//carro st---------------------------------------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0);
		glm::vec3 color2 = glm::vec3(1.0f, 0.0f, 0.0f);

		model = glm::translate(model, glm::vec3(-0.0f, -0.8f, 0.0f));// hacia carritos,altura,-hacia casa
		model = glm::translate(model, glm::vec3(movCarroX, movCarroY, movCarroZ));
		model = glm::rotate(model, glm::radians(-rotCarroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotCarroZ), glm::vec3(0.0f, 0.0f, 0.1f));
		/*model = glm::rotate(model, glm::radians(mainWindow.getrotacarro() * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::translate(model, glm::vec3(mainWindow.getheli2(), 0.0f, mainWindow.getcarro()));*/

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PaletaColores.UseTexture();
		Fiestast.RenderModel();


		//view = camera.GetViewMatrix();
		//model = glm::mat4(1);
		////CORDENADAS BASE
		////model = glm::translate(model, glm::vec3(61.784f, 0.0f, 6.896f));
		////model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(movCarroX, movCarroY, movCarroZ));
		//model = glm::rotate(model, glm::radians(-rotCarroY), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(-rotCarroZ), glm::vec3(0.0f, 0.0f, 0.1f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//CarroPista.Draw(lightingShader);


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}