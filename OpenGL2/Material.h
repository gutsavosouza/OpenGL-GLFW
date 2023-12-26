#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();

	Material(GLfloat intensidadeE, GLfloat brilhoE);

	void usarMaterial(GLuint intensidadeEspecLoc, GLuint brilhoLoc);

	~Material();

private:
	GLfloat intensidadeEspecular, brilho;

};

