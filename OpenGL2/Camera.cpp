#include "Camera.h"

Camera::Camera() {
}
Camera::Camera(glm::vec3 posInical, glm::vec3 cimaInicial, GLfloat yawInicial, GLfloat pitchInicial, GLfloat velocidadeMovInicial, GLfloat velocidadeMouseInicial) {
	pos = posInical;
	mundoCima = cimaInicial;
	yaw = yawInicial;
	pitch = pitchInicial;
	frente = glm::vec3(0.0f, 0.0f, -1.0f);
	velocidadeMov = velocidadeMovInicial;
	velocidadeMouse = velocidadeMouseInicial;

	update();
}

void Camera::controleKey(bool* keys, GLfloat deltaTime) {
	GLfloat velocidade = velocidadeMov * deltaTime;

	if (keys[GLFW_KEY_W]) {
		pos += frente * velocidade;
	}
	if (keys[GLFW_KEY_S]) {
		pos -= frente * velocidade;
	}
	if (keys[GLFW_KEY_A]) {
		pos -= direita * velocidade;
	}
	if (keys[GLFW_KEY_D]) {
		pos += direita * velocidade;
	}
	if (keys[GLFW_KEY_SPACE]) {
		pos += mundoCima * velocidade;
	}
	if (keys[GLFW_KEY_LEFT_CONTROL]) {
		pos -= mundoCima * velocidade;
	}
}

void Camera::controleMouse(GLfloat mudancaX, GLfloat mudancaY) {
	mudancaX *= velocidadeMouse;
	mudancaY *= velocidadeMouse;

	yaw += mudancaX;
	pitch += mudancaY;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calcularMatrizVisao() {
	return glm::lookAt(pos, pos + frente, cima);
}

void Camera::update() {
	frente.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frente.y = sin(glm::radians(pitch));
	frente.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	frente = glm::normalize(frente);

	direita = glm::normalize(glm::cross(frente, mundoCima));
	cima = glm::normalize(glm::cross(direita, frente));
}

Camera::~Camera() {

}
