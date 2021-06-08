#define GLM_FORCE_RADIANS

#include "includes.h"
#include "wall.h"
#include "creeper.h"
#include "map.h"


extern float wallSegmentVertices[];
extern float wallSegmentTexCoords[];
extern float wallSegmentNormals[];

WallSegment wallSegment;	// Obiekt segmentu ściany
Creeper creeper;			// Obiekt głównej postaci

bool go_left, go_right, go_up, go_down;		// wydarzenie zmieniajace kierunek
float window_width = 1280;
float window_height = 720;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod ) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) 
			go_left = true;
		if (key == GLFW_KEY_RIGHT) 
			go_right = true;
		if (key == GLFW_KEY_UP) 
			go_up = true;
		if (key == GLFW_KEY_DOWN) 
			go_down = true;
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

void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);

	//wczytanie tekstury ścian
	wallSegment.readTexture("./textures/bricks/bricks.png");
	creeper.readTexture("./textures/creeper/AA1.png");
	creeper.loadModel("./textures/creeper/Minecraft_Creeper.fbx");

	// skalowanie rozmiaru modelu
	creeper.position = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	creeper.position = glm::scale(creeper.position, glm::vec3(0.25f, 0.25f, 0.25f));
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();

	// zwalnianie tekstur
	glDeleteTextures(1, &creeper.texture);
	glDeleteTextures(1, &wallSegment.texture);
}

void move()
{
	creeper.position = glm::scale(creeper.position, glm::vec3(4.0f, 4.0f, 4.0f));
	int licznik = 0;

	if (go_right)
		licznik++;
	if (go_left)
		licznik++;
	if (go_up)
		licznik++;
	if (go_down)
		licznik++;

	if (licznik == 1) {
		if (floorf(creeper.position_x) == creeper.position_x) //sprawdzenie czy float ma wartość całkowitą
		{
			if (go_left && map[int(creeper.position_x)+ 1][int(creeper.position_z)] != 1)
			{
				creeper.direction = "left";
			}
			if (go_right && map[int(creeper.position_x - 1)][int(creeper.position_z)] != 1)
			{
				creeper.direction = "right";
			}
		}
		if (floorf(creeper.position_z) == creeper.position_z) //sprawdzenie czy float ma wartość całkowitą
		{
			if (go_up && map[int(creeper.position_x)][int(creeper.position_z)+1] != 1)
			{
				creeper.direction = "up";
			}
			if (go_down && map[int(creeper.position_x)][int(creeper.position_z)-1] != 1)
			{
				creeper.direction = "down";
			}
		}
	}

	if (creeper.direction == "up")
	{
		if (map[int(creeper.position_x)][int(creeper.position_z) + 1] != 1)
		{
			creeper.position_z += creeper.movingSpeed;
			creeper.position = glm::translate(creeper.position, glm::vec3(0, 0, creeper.movingSpeed));
			std::cout << creeper.position_x << " " << creeper.position_z << std::endl;
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
	creeper.position = glm::scale(creeper.position, glm::vec3(0.25f, 0.25f, 0.25f));
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

	glm::mat4 V = glm::lookAt(glm::vec3(map_width/2, 10.0f, -map_height/2), glm::vec3(4.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	glm::mat4 P = glm::perspective(glm::radians(50.0f), window_width/window_height, 1.0f, 50.0f);


	move();
	//creeper.move();

	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			if (map[i][j] == 1)
				wallSegment.drawSegment(glm::scale(glm::translate(
				glm::mat4(1.0f), glm::vec3(i, 0, j)), glm::vec3(0.5f, 0.5f, 0.5f)));
		}
	}
	creeper.drawModel();

	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}


int main(void)
{
	GLFWwindow* window;	
	wallSegment = WallSegment();
	creeper = Creeper();

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
