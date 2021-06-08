#ifndef wall_h
#define wall_h

#include "includes.h"


class WallSegment {
public:
	// textura modelu
	GLuint texture;

	// liczba wierzchołków w modelu
	int wallSegmentCount = 36;

	// załadowanie tekstury
	void readTexture(const char* filename);

	// rysowanie modelu
	void drawSegment(glm::mat4 M);
};

#endif
