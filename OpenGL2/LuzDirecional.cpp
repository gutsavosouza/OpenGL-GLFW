#include "LuzDirecional.h"

LuzDirecional::LuzDirecional() : Luz() {
	direcao = glm::vec3(0.0f, -1.0f, 0.0f);
}

LuzDirecional::LuzDirecional(GLfloat vermelho, GLfloat verde, GLfloat azul, GLfloat intensidadeA, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat intensidadeD) : Luz(vermelho, verde, azul, intensidadeA, intensidadeD) {
	direcao = glm::vec3(xDir, yDir, zDir);
}

void LuzDirecional::usarLuzDirecional(GLuint intensidadeALoc, GLuint corLoc, GLuint intensidadeDLoc, GLuint dirLoc) {
	glUniform3f(corLoc, cor.x, cor.y, cor.z);
	glUniform1f(intensidadeALoc, intensidadeAmbiente);
	glUniform3f(dirLoc, direcao.x, direcao.y, direcao.z);
	glUniform1f(intensidadeDLoc, intensidadeDifusao);
}

LuzDirecional::~LuzDirecional() {

}