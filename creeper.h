#ifndef creeper_h
#define creeper_h

#include "includes.h"

class Creeper {
public:
	// textura modelu
	GLuint texture;	
	// zmienne odpowiadajace za ruch modelu
	std::string direction;
	glm::mat4 position;
	// wydarzenie zmieniajace kierunek
	bool go_left, go_right, go_up, go_down;		

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