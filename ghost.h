#ifndef ghost_h
#define ghost_h

#include "includes.h"

class Ghost {
public:
	// textura modelu
	GLuint texture;
	// zmienne odpowiadajace za ruch modelu
	glm::mat4 position;
	// wydarzenie zmieniajace kierunek

	int movingSpeed = 20;
	int arrayPositionX = 1;
	int arrayPositionZ = 1;
	int realPositionX = movingSpeed;
	int realPositionZ = movingSpeed;


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
};

#endif