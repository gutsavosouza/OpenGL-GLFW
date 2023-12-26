#pragma once

#include "Luz.h"

class LuzDirecional : public Luz
{
public:
	LuzDirecional();
	LuzDirecional(GLfloat vermelho, GLfloat verde, GLfloat azul, GLfloat intensidadeA, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat intensidadeD);

	void usarLuzDirecional(GLuint intensidadeALoc, GLuint corLoc, GLuint intensidadeDLoc, GLuint dirLoc);

	~LuzDirecional();

private:

	glm::vec3 direcao;
};