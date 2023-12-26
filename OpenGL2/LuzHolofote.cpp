#include "LuzHolofote.h"

LuzHolofote::LuzHolofote() : LuzPontual() {
	direcao = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
	borda = 0.0f;
	proBorda = cosf(glm::radians(borda));
}

LuzHolofote::LuzHolofote(GLfloat vermelho, GLfloat verde, GLfloat azul, 
						GLfloat intensidadeA, GLfloat intensidadeD,
						GLfloat xPos, GLfloat yPos, GLfloat zPos, 
						GLfloat xDir, GLfloat yDir, GLfloat zDir, 
						GLfloat con, GLfloat lin, GLfloat exp, 
						GLfloat bord) : LuzPontual(vermelho, verde, azul, intensidadeA, intensidadeD, xPos, yPos, zPos, con, lin, exp) {
	direcao = glm::normalize(glm::vec3(xDir, yDir, zDir));
	borda = bord;
	proBorda = cosf(glm::radians(borda));
}

void LuzHolofote::usarLuzHolofote(GLuint intensidadeALoc, GLuint corLoc,
								GLuint intensidadeDLoc, GLuint posLoc, GLuint direcaoLoc, 
								GLuint constLoc, GLuint linLoc, GLuint expLoc,
								GLuint bordaLoc) {
	glUniform3f(corLoc, cor.x, cor.y, cor.z);
	glUniform1f(intensidadeALoc, intensidadeAmbiente);
	glUniform1f(intensidadeDLoc, intensidadeDifusao);

	glUniform3f(posLoc, posicao.x, posicao.y, posicao.z);
	glUniform1f(constLoc, constante);
	glUniform1f(linLoc, linear);
	glUniform1f(expLoc, expoente);

	glUniform3f(direcaoLoc, direcao.x, direcao.y, direcao.z);
	glUniform1f(bordaLoc, proBorda);
}

void LuzHolofote::definirLanterna(glm::vec3 pos, glm::vec3 dir) {
	posicao = pos;
	direcao = dir;
}

LuzHolofote::~LuzHolofote() {
}
