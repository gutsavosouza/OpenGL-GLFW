#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 posInical, glm::vec3 cimaInicial, GLfloat yawInicial, GLfloat pitchInicial, GLfloat velocidadeMovInicial, GLfloat velocidadeMouseInicial);

	void controleKey(bool* keys, GLfloat deltaTime);

	void controleMouse(GLfloat mudancaX, GLfloat mudancaY);

	glm::vec3 getPosicao() { return pos;  }
	glm::vec3 getDirecao() { return glm::normalize(frente); }

	glm::mat4 calcularMatrizVisao();

	~Camera();

private:
	glm::vec3 pos, frente, cima, direita, mundoCima;

	GLfloat yaw, pitch, velocidadeMov, velocidadeMouse;

	void update();
};