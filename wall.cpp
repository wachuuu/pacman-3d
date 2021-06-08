#include "wall.h"

float wallSegmentVertices[] = {
	//�ciana 1
	1.0f,-1.0f,-1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,1.0f,

	1.0f,-1.0f,-1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,

	//�ciana 2
	-1.0f,-1.0f, 1.0f,1.0f,
	1.0f, 1.0f, 1.0f,1.0f,
	1.0f,-1.0f, 1.0f,1.0f,

	-1.0f,-1.0f, 1.0f,1.0f,
	-1.0f, 1.0f, 1.0f,1.0f,
	1.0f, 1.0f, 1.0f,1.0f,

	//�ciana 3
	-1.0f,-1.0f,-1.0f,1.0f,
	1.0f,-1.0f, 1.0f,1.0f,
	1.0f,-1.0f,-1.0f,1.0f,

	-1.0f,-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f, 1.0f,1.0f,
	1.0f,-1.0f, 1.0f,1.0f,

	//�ciana 4
	-1.0f, 1.0f, 1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,
	1.0f, 1.0f, 1.0f,1.0f,

	-1.0f, 1.0f, 1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,

	//�ciana 5
	-1.0f,-1.0f,-1.0f,1.0f,
	-1.0f, 1.0f, 1.0f,1.0f,
	-1.0f,-1.0f, 1.0f,1.0f,

	-1.0f,-1.0f,-1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,
	-1.0f, 1.0f, 1.0f,1.0f,

	//�ciana 6
	1.0f,-1.0f, 1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,1.0f,

	1.0f,-1.0f, 1.0f,1.0f,
	1.0f, 1.0f, 1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,
};

float wallSegmentNormals[] = {
	//sciana 1
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,

	//sciana 2
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,

	//sciana 3
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,

	//sciana 4
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,

	//sciana 5
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,

	//sciana 6
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
};

float wallSegmentTexCoords[] = {
	//sciana 1
	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	//sciana 2
	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	//sciana 3
	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	//sciana 4
	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	//sciana 5
	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	//sciana 6
	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

void WallSegment::readTexture(const char* filename) {
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pami�ci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do kt�rych wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pami�ci karty graficznej
	glGenTextures(1, &texture); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, texture); //Uaktywnij uchwyt
	//Wczytaj obrazek do pami�ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void WallSegment::drawSegment(glm::mat4 M) {
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, wallSegmentVertices);
	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, wallSegmentNormals);
	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, wallSegmentTexCoords);

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture); glUniform1i(spLambertTextured->u("tex"), 0);
	glDrawArrays(GL_TRIANGLES, 0, wallSegmentCount);

	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
}
