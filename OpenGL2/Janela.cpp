#include "Janela.h"

Janela::Janela() {
	widht = 1024;
	height = 768;
	mousePrimeiroMovimento = true;
	mudancaX = 0.0f;
	mudancaY = 0.0f;


	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

Janela::Janela(GLint wWidht, GLint wHeight) {
	widht = wWidht;
	height = wHeight;
	mousePrimeiroMovimento = true;
	mudancaX = 0.0f;
	mudancaY = 0.0f;
	
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = false;
	}
}

int Janela::init() {
	// inciando GLFW
	if (!glfwInit()) {
		printf("Erro ao iniciar o GLFW.");
		glfwTerminate();
		return 1;
	}

	// configurando as propriedas da janela do glfw
	// versao do openGL, que é a 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// perfil core == sem retrocompatibilidade e ativando a compatibilidade coma atualizacoes futuras do openGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// iniciando a janela do GLFW
	mainWindow = glfwCreateWindow(widht, height, "OpenGL", NULL, NULL);
	if (!mainWindow) {	
		printf("A janela do GLFW nao pode ser criada.");
		glfwTerminate();
		return 1;
	}

	// configurando o tamanho do buffer para determinar a janela de exibicao
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// passando o contexto atual para o GLFW, no caso, a janela a ser usada
	glfwMakeContextCurrent(mainWindow);

	// entrada de tecla e mouse
	criarCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ativando funcoes experimentais do openGL
	glewExperimental = GL_TRUE;

	// inicializando o GLEW
	if (glewInit() != GLEW_OK) {
		printf("Erro ao inicilizar o GLEW.");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// configurando o tamanho da janela de exibição
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

GLfloat Janela::getMudancaX() {
	GLfloat mudanca = mudancaX;
	mudancaX = 0.0f;
	return mudanca;
}

GLfloat Janela::getMudancaY() {
	GLfloat mudanca = mudancaY;
	mudancaY = 0.0f;
	return mudanca;
}

void Janela::criarCallbacks() {
	glfwSetKeyCallback(mainWindow, keyHandler);
	glfwSetCursorPosCallback(mainWindow, mouseHandler);
}

void Janela::keyHandler(GLFWwindow* window, int key, int code, int action, int mode) {
	Janela* wind = static_cast<Janela*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			wind->keys[key] = true;
			//printf("Tecla pressionada: %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			wind->keys[key] = false;
			//printf("Tecla solta: %d\n", key);
		}
	}
}

void Janela::mouseHandler(GLFWwindow* window, double xPos, double yPos) {
	Janela* wind = static_cast<Janela*>(glfwGetWindowUserPointer(window));

	if (wind->mousePrimeiroMovimento) {
		wind->ultimoX = xPos;
		wind->ultimoY = yPos;
		wind->mousePrimeiroMovimento = false;
	}

	wind->mudancaX = xPos - wind->ultimoX;
	wind->mudancaY = wind->ultimoY - yPos;

	wind->ultimoX = xPos;
	wind->ultimoY = yPos;

	//printf("X: %.3f, Y: %.3f \n", wind->mudancaX, wind->mudancaY);
}

Janela::~Janela() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
