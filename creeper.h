#ifndef creeper_h
#define creeper_h

#include "includes.h"

class Creeper {
public:
	GLuint texture;

	std::string direction;
	glm::mat4 position;
	
	float position_x = 1;
	float position_z = 1;
	float movingSpeed = 1;

	std::vector<glm::vec4> vertexes;
	std::vector<glm::vec4> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;


	void readTexture(const char* filename);

	void loadModel(std::string plik);
};

#endif