#include "coin.h"

void Coin::readTexture(const char* filename) {
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

void Coin::loadModel(std::string plik) {
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

void Coin::drawModel(float xCoords, float yCoords) {
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(position[xCoords][yCoords]));
	//position[xCoords][yCoords] = glm::rotate(glm::translate(position[xCoords][yCoords], glm::vec3(-0.65f, 0.0f, 0.2f)), PI / 30, glm::vec3(0.0f, 1.0f, 0.0f));
	position[xCoords][yCoords] = glm::rotate(glm::translate(position[xCoords][yCoords], glm::vec3(-0.4f, 0.0f, 0.1f)), PI / 50, glm::vec3(0.0f, 1.0f, 0.0f));
	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, vertexes.data());

	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, normals.data());

	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture); glUniform1i(spLambertTextured->u("tex"), 0);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
}

void Coin::placeCoins(int map[11][11]) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == 0) {
				drawModel(i, j);
			}
		}
	}
}

void Coin::loadMap(int map[11][11]) {
	std::vector<glm::mat4> temp;
	for (int i = 0; i < 11; i++) {
		temp.push_back(glm::mat4(1.0f));
	}
	for (int i = 0; i < 11; i++) {
		position.push_back(temp);
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == 0) {
				position[i][j] = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j - 0.25f));
				position[i][j] = glm::scale(position[i][j], glm::vec3(0.05f, 0.05f, 0.05f));
			}
		}
	}
}