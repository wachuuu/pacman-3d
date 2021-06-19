#ifndef ghost_h
#define ghost_h

#include "includes.h"

class Ghost {
public:
	int map[11][11] = {
	{1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,1},
	{1,0,0,0,1,0,1,0,0,0,1},
	{1,1,1,0,1,0,1,0,1,1,1},
	{1,0,0,0,1,0,1,0,0,0,1},
	{1,0,1,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,2,1},
	{1,1,1,1,1,1,1,1,1,1,1} };

	// textura modelu
	GLuint texture;
	// zmienne odpowiadajace za ruch modelu
	glm::mat4 position;
	bool go_left, go_right, go_up, go_down;
	std::string direction;
	// wydarzenie zmieniajace kierunek

	int movingSpeed = 20;
	int arrayPositionX = 9;
	int arrayPositionZ = 9;
	int realPositionX = arrayPositionX * movingSpeed;
	int realPositionZ = arrayPositionZ * movingSpeed;


	// wektory modelu
	std::vector<glm::vec4> vertexes;
	std::vector<glm::vec4> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;

	// za³adowanie tekstury
	void readTexture(const char* filename);

	// za³adowanie modelu
	void loadModel(std::string plik);

	// rysowanie modelu
	void drawModel();

	// poruszanie siê
	void move();
};

#endif