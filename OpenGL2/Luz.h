#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Luz
{
public:
	Luz();
	Luz(GLfloat vermelho, GLfloat verde, GLfloat azul, GLfloat intensidadeA, GLfloat intensidadeD);
	~Luz();
protected:
	glm::vec3 cor;
	GLfloat intensidadeAmbiente;
	GLfloat intensidadeDifusao;
};