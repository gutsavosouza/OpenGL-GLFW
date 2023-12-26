#include "Material.h"

Material::Material() {
	intensidadeEspecular = 0;
	brilho = 0;
}

Material::Material(GLfloat intensidadeE, GLfloat brilhoE) {
	intensidadeEspecular = intensidadeE;;
	brilho = brilhoE;
}

void Material::usarMaterial(GLuint intensidadeEspecLoc, GLuint brilhoLoc) {
	glUniform1f(intensidadeEspecLoc, intensidadeEspecular);
	glUniform1f(brilhoLoc, brilho);
}

Material::~Material() {

}