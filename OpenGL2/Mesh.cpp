#include "Mesh.h"

Mesh::Mesh() {
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCont = 0;

}

// funcao que cria uma Mesh
// baseando-se em pontos definidos, x, y e z a funcao cria o VAO e o tambem o VBO e os binda, apos execucao da funcao o VAO e o VBO
// sao desbindados
// aqui tambem eh passado os vertices do triangulo para o VBO
void Mesh::criarMesh(GLfloat* vertices, unsigned int* indices, unsigned int numDeVertices, unsigned int numDeIndices) {
	indexCont = numDeIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numDeIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * numDeVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::renderizarMesh() {
	// determianndo qual VAO estaremos usando no loop tambem
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// desenhando um triangulo que esta presente no VAO
	glDrawElements(GL_TRIANGLES, indexCont, GL_UNSIGNED_INT, 0);

	// desbindando o VAO para poder utilizar outro em outra iteracao do loop
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::limparMesh() {
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if(VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCont = 0;
}

Mesh::~Mesh() {
	limparMesh();
}