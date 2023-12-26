#include "LuzPontual.h"

LuzPontual::LuzPontual() : Luz() {
	posicao = glm::vec3(0.0f, 0.0f, 0.0f);
	constante = 1.0f;
	linear = 0.0f;
	expoente = 0.0f;
}

LuzPontual::LuzPontual(GLfloat vermelho, GLfloat verde, GLfloat azul, 
						GLfloat intensidadeA, GLfloat intensidadeD, 
						GLfloat xPos, GLfloat yPos, GLfloat zPos, 
						GLfloat con, GLfloat lin, GLfloat exp)  : Luz(vermelho, verde, azul, intensidadeA, intensidadeD) {
	posicao = glm::vec3(xPos, yPos, zPos);
	constante = con;
	linear = lin;
	expoente = exp;
}

void LuzPontual::usarLuzPontual(GLuint intensidadeALoc, GLuint corLoc,
								GLuint intensidadeDLoc, GLuint posLoc,
								GLuint constLoc, GLuint linLoc, GLuint expLoc) {
	glUniform3f(corLoc, cor.x, cor.y, cor.z);
	glUniform1f(intensidadeALoc, intensidadeAmbiente);
	glUniform1f(intensidadeDLoc, intensidadeDifusao);

	glUniform3f(posLoc, posicao.x, posicao.y, posicao.z);
	glUniform1f(constLoc, constante);
	glUniform1f(linLoc, linear);
	glUniform1f(expLoc, expoente);
}

LuzPontual::~LuzPontual() {

}