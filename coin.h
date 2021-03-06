#ifndef coin_h
#define coin_h

#include "includes.h"

class Coin {
public:
	// textura modelu
	GLuint texture;

	// wektory modelu
	std::vector<glm::vec4> vertexes;
	std::vector<glm::vec4> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;
	std::vector<std::vector<glm::mat4>> position;

	// załadowanie tekstury
	void readTexture(const char* filename);

	// załadowanie modelu
	void loadModel(std::string plik);

	// rysowanie modelu
	void drawModel(float xCoords, float yCoords);

	// rozłożenie monet na mapie
	void placeCoins(int map[11][11]);

	void loadMap(int map[11][11]);
};

#endif
