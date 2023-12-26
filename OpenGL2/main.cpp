#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>

#include "Janela.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Textura.h"
#include "LuzDirecional.h"
#include "Material.h"
#include "ValoresComuns.h"
#include "LuzPontual.h"
#include "LuzHolofote.h"
#include "Model.h"

Janela mainWindow;
std::vector<Mesh*> listaMesh;
std::vector<Shader> listaShader;
Camera camera;

Textura gramaTex;
Textura terraTex;
Textura blocoTex;
Textura metalTex;

Material metalMat;
Material opacoMat;

Model model1;

LuzDirecional luzDir;
LuzPontual luzPont[MAX_LUZ_PONTUAL_CONT];
LuzHolofote luzHol[MAX_LUZ_HOLOFOTE_CONT];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// campos referentes a movimentao do triangulo desenhado na tela
// direcao quando for true significa que o objeto esta indo para a direita e false quando for pra esquerda
// trianguloOffSet eh a posicao alterada do objeto
// trianguloMaxOffSet eh a posicao maxima altera, quando o objeto chega e essa posicao ele passa a mover para o outro lado
// trianguloIncremento eh a modificacao na posicao a cada iterecao do loop, quanto maior o valor mais rapido o objeto move
// angAtual se refere ao angulo atual do objeto, usado para rotacionar o objeto nas iteracoes
bool direcao = true;
float trianguloOffSet = 0;
float trianguloMaxOffSet = 0.8f;
float trianguloIncremento = 0.00007f;
float angAtual = 0.0f;
bool tamDirecao = true;
float tamAtual = 0.4f;
float tamMax = 0.5f;
float tamMin = 0.2f;
float tamIncremento = 0.00007f;
// para converter graus em radianos para utilizar na rotação de objetos
const float toRadiano = 3.14159265f / 180.0f;

// codigo dos shaders
static const char* vertexShader = "Shaders/shader.vert";

static const char* fragmentShader = "Shaders/shader.frag";

void calcularNormais(unsigned int* indices, unsigned int indicesCont, GLfloat* vertices, unsigned int verticesCont, unsigned int tamV, unsigned int normalOffSet) {
	for (size_t i = 0; i < indicesCont ; i += 3) {
		unsigned int in0 = indices[i] * tamV;
		unsigned int in1 = indices[i + 1] * tamV;
		unsigned int in2 = indices[i + 2] * tamV;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffSet;
		in1 += normalOffSet;
		in2 += normalOffSet;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}
	for (size_t i = 0; i < (verticesCont / tamV); i++) {
		unsigned int nOffSet = i * tamV + normalOffSet;
		glm::vec3 vec(vertices[nOffSet], vertices[nOffSet + 1], vertices[nOffSet + 2]);
		vec = glm::normalize(vec);

		vertices[nOffSet] = vec.x;
		vertices[nOffSet + 1] = vec.y;
		vertices[nOffSet + 2] = vec.z;
	}
}

