#include "creeper.h"

void Creeper::readTexture(const char* filename) {
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

void Creeper::loadModel(std::string plik) {
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

void Creeper::drawModel() {

	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(position));

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

/*void Creeper::move() {
	position = glm::scale(position, glm::vec3(4.0f, 4.0f, 4.0f));
	int licznik = 0;

	if (go_right)
		licznik++;
	if (go_left)
		licznik++;
	if (go_up)
		licznik++;
	if (go_down)
		licznik++;

	if (licznik == 1) {
		if (floorf(position_x) == position_x) //sprawdzenie czy float ma wartoœæ ca³kowit¹
		{
			if (go_left && map[int(position_x) + 1][int(position_z)] != 1)
			{
				direction = "left";
			}
			if (go_right && map[int(position_x - 1)][int(position_z)] != 1)
			{
				direction = "right";
			}
		}
		if (floorf(position_z) == position_z) //sprawdzenie czy float ma wartoœæ ca³kowit¹
		{
			if (go_up && map[int(position_x)][int(position_z) + 1] != 1)
			{
				direction = "up";
			}
			if (go_down && map[int(position_x)][int(position_z) - 1] != 1)
			{
				direction = "down";
			}
		}
	}

	if (direction == "up")
	{
		if (map[int(position_x)][int(position_z) + 1] != 1)
		{
			position_z += movingSpeed;
			position = glm::translate(position, glm::vec3(0, 0, movingSpeed));
			std::cout << position_x << " " << position_z << std::endl;
		}
	}
	if (direction == "down")
	{
		if (map[int(position_x)][int(position_z) - 1] != 1)
		{
			position_z -= movingSpeed;
			position = glm::translate(position, glm::vec3(0, 0, -movingSpeed));
		}
	}
	if (direction == "left")
	{
		if (map[int(position_x) + 1][int(position_z)] != 1)
		{
			position_x += movingSpeed;
			position = glm::translate(position, glm::vec3(movingSpeed, 0, 0));
		}
	}
	if (direction == "right")
	{
		if (map[int(position_x) - 1][int(position_z)] != 1)
		{
			position_x -= movingSpeed;
			position = glm::translate(position, glm::vec3(-movingSpeed, 0, 0));
		}
	}
	position = glm::scale(position, glm::vec3(0.25f, 0.25f, 0.25f));
}*/
