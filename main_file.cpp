#define GLM_FORCE_RADIANS

#include "includes.h"
#include "wall.h"
#include "creeper.h"
#include "map.h"
#include "coin.h"

extern float wallSegmentVertices[];
extern float wallSegmentTexCoords[];
extern float wallSegmentNormals[];

WallSegment wallSegment;	// Obiekt segmentu ściany
Creeper creeper;			// Obiekt głównej postaci
Coin coin;


// współrzędne światła
std::vector<glm::vec3> lightPos = {
	glm::vec3(5.0f, 15.0f, -10.0f),
	glm::vec3(25.0f, 20.0f, 13.0f),
	glm::vec3(-15.0f, 20.0f, 13.0f),
	glm::vec3(5.0f, 20.0f, 35.0f)
};

float window_width = 1280;
float window_height = 720;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod ) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) 
			creeper.go_left = true;
		if (key == GLFW_KEY_RIGHT) 
			creeper.go_right = true;
		if (key == GLFW_KEY_UP) 
			creeper.go_up = true;
		if (key == GLFW_KEY_DOWN) 
			creeper.go_down = true;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT)
			creeper.go_left = false;
		if (key == GLFW_KEY_RIGHT)
			creeper.go_right = false;
		if (key == GLFW_KEY_UP)
			creeper.go_up = false;
		if (key == GLFW_KEY_DOWN)
			creeper.go_down = false;
	}
}

void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);

	//wczytanie tekstury ścian
	wallSegment.readTexture("./textures/bricks/bricks.png");
	creeper.readTexture("./textures/creeper/AA1.png");
	creeper.loadModel("./textures/creeper/Minecraft_Creeper.fbx");
	coin.readTexture("./textures/coin/coinTex.png");
	coin.loadModel("./textures/coin/Coin.fbx");
	// skalowanie rozmiaru modelu
	creeper.position = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	creeper.position = glm::scale(creeper.position, glm::vec3(0.25f, 0.25f, 0.25f));


}

void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();

	// zwalnianie tekstur
	glDeleteTextures(1, &creeper.texture);
	glDeleteTextures(1, &coin.texture);
	glDeleteTextures(1, &wallSegment.texture);
}

bool winCheck() //sprawdza czy zebrano wszystkie monety
{
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
			if (map[i][j] == 0)
				return false;
	return true;
}

void move() {
	creeper.position = glm::scale(creeper.position, glm::vec3(4.0f, 4.0f, 4.0f));
	int licznik = 0;

	//std::cout << "x: " << creeper.realPositionX << " z: " << creeper.realPositionZ << std::endl;
	if (creeper.realPositionX % creeper.movingSpeed == 0)
		creeper.arrayPositionX = creeper.realPositionX / creeper.movingSpeed;
	if (creeper.realPositionZ % creeper.movingSpeed == 0)
		creeper.arrayPositionZ = creeper.realPositionZ / creeper.movingSpeed;


	// rozwiazanie konfliktu klawiszy
	// model porusza sie tylko w jednym kierunku jednoczesnie
	if (creeper.go_right)
		licznik++;
	if (creeper.go_left)
		licznik++;
	if (creeper.go_up)
		licznik++;
	if (creeper.go_down)
		licznik++;

	// ustalenie kierunku lub kolizji
	if (licznik == 1) {
		if (creeper.realPositionX % creeper.movingSpeed == 0 && creeper.realPositionZ % creeper.movingSpeed == 0)
		{
			if (creeper.go_left && map[creeper.arrayPositionX + 1][creeper.arrayPositionZ] != 1)
			{
				creeper.direction = "left";
			}
			if (creeper.go_right && map[creeper.arrayPositionX - 1][creeper.arrayPositionZ] != 1)
			{
				creeper.direction = "right";
			}
		}
		if (creeper.realPositionX % creeper.movingSpeed == 0 && creeper.realPositionZ % creeper.movingSpeed == 0)
		{
			if (creeper.go_up && map[creeper.arrayPositionX][creeper.arrayPositionZ + 1] != 1)
			{
				creeper.direction = "up";
			}
			if (creeper.go_down && map[creeper.arrayPositionX][creeper.arrayPositionZ - 1] != 1)
			{
				creeper.direction = "down";
			}
		}
		//std::cout << "-------------------------------\n" + creeper.direction << std::endl;
	}

	// właściwy ruch modelu
	if (creeper.direction == "up")
	{
		if (map[creeper.arrayPositionX][creeper.arrayPositionZ + 1] != 1)
		{
			creeper.realPositionZ += 1;
			creeper.position = glm::translate(creeper.position, glm::vec3(0, 0, 1.0f / (float) creeper.movingSpeed));
		}
	}
	if (creeper.direction == "down")
	{
		if (map[creeper.arrayPositionX][creeper.arrayPositionZ - 1] != 1)
		{
			creeper.realPositionZ -= 1;
			creeper.position = glm::translate(creeper.position, glm::vec3(0, 0, -1.0f / (float) creeper.movingSpeed));
		}
	}
	if (creeper.direction == "left")
	{
		if (map[creeper.arrayPositionX + 1][creeper.arrayPositionZ] != 1)
		{
			creeper.realPositionX += 1;
			creeper.position = glm::translate(creeper.position, glm::vec3(1.0f / (float) creeper.movingSpeed, 0, 0));
		}
	}
	if (creeper.direction == "right")
	{
		if (map[creeper.arrayPositionX - 1][creeper.arrayPositionZ] != 1)
		{
			creeper.realPositionX -= 1;
			creeper.position = glm::translate(creeper.position, glm::vec3(-1.0f / (float) creeper.movingSpeed, 0, 0));
		}
	}
	
	// zaznaczenie odwiedzonego pola (zebranie monety)
	// jezeli model jest na całkowitym polu
	if(creeper.realPositionX % creeper.movingSpeed == 0 && creeper.realPositionZ % creeper.movingSpeed == 0)
		map[creeper.realPositionX / creeper.movingSpeed][creeper.realPositionZ / creeper.movingSpeed] = 2; // ustaw pole jako odwiedzone

	creeper.position = glm::scale(creeper.position, glm::vec3(0.25f, 0.25f, 0.25f));
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec4 lightPosition1 = glm::vec4(lightPos[0], 1.f);
	glm::vec4 lightPosition2 = glm::vec4(lightPos[1], 1.f);
	glm::vec4 lightPosition3 = glm::vec4(lightPos[2], 1.f);
	glm::vec4 lightPosition4 = glm::vec4(lightPos[3], 1.f);

	glm::mat4 V = glm::lookAt(glm::vec3(5.0f, 15.0f, -1.0f), glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 P = glm::perspective(glm::radians(50.0f), window_width / window_height, 1.0f, 50.0f);

	move();

	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));

	glUniform4fv(spLambertTextured->u("lpos1"), 1, glm::value_ptr(lightPosition1));
	glUniform4fv(spLambertTextured->u("lpos2"), 1, glm::value_ptr(lightPosition2));
	glUniform4fv(spLambertTextured->u("lpos3"), 1, glm::value_ptr(lightPosition3));
	glUniform4fv(spLambertTextured->u("lpos4"), 1, glm::value_ptr(lightPosition4));

	wallSegment.drawMap(map);
	creeper.drawModel();
	coin.placeCoins(map);

	glfwSwapBuffers(window);
}

int main(void)
{
	GLFWwindow* window;	
	wallSegment = WallSegment();
	creeper = Creeper();
	coin = Coin();
	coin.loadMap(map);

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) { 
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(window_width, window_height, "Pac-Man 3D", NULL, NULL); 

	if (!window) {
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); 
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) { 
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); 

	while (!glfwWindowShouldClose(window)) {
		glfwSetTime(0); 
		drawScene(window); 
		glfwPollEvents();
		if (winCheck())
		{
			std::cout << "Wygrales! \n \"Lata rozpadaja sie na miesiace, miesiace na dni, dni na godziny, minuty na sekundy, a sekundy przeciekaja. \n Czy jestem? Jestem pewna iloscia sekund- ktore przeciekly.\n Rezultat: nic. Nic. \"" << std::endl;
			break;
		}
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
