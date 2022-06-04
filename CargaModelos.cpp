/*
Semestre 2022-2
Pr�ctica 5: Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

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

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture DadoTexture;
Texture Dado8Texture;


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;

Model Fiestast;
Model Helice;
Model Troca;
Model Arbol;
Model Llantafist;
Model Carrofist;




Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


// c�lculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
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
	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);
}


void CrearDado()
{
	unsigned int cubo_indices[] = {
		
		/*// front arriba
		0, 1, 2,
		2, 3, 0,
		// right arriba
		4, 5, 6,
		6, 7, 4,
		// back arriba
		8, 9, 10,
		10, 11, 8,

		// left arriba
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
		
		*/

		
		// front arriba
		0, 1, 2,

		// right arriba
		3, 4, 5,
		// back arriba
		6,7 , 8,
		// left arriba
		9,10 , 11,

		// front abajo
		12, 13, 14,
		// derecha abajo
		15,16, 17,
		// atras abajo
		18,19 , 20,
		// izquierda abajo
		21,22 , 23,
		
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		
		// frontal arriba
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.0f,  0.5f,	0.389f,  0.5f,		0.0f,	-0.5f,	-0.5f,	//0
		0.5f, -0.0f,  0.5f,		0.650f,	0.5f,		0.0f,	-0.5f,	-0.5f,	//1
		0.0f,  0.5f,  0.0f,		0.52f,	0.728f,		0.0f,	-0.5f,	-0.5f,	//2 punto superior

		// right arriba
		//x		y		z		S		T
		0.5f, -0.0f,  0.5f,	    0.640f,	0.5f,		-0.5f,	-0.5f,	0.0f,	//1
		0.5f, -0.0f,  -0.5f,	0.770f,	0.728f,		-0.5f,	-1.0f,	0.0f,	//3
		0.0f,  0.5f,  0.0f,		0.52f,	0.728f,		-0.5f,	-0.5f,	0.0f,	//punto superior

		// back arriba
		0.5f, -0.0f,  -0.5f,	0.39f,	0.94f,		0.0f,	-0.5f,	0.5f,	//3
		-0.5f, -0.0f,  -0.5f,	0.260f,	0.728f,		0.0f,	-0.5f,	0.5f,	//4
		0.0f,  0.5f,  0.0f,		0.5f,	0.728f,		0.0f,	-0.5f,	0.5f,	//punto superior


		// left arriba
		//x		y		z		S		T
		-0.5f, -0.0f,  -0.5f,	0.260f,	0.728f,		0.5f,	-0.5f,	0.0f,	//4
		-0.5f, -0.0f,  0.5f,	0.389f,  0.5f,		0.5f,	-0.5f,	0.0f,	//5
		0.0f,  0.5f,  0.0f,		0.52f,	0.728f,		0.5f,	-0.5f,	0.0f,	//punto superior


		// frontal abajo----------------
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.0f,  0.5f,	0.389f,  0.5f,		0.0f,	0.5f,	-0.5f,	//0
		0.5f, -0.0f,  0.5f,		0.650f,	0.5f,		0.0f,	0.5f,	-0.5f,	//1
		0.0f,  -0.5f,  0.0f,	0.52f,	0.271f,		0.0f,	0.5f,	-0.5f,	//6

		// right abajo
		//x		y		z		S		T
		0.5f, -0.0f,  0.5f,	    0.650f,	0.5f,		-0.5f,	0.5f,	0.0f,	//1
		0.5f, -0.0f,  -0.5f,	0.78f,	0.271f,		-0.5f,	0.5f,	0.0f,	//3
		0.0f,  -0.5f,  0.0f,	0.52f,	0.271f,		-0.5f,	0.5f,	0.0f,	//6 punto bajo

		// back abajo
		0.5f, -0.0f,  -0.5f,	0.39f,	0.062f,		0.0f,	0.5f,	0.5f,	//3
		-0.5f, -0.0f,  -0.5f,	0.26f,	0.271f,		0.0f,	0.5f,	0.5f,	//4
		0.0f,  -0.5f,  0.0f,	0.5f,	0.271f,		0.0f,	0.5f,	0.5f,	//6punto bajo


		// left abajo
		//x		y		z		S		T
		-0.5f, -0.0f,  -0.5f,	0.26f,	0.271f,		0.5f,	0.5f,	0.0f,	//4
		-0.5f, -0.0f,  0.5f,	0.389f,  0.5f,		0.5f,	0.5f,	0.0f,	//5
		0.0f,  -0.5f,  0.0f,	0.52f,	0.271f,		0.5f,	0.5f,	0.0f,	//6punto bajo
		

		/*
		// front-------------------------------------------------------------------------------
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.340f,  0.55f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.660f,	0.55f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.660f,	0.76f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.340f,	0.76f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.660f,	0.55f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.55f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	0.76f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.660f,	0.76f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.34f,  0.06f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.66f,	0.06f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.66f,	0.28f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.34f,	0.28f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.55f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.34f,	0.55f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.34f,	0.76f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.76f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.34f,  0.3f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.66f,	0.3f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.66f,	0.51f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.34f,	0.51f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.34f,  0.76f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.66f,	0.76f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.66f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.34f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 */
	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 24);
	meshList.push_back(dado);

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
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
	DadoTexture = Texture("Textures/accion_dado.png");
	DadoTexture.LoadTextureA();
	Dado8Texture = Texture("Textures/dado8.png");
	Dado8Texture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kit_obj.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60_nomotor.fbx");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");

	Fiestast = Model();
	Fiestast.LoadModel("Models/fiestast.obj");
	Troca = Model();
	Troca.LoadModel("Models/troca.obj");
	Arbol = Model();
	Arbol.LoadModel("Models/arbol1.obj");
	Llantafist = Model();
	Llantafist.LoadModel("Models/llantafist.obj");
	Carrofist = Model();
	Carrofist.LoadModel("Models/fiestasinllantas.obj");

	

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

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
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);




		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);





		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//dado
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, 2.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Dado8Texture.UseTexture();
		meshList[4]->RenderMesh();

		/*
		//helicoptero
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 8.0f, -1.0));
		modelaux = model;
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Blackhawk_M.RenderModel();
		*/

		// helicoptero--------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 30.0f, -0.0));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice.RenderModel();

		/*
		//camino
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.53f, -4.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Camino_M.RenderModel();
		*/

		// camino
		model = glm::mat4(1.0);
		//glm::vec3 colorverde = glm::vec3(0.0f, 1.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(colorverde));
		model = glm::translate(model, glm::vec3(0.0f, -1.53f, -0.5f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();


		//coche
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Kitt_M.RenderModel();

		//llantas
		color = glm::vec3(0.5f, 0.5f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.8f, -0.5f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_M.RenderModel();

		color = glm::vec3(0.5f, 0.2f, 0.70f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.8f, -0.5f, -1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_M.RenderModel();

		color = glm::vec3(0.9f, 0.7f, 0.35f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.3f, -0.5f, -1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_M.RenderModel();

		color = glm::vec3(0.71f, 0.86f, 0.61f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.3f, -0.5f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_M.RenderModel();

		
		// carro voxel--------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, -0.8f, -0.0f));

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Troca.RenderModel();

		// arbol voxel--------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 6.0f, 25.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));

		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol.RenderModel();

		/*
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.53f, -0.5f));
		model = glm::scale(model, glm::vec3(30.0f,1.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		//llanta trasera izquierda


		model = glm::mat4(1.0);
		glm::vec3 colorverde = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorverde));
		//model = modelaux;
		model = glm::translate(model, glm::vec3(-0.7f, -0.3f, -1.85f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//llanta enfrente izquierda
		model = glm::mat4(1.0);
		glm::vec3 colorazul = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorazul));
		model = glm::translate(model, glm::vec3(-2.8f, -0.3f, -1.85f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//llanta trasera derecha

		model = glm::mat4(1.0);
		glm::vec3 colormag = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(colormag));
		model = glm::translate(model, glm::vec3(-0.7f, -0.3f, -3.25f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//llanta enfrente derecha
		model = glm::mat4(1.0);
		glm::vec3 colorama = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorama));
		model = glm::translate(model, glm::vec3(-2.8f, -0.3f, -3.25f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		*/
		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}