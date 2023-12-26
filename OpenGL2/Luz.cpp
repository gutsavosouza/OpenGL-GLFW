#include "Luz.h"
Luz::Luz() {
	cor = glm::vec3(1.0f, 1.0f, 1.0f);
	intensidadeAmbiente = 1.0f; 
	intensidadeDifusao = 0.0f;
}

Luz::Luz(GLfloat vermelho, GLfloat verde, GLfloat azul, GLfloat intensidadeA, GLfloat intensidadeD){
	cor = glm::vec3(vermelho, verde, azul);
	intensidadeAmbiente = intensidadeA;
	intensidadeDifusao = intensidadeD;
}

Luz::~Luz() {

}