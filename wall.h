#ifndef wall_h
#define wall_h

#include "includes.h"


class WallSegment {
public:
	// textura modelu
	GLuint texture;

	// liczba wierzcho�k�w w modelu
	int wallSegmentCount = 36;

	// za�adowanie tekstury
	void readTexture(const char* filename);

	// rysowanie modelu
	void drawSegment(glm::mat4 M);

	// rysowanie ca�ej mapy
	void drawMap(int map[11][11]);
};

#endif