// funcao que cria um objeto
// baseando-se em pontos definidos, x, y e z a funcao cria o VAO e o tambem o VBO e os binda, apos execucao da funcao o VAO e o VBO
// sao desbindados
// aqui tambem eh passado os vertices do triangulo para o VBO
void criarObj() {
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	unsigned int chaoIndices[] = {
		0, 2, 1,
		1, 2, 3,
	};

	GLfloat vertices[] = { 
	//	coordenadas da posicao   coordenadas do mapa uv		normais
		-1.0f, -1.0f, -0.7f,		0.0f, 0.0f,				0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,			0.5f, 0.0f,				0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.7f,			1.0f, 0.0f,				0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,			0.5f, 1.0f,				0.0f, 0.0f, 0.0f,
	};

	GLfloat chaoVertices[] = {
		-70.0f, 0.0f, -70.0f,		0.0f, 0.0f,				0.0f, -1.0f, 0.0f,
		70.0f, 0.0f, -70.0f,		70.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		-70.0f, 0.0f, 70.0f,		0.0f, 70.0f,			0.0f, -1.0f, 0.0f,
		70.0f, 0.0f, 70.0f,			70.0f, 70.0f,			0.0f, -1.0f, 0.0f,
	};

	calcularNormais(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->criarMesh(vertices, indices, 32, 12);
	listaMesh.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->criarMesh(vertices, indices, 32, 12);
	listaMesh.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->criarMesh(vertices, indices, 32, 12);
	listaMesh.push_back(obj3);

	Mesh* chao = new Mesh();
	chao->criarMesh(chaoVertices, chaoIndices, 32, 6);
	listaMesh.push_back(chao);
}

void criarShaders() {
	Shader* shader1 = new Shader();
	shader1->criarDeArquivo(vertexShader, fragmentShader);
	listaShader.push_back(*shader1);
}

int main() {

	mainWindow = Janela(1600.0f, 900.0f);
	mainWindow.init();

	// chamandos as funcoes para criar o triangulo e compilar os shaders e o shader program
	criarObj();
	criarShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, .2f);

	gramaTex = Textura("Texturas/grama3.png");
	gramaTex.carregarTexturaAlpha();
	terraTex = Textura("Texturas/terra3.png");
	terraTex.carregarTexturaAlpha();
	blocoTex = Textura("Texturas/bloco3.png");
	blocoTex.carregarTexturaAlpha();
	metalTex = Textura("Texturas/metal1.png");
	metalTex.carregarTexturaAlpha();

	metalMat = Material(1.0f, 32);
	opacoMat = Material(0.3f, 8);

	model1 = Model();
	model1.carregarModel("Model/home_flower_OBJ.obj");

	luzDir = LuzDirecional(0.5f, 0.5f, 1.0f,
							0.7f,
							0.0f, -1.0f, 0.0f,
							0.2f);

	unsigned int contLuzPontual = 0, contLuzHolofote = 0;

	luzPont[0] = LuzPontual(0.3f, 0.3f, 1.0f,
							1.0f, 1.0f,
							-3.0f, 0.0f, -2.0f,
							0.1f, 0.0f, 0.0f);
	// contLuzPontual++;

	luzHol[0] = LuzHolofote(1.0f, 1.0f, 0.4f,	// R G B
							0.5f, 0.7f,			// IntensidadeA e IntensidadeD
							0.0f, 0.0f, 0.0f,	// posicao(x, y, z)
							0.0f, -1.0f, 0.0f,	// direcao (x, y, z)
							0.3f, 0.2f, 0.2f,	// constante, linear, expoente >> calculo do fading da luz
							10.0f);				// angulo de abertura para definir a borda da luz
	contLuzHolofote++;

	luzHol[1] = LuzHolofote(0.0f, 0.0f, 1.0f,
							0.5f, 0.9f,
							0.0f, 5.0f, -2.5f,
							0.0f, -1.0f, 0.0f,
							0.7f, 0.2f, 0.0f,
							45.0f);
	contLuzHolofote++;

	GLuint uniformProj = 0, uniformModel = 0, uniformVisao = 0, uniformPosOlho = 0,
		uniformIntensidadeEspecular = 0, uniformBrilho = 0;
	glm::mat4 proj = glm::perspective(70.0f, (GLfloat) mainWindow.getBufferWidht() / (GLfloat) mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// loop principal para manter a janela aberta
	while (!mainWindow.getShouldClose()) {
		GLfloat tempoAtual = glfwGetTime();
		deltaTime = tempoAtual - lastTime;
		lastTime = tempoAtual;
		
		// recebendo as acoes do usuario
		glfwPollEvents();

		camera.controleKey(mainWindow.getKeys(), deltaTime);
		camera.controleMouse(mainWindow.getMudancaX(), mainWindow.getMudancaY());

		if (direcao) {
			trianguloOffSet += trianguloIncremento;
		}
		else {
			trianguloOffSet -= trianguloIncremento;
		}

		if (abs(trianguloOffSet) >= trianguloMaxOffSet) {
			direcao = !direcao;
		}

		angAtual += 0.03f;
		if (angAtual >= 360) {
			angAtual -= 360;
		}

		if (tamDirecao) {
			tamAtual += tamIncremento;
		}
		else {
			tamAtual -= tamIncremento;
		}
		if (tamAtual >= tamMax || tamAtual <= tamMin) {
			tamDirecao = !tamDirecao;
		}

		// limpando uma janela aplicando uma cor em RBG nela toda
		glClearColor(1.0f, 0.4f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// determinando qual shader program estaremos usando nesse loop
		listaShader[0].usarShader();
		uniformModel = listaShader[0].getModelLocal();
		uniformProj = listaShader[0].getProjLocal();
		uniformVisao = listaShader[0].getVisaoLoc();
		uniformPosOlho = listaShader[0].getPosOlhoLoc();
		uniformBrilho = listaShader[0].getBrilhoLoc();
		uniformIntensidadeEspecular = listaShader[0].getIntensidadeEspecularLoc();

		luzHol[0].definirLanterna(camera.getPosicao(), camera.getDirecao());

		listaShader[0].definirLuzDirecional(&luzDir);
		listaShader[0].definirLuzPontual(luzPont, contLuzPontual);
		listaShader[0].definirLuzHolofote(luzHol, contLuzHolofote);

		glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(uniformVisao, 1, GL_FALSE, glm::value_ptr(camera.calcularMatrizVisao()));
		glUniform3f(uniformPosOlho, camera.getPosicao().x, camera.getPosicao().y, camera.getPosicao().z);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gramaTex.usarTextura();
		opacoMat.usarMaterial(uniformIntensidadeEspecular, uniformBrilho);
		listaMesh[3]->renderizarMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, -0.4f, -2.5f));
		model = glm::rotate(model, angAtual * toRadiano, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		opacoMat.usarMaterial(uniformIntensidadeEspecular, uniformBrilho);
		listaMesh[0]->renderizarMesh();

		/*model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -2.5f));
		model = glm::rotate(model, angAtual * toRadiano, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		terraTex.usarTextura();
		listaMesh[1]->renderizarMesh();*/

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, -0.4f, -2.5f));
		model = glm::rotate(model, angAtual * toRadiano, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		metalTex.usarTextura();
		metalMat.usarMaterial(uniformIntensidadeEspecular, uniformBrilho);
		listaMesh[2]->renderizarMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -7.0f));
		model = glm::rotate(model, 0 * toRadiano, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		opacoMat.usarMaterial(uniformIntensidadeEspecular, uniformBrilho);
		model1.renderizarModel();

		// debindando o shader program a ser utilizado pelo mesmo motivo acima
		glUseProgram(0);

		// trocando os buffers para atualizar a tela
		mainWindow.swapBuffers();
	}

	return 0;
}