#include "ghost.h"

void Ghost::readTexture(const char* filename) {
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamiêci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamiêci karty graficznej
	glGenTextures(1, &texture); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, texture); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Ghost::loadModel(std::string plik) {
	using namespace std;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(plik,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
	cout << importer.GetErrorString() << endl;

	aiMesh* mesh = scene->mMeshes[0];
	for (int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D vertex = mesh->mVertices[i];

		vertexes.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

		aiVector3D normal = mesh->mNormals[i];
		normals.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

		aiVector3D texCoord = mesh->mTextureCoords[0][i];
		texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace& face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
}

void Ghost::drawModel() {

	glUniformMatrix4fv(myShader->u("M"), 1, false, glm::value_ptr(position));

	glEnableVertexAttribArray(myShader->a("vertex"));
	glVertexAttribPointer(myShader->a("vertex"), 4, GL_FLOAT, false, 0, vertexes.data());

	glEnableVertexAttribArray(myShader->a("normal"));
	glVertexAttribPointer(myShader->a("normal"), 4, GL_FLOAT, false, 0, normals.data());

	glEnableVertexAttribArray(myShader->a("texCoord"));
	glVertexAttribPointer(myShader->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture); glUniform1i(myShader->u("tex"), 0);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(myShader->a("vertex"));
	glDisableVertexAttribArray(myShader->a("normal"));
	glDisableVertexAttribArray(myShader->a("texCoord"));
}

void Ghost::move() {
	position = glm::rotate(position, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	position = glm::scale(position, glm::vec3(4.0f, 4.0f, 4.0f));
	bool debug = false;

	if (debug) std::cout << "x: " << realPositionX << " z: " << realPositionZ << std::endl;
	if (realPositionX % movingSpeed == 0)
		arrayPositionX = realPositionX / movingSpeed;
	if (realPositionZ % movingSpeed == 0)
		arrayPositionZ = realPositionZ / movingSpeed;

		if (realPositionX % movingSpeed == 0 && realPositionZ % movingSpeed == 0) {
			int los = (rand() % 4) + 1;
			if (los == 1 && map[arrayPositionX + 1][arrayPositionZ] != 1) {
				direction = "left";
			}
			if (los == 2 && map[arrayPositionX - 1][arrayPositionZ] != 1) {
				direction = "right";
			}
			if (los == 3 && map[arrayPositionX][arrayPositionZ + 1] != 1) {
				direction = "up";
			}
			if (los == 4 && map[arrayPositionX][arrayPositionZ - 1] != 1) {
				direction = "down";
			}
		}
		if (debug ) std::cout << "-------------------------------\n" + direction << std::endl;

	// w³aœciwy ruch modelu
	if (direction == "up")
	{

		if (map[arrayPositionX][arrayPositionZ + 1] != 1)
		{
			realPositionZ += 1;
			position = glm::translate(position, glm::vec3(0.0f, 0.0f, 1.0f / (float)movingSpeed));
		}
	}
	if (direction == "down")
	{
		if (map[arrayPositionX][arrayPositionZ - 1] != 1)
		{
			realPositionZ -= 1;
			position = glm::translate(position, glm::vec3(0.0f, 0.0f, -1.0f / (float)movingSpeed));
		}
	}
	if (direction == "left")
	{
		if (map[arrayPositionX + 1][arrayPositionZ] != 1)
		{
			realPositionX += 1;
			position = glm::translate(position, glm::vec3(1.0f / (float)movingSpeed, 0.0f, 0.0f));
		}
	}
	if (direction == "right")
	{
		if (map[arrayPositionX - 1][arrayPositionZ] != 1)
		{
			realPositionX -= 1;
			position = glm::translate(position, glm::vec3(-1.0f / (float)movingSpeed, 0.0f, 0.0f));
		}
	}

	// zaznaczenie odwiedzonego pola (zebranie monety)
	/*if (realPositionX % movingSpeed == 0 && realPositionZ % movingSpeed == 0) {
		if (map[realPositionX / movingSpeed][realPositionZ / movingSpeed] == 0) {
			map[realPositionX / movingSpeed][realPositionZ / movingSpeed] = 2; // zdobycie monety
			//PlaySound(TEXT("./sounds/coin_sound-_1_.wav"), NULL, SND_SYNC);
		}
	}*/
	position = glm::scale(position, glm::vec3(0.25f, 0.25f, 0.25f));
	position = glm::rotate(position, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
}