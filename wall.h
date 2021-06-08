#ifndef wall_h
#define wall_h

#include "includes.h"

class WallSegment {
public:
	GLuint texture;
	int wallSegmentCount = 36;

	void readTexture(const char* filename);

	void drawSegment(glm::mat4 M);
};

#endif
