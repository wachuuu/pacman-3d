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
	
	float position_x = 1;
	float position_z = 1;
	float movingSpeed = 1;

	// wektory modelu
	std::vector<glm::vec4> vertexes;
	std::vector<glm::vec4> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;

	// za³adowanie tekstury
	void readTexture(const char* filename);

	// za³adowanie modelu
	void loadModel(std::string plik);

	void drawModel();

	// poruszanie sie
	//void move();
};

#endif