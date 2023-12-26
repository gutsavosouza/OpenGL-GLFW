#pragma once
#include "Luz.h"
class LuzPontual : public Luz
{

public:
	LuzPontual();

	LuzPontual(GLfloat vermelho, GLfloat verde, GLfloat azul,
				GLfloat intensidadeA, GLfloat intensidadeD,
				GLfloat xPos, GLfloat yPos, GLfloat zPos, 
				GLfloat con, GLfloat lin, GLfloat exp);

	void usarLuzPontual(GLuint intensidadeALoc, GLuint corLoc,
						GLuint intensidadeDLoc, GLuint posLoc,
						GLuint constLoc, GLuint linLoc, GLuint expLoc);

	~LuzPontual();

protected:
	glm::vec3 posicao;

	GLfloat constante, linear, expoente;
};