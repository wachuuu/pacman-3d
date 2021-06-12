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

void move() {
	creeper.position = glm::scale(creeper.position, glm::vec3(4.0f, 4.0f, 4.0f));
	int licznik = 0;

	std::cout << "x: " << creeper.position_x << " " << floorf(creeper.position_x+0.1) << ";  y:" << creeper.position_z << " " << floorf(creeper.position_z+0.1) << std::endl;
	std::cout << creeper.direction << std::endl;


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
		if (floorf(creeper.position_x) == creeper.position_x) //sprawdzenie czy float ma wartość całkowitą
		{
			if (creeper.go_left && map[int(creeper.position_x) + 1][int(creeper.position_z)] != 1)
			{
				creeper.direction = "left";
			}
			if (creeper.go_right && map[int(creeper.position_x) - 1][int(creeper.position_z )] != 1)
			{
				creeper.direction = "right";
			}
		}
		if (floorf(creeper.position_z) == creeper.position_z) //sprawdzenie czy float ma wartość całkowitą
		{
			if (creeper.go_up && map[int(creeper.position_x)][int(creeper.position_z) + 1] != 1)
			{
				creeper.direction = "up";
			}
			if (creeper.go_down && map[int(creeper.position_x)][int(creeper.position_z) - 1] != 1)
			{
				creeper.direction = "down";
			}
		}
	}

	// właściwy ruch modelu
	if (creeper.direction == "up")
	{
		if (map[int(creeper.position_x)][int(creeper.position_z) + 1] != 1)
		{
			creeper.position_z += creeper.movingSpeed;
			creeper.position = glm::translate(creeper.position, glm::vec3(0, 0, creeper.movingSpeed));
		}
	}
	if (creeper.direction == "down")
	{
		if (map[int(creeper.position_x)][int(creeper.position_z) - 1] != 1)
		{
			creeper.position_z -= creeper.movingSpeed;
			creeper.position = glm::translate(creeper.position, glm::vec3(0, 0, -creeper.movingSpeed));
		}
	}
	if (creeper.direction == "left")
	{
		if (map[int(creeper.position_x) + 1][int(creeper.position_z)] != 1)
		{
			creeper.position_x += creeper.movingSpeed;
			creeper.position = glm::translate(creeper.position, glm::vec3(creeper.movingSpeed, 0, 0));
		}
	}
	if (creeper.direction == "right")
	{
		if (map[int(creeper.position_x) - 1][int(creeper.position_z)] != 1)
		{
			creeper.position_x -= creeper.movingSpeed;
			creeper.position = glm::translate(creeper.position, glm::vec3(-creeper.movingSpeed, 0, 0));
		}
	}

	// zaznaczenie odwieczonego pola (zebranie monety)
	// jezeli model jest na całkowitym polu
	map[int(creeper.position_x+0.1)][int(creeper.position_z+0.1)] = 2; // ustaw pole jako odwiedzone
	

	creeper.position = glm::scale(creeper.position, glm::vec3(0.25f, 0.25f, 0.25f));
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 V = glm::lookAt(glm::vec3(5.0f, 15.0f, -1.0f), glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 P = glm::perspective(glm::radians(50.0f), window_width / window_height, 1.0f, 50.0f);


	move();

	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));

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

	//Główna pętla
	while (!glfwWindowShouldClose(window)) {
		glfwSetTime(0); 
		drawScene(window); 
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
