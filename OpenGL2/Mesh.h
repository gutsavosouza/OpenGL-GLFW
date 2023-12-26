#pragma once

#include <GL/glew.h>

class Mesh {
public:
	Mesh();

	void criarMesh(GLfloat *vertices, unsigned int *indices, unsigned int numDeVertices, unsigned int numDeIndices);
	void renderizarMesh();
	void limparMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCont;
};

