#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "ValoresComuns.h"

#include "LuzDirecional.h"
#include "LuzPontual.h"
#include "LuzHolofote.h"

class Shader {
public:
	Shader();

	void criarDeString(const char* vertexCode, const char* fragCode);
	void criarDeArquivo(const char* vertexLoc, const char* fragLoc);

	std::string lerArquivo(const char* arquivoLoc);

	void definirLuzDirecional(LuzDirecional *LD);
	void definirLuzPontual(LuzPontual* LP, unsigned int contLuz);
	void definirLuzHolofote(LuzHolofote* LH, unsigned int contLuz);

	void usarShader();
	void limparShader();

	GLuint getProjLocal() { return uniformProj; }
	GLuint getModelLocal() { return uniformModel; }
	GLuint getVisaoLoc() { return uniformVisao; }
	GLuint getIntensidadeAmbienteLoc() { return uniformLuzDirecional.uniformIntensidadeA; }
	GLuint getCorAmbienteLoc() { return uniformLuzDirecional.uniformCor; }
	GLuint getDirecaoLoc() { return uniformLuzDirecional.uniformDirecao; }
	GLuint getIntensidadeDifusaoLoc() { return uniformLuzDirecional.uniformIntensidadeD; }
	GLuint getPosOlhoLoc() { return uniformPosOlho; }
	GLuint getIntensidadeEspecularLoc() { return uniformIntensidadeEspecular; }
	GLuint getBrilhoLoc() { return uniformBrilho; }

	~Shader();

private:
	int contLuzPontual, contLuzHolofote;

	GLuint shaderID, uniformProj, uniformModel, uniformVisao, uniformPosOlho,
		uniformIntensidadeEspecular, uniformBrilho, uniformContLuzPontual, uniformContLuzHolofote;

	struct {
		GLuint uniformCor;
		GLuint uniformIntensidadeA;
		GLuint uniformIntensidadeD;
		GLuint uniformDirecao;
	} uniformLuzDirecional;

	struct {
		GLuint uniformCor;
		GLuint uniformIntensidadeA;
		GLuint uniformIntensidadeD;

		GLuint uniformPosicao;
		GLuint uniformConstante;
		GLuint uniformLinear;
		GLuint uniformExpoente;
	} uniformLuzPontual[MAX_LUZ_PONTUAL_CONT];

	struct {
		GLuint uniformCor;
		GLuint uniformIntensidadeA;
		GLuint uniformIntensidadeD;

		GLuint uniformPosicao;
		GLuint uniformConstante;
		GLuint uniformLinear;
		GLuint uniformExpoente;

		GLuint uniformDirecao;
		GLuint uniformBorda;
	} uniformLuzHolofote[MAX_LUZ_HOLOFOTE_CONT];

	// essa eh a funcao principal para os shaders e o shader program
	// aqui o shader program eh incilizado, depois disso sao criados o vertex shader e o fragment shader
	// ambos sao adicionados ao shader program
	// apos isso o shader program eh linkado e validado, realizando testes para checar o sucesso das operacoes
	void compilarShader(const char* vertexCode, const char* fragCode);

	// essa funcao adiciona ao shader program os shaders passados em parametros
	// sera utilziada na compilação dos shader
	// aqui tambem ocorre a compilção dos shaders determinados em parametros
	void adicionarShader(GLuint program, const char* shaderCode, GLenum shaderTipo);
};

