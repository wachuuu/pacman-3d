/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


const float speed = 1; // prędkość postaci
std::string direction;
GLuint tex, tex_brick; //Uchwyt – deklaracja globalna

//tu stworzyc klase obiekt i tam przechowywac tablice
std::vector<glm::vec4> verts;
std::vector<glm::vec4> norms;
std::vector<glm::vec2> texCoords2;
std::vector<unsigned int> indices;
const int mapa_wys = 8;
const int mapa_szer = 8;
int mapa[mapa_wys][mapa_szer] = { {1,1,1,1,1,1,1,1},
								{1,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,1},
								{1,1,1,1,1,1,1,1} };
glm::mat4 position;
float position_x = 1;
float position_z = 1;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}
bool go_left, go_right, go_up, go_down;
void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			go_left = true;
		}
		if (key == GLFW_KEY_RIGHT) {
			go_right = true;
		}
		if (key == GLFW_KEY_UP) {
			go_up = true;
		}
		if (key == GLFW_KEY_DOWN) {
			go_down = true;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT)
			go_left = false;
		if (key == GLFW_KEY_RIGHT)
			go_right = false;
		if (key == GLFW_KEY_UP)
			go_up = false;
		if (key == GLFW_KEY_DOWN)
			go_down = false;
	}
}

GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void loadModel(std::string plik) {
	using namespace std;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(plik,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
	cout << importer.GetErrorString() << endl;

	aiMesh* mesh = scene->mMeshes[0];
	for (int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D vertex = mesh->mVertices[i];

		verts.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

		aiVector3D normal = mesh->mNormals[i];
		norms.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

		aiVector3D texCoord = mesh->mTextureCoords[0][i];
		texCoords2.push_back(glm::vec2(texCoord.x, texCoord.y));
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace& face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);

	tex = readTexture("./textures/creeper/AA1.png");
	tex_brick = readTexture("bricks.png");
	loadModel(std::string("./textures/creeper/Minecraft_Creeper.fbx"));
	position = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 1));
	position = glm::scale(position, glm::vec3(0.25f, 0.25f, 0.25f));
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1, &tex);
	glDeleteTextures(1, &tex_brick);
}

void drawBrick(glm::mat4 M)
{
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices);
	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, myCubeNormals);
	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myCubeTexCoords);

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, tex_brick); glUniform1i(spLambertTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);
	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
}

void move()
{
	if (direction == "up")
	{
		if (mapa[int(position_x)][int(position_z) + 1] != 1)
		{
			position_z += speed;
			position = glm::translate(position, glm::vec3(0, 0, speed));
			std::cout << position_x << " " << position_z << std::endl;
		}
	}
	if (direction == "down")
	{
		if (mapa[int(position_x)][int(position_z) - 1] != 1)
		{
			position_z -= speed;
			position = glm::translate(position, glm::vec3(0, 0, -speed));
		}
	}
	if (direction == "left")
	{
		if (mapa[int(position_x) + 1][int(position_z)] != 1)
		{
			position_x += speed;
			position = glm::translate(position, glm::vec3(speed, 0, 0));
		}
	}
	if (direction == "right")
	{
		if (mapa[int(position_x) - 1][int(position_z)] != 1)
		{
			position_x -= speed;
			position = glm::translate(position, glm::vec3(-speed, 0, 0));
		}
	}
	int licznik = 0;
	if (go_right)
		licznik++;
	if (go_left)
		licznik++;
	if (go_up)
		licznik++;
	if (go_down)
		licznik++;
	if (licznik == 1)
	{
		if (floorf(position_x) == position_x) //sprawdzenie czy float ma wartość całkowitą
		{
			if (go_left && mapa[int(position_x)+ 1][int(position_z)] != 1)
			{
				direction = "left";
			}
			if (go_right && mapa[int(position_x - 1)][int(position_z)] != 1)
			{
				direction = "right";
			}
		}
		if (floorf(position_z) == position_z) //sprawdzenie czy float ma wartość całkowitą
		{
			if (go_up && mapa[int(position_x)][int(position_z)+1] != 1)
			{
				direction = "up";
			}
			if (go_down && mapa[int(position_x)][int(position_z)-1] != 1)
			{
				direction = "down";
			}
		}
	}
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

	//M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f)); //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y
	//M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f)); //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi X
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 15.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	//Tablica współrzędnych teksturowania - wklejona do pliku myCube.h
	//Tablica wektorow normalnych - wklejona do pliku myCube.h

	position = glm::scale(position, glm::vec3(4.0f, 4.0f, 4.0f));
	move();
	position = glm::scale(position, glm::vec3(0.25f, 0.25f, 0.25f));
	

	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));
	for (int i = 0; i < mapa_wys; i++)
	{
		for (int j = 0; j < mapa_szer; j++)
		{
			if (mapa[i][j] == 1)
				drawBrick(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0, j)), glm::vec3(0.5f, 0.5f, 0.5f)));
		}
	}
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(position));

	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, verts.data());

	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, norms.data());

	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords2.data());

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, tex); glUniform1i(spLambertTextured->u("tex"), 0);

	//glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));

	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1280, 720, "Pac-Man 3D", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float angle_y = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	glfwSetTime(0); //Wyzeruj licznik czasu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
