#pragma once
#include "LuzPontual.h"
class LuzHolofote : public LuzPontual
{
public:
	LuzHolofote();

	LuzHolofote(GLfloat vermelho, GLfloat verde, GLfloat azul,
		GLfloat intensidadeA, GLfloat intensidadeD,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat bord);

	void usarLuzHolofote(GLuint intensidadeALoc, GLuint corLoc,
		GLuint intensidadeDLoc, GLuint posLoc, GLuint direcaoLoc,
		GLuint constLoc, GLuint linLoc, GLuint expLoc,
		GLuint bordaLoc);

	void definirLanterna(glm::vec3 pos, glm::vec3 dir);

	~LuzHolofote();

private:
	glm::vec3 direcao;
	GLfloat borda, proBorda;
};