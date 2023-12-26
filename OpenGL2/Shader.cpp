#include "Shader.h"

Shader::Shader() {
	shaderID = 0;
	uniformModel = 0;
	uniformProj = 0;
	contLuzPontual = 0;
	contLuzHolofote = 0;
}

void Shader::criarDeString(const char* vertexCode, const char* fragCode) {
	compilarShader(vertexCode, fragCode);
}

std::string Shader::lerArquivo(const char* arquivoLoc) {
	std::string conteudo;
	std::ifstream arquivo(arquivoLoc, std::ios::in);

	if (!arquivo.is_open()) {
		printf("Erro ao ler o arquivo %s", arquivoLoc);
		return "";
	}

	std::string linha = "";
	while (!arquivo.eof()) {
		std::getline(arquivo, linha);
		conteudo.append(linha + "\n");
	}

	arquivo.close();
	return conteudo;
}

void Shader::criarDeArquivo(const char* vertexLoc, const char* fragLoc) {
	std::string vertexString = lerArquivo(vertexLoc);
	std::string fragString = lerArquivo(fragLoc);

	const char* vertexCode = vertexString.c_str();
	const char* fragCode = fragString.c_str();

	compilarShader(vertexCode, fragCode);
}

void Shader::compilarShader(const char* vertexCode, const char* fragCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Erro ao criar o Shader Program.");
		return;
	}

	adicionarShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	adicionarShader(shaderID, fragCode, GL_FRAGMENT_SHADER);

	GLint resultado = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &resultado);
	if (!resultado) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Erro ao linkar o shader program: \n %s \n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &resultado);
	if (!resultado) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Erro ao validar o shader program: \n %s \n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProj = glGetUniformLocation(shaderID, "proj");
	uniformVisao = glGetUniformLocation(shaderID, "visao");
	uniformLuzDirecional.uniformCor = glGetUniformLocation(shaderID, "LD.base.cor");
	uniformLuzDirecional.uniformIntensidadeA = glGetUniformLocation(shaderID, "LD.base.intensidadeAmbiente");
	uniformLuzDirecional.uniformDirecao = glGetUniformLocation(shaderID, "LD.direcao");
	uniformLuzDirecional.uniformIntensidadeD = glGetUniformLocation(shaderID, "LD.base.intensidadeDifusao");
	uniformPosOlho = glGetUniformLocation(shaderID, "posOlho");
	uniformIntensidadeEspecular = glGetUniformLocation(shaderID, "material.intensidadeEspecular");
	uniformBrilho = glGetUniformLocation(shaderID, "material.brilho");

	uniformContLuzPontual = glGetUniformLocation(shaderID, "contLuzPontual");

	for (size_t i = 0; i < MAX_LUZ_PONTUAL_CONT; i++) {
		char locBuffer[100] = { '\0' };

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].base.cor", i);
		uniformLuzPontual[i].uniformCor = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].base.intensidadeAmbiente", i);
		uniformLuzPontual[i].uniformIntensidadeA = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].base.intensidadeDifusao", i);
		uniformLuzPontual[i].uniformIntensidadeD = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].posicao", i);
		uniformLuzPontual[i].uniformPosicao = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].constante", i);
		uniformLuzPontual[i].uniformConstante = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].linear", i);
		uniformLuzPontual[i].uniformLinear = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LP[%d].expoente", i);
		uniformLuzPontual[i].uniformExpoente = glGetUniformLocation(shaderID, locBuffer);
	}

	uniformContLuzHolofote = glGetUniformLocation(shaderID, "contLuzHolofote");

	for (size_t i = 0; i < MAX_LUZ_HOLOFOTE_CONT; i++) {
		char locBuffer[100] = { '\0' };

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.base.cor", i);
		uniformLuzHolofote[i].uniformCor = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.base.intensidadeAmbiente", i);
		uniformLuzHolofote[i].uniformIntensidadeA = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.base.intensidadeDifusao", i);
		uniformLuzHolofote[i].uniformIntensidadeD = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.posicao", i);
		uniformLuzHolofote[i].uniformPosicao = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.constante", i);
		uniformLuzHolofote[i].uniformConstante = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.linear", i);
		uniformLuzHolofote[i].uniformLinear = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].base.expoente", i);
		uniformLuzHolofote[i].uniformExpoente = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].direcao", i);
		uniformLuzHolofote[i].uniformDirecao = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "LH[%d].borda", i);
		uniformLuzHolofote[i].uniformBorda = glGetUniformLocation(shaderID, locBuffer);
	}
}

void Shader::adicionarShader(GLuint program, const char* shaderCode, GLenum shaderTipo) {
	GLuint shader = glCreateShader(shaderTipo);

	const GLchar* code[1];
	code[0] = shaderCode;

	GLint codeLen[1];
	codeLen[0] = strlen(shaderCode);

	glShaderSource(shader, 1, code, codeLen);

	glCompileShader(shader);
	GLint resultado = 0;
	GLchar eLog[1024] = { 0 };


	glGetShaderiv(shader, GL_COMPILE_STATUS, &resultado);
	if (!resultado) {
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Erro ao compilar o shader %d: \n %s \n", shaderTipo, eLog);
		return;
	}

	glAttachShader(program, shader);
}

void Shader::definirLuzDirecional(LuzDirecional* LD) {
	LD->usarLuzDirecional(uniformLuzDirecional.uniformIntensidadeA, uniformLuzDirecional.uniformCor, 
						uniformLuzDirecional.uniformIntensidadeD, uniformLuzDirecional.uniformDirecao);
}

void Shader::definirLuzPontual(LuzPontual* LP, unsigned int contLuz) {
	if (contLuz > MAX_LUZ_PONTUAL_CONT) {
		contLuz = MAX_LUZ_PONTUAL_CONT;
	}

	glUniform1i(uniformContLuzPontual, contLuz);

	for (size_t i = 0; i < contLuz; i++) {
		LP[i].usarLuzPontual(uniformLuzPontual[i].uniformIntensidadeA, uniformLuzPontual[i].uniformCor,
								uniformLuzPontual[i].uniformIntensidadeD, uniformLuzPontual[i].uniformPosicao, 
								uniformLuzPontual[i].uniformConstante, uniformLuzPontual[i].uniformLinear, uniformLuzPontual[i].uniformExpoente);
	}
}

void Shader::definirLuzHolofote(LuzHolofote* LH, unsigned int contLuz) {
	if (contLuz > MAX_LUZ_HOLOFOTE_CONT) {
		contLuz = MAX_LUZ_HOLOFOTE_CONT;
	}

	glUniform1i(uniformContLuzHolofote, contLuz);

	for (size_t i = 0; i < contLuz; i++) {
		LH[i].usarLuzHolofote(uniformLuzHolofote[i].uniformIntensidadeA, uniformLuzHolofote[i].uniformCor,
			uniformLuzHolofote[i].uniformIntensidadeD, uniformLuzHolofote[i].uniformPosicao, uniformLuzHolofote[i].uniformDirecao,
			uniformLuzHolofote[i].uniformConstante, uniformLuzHolofote[i].uniformLinear, uniformLuzHolofote[i].uniformExpoente,
			uniformLuzHolofote[i].uniformBorda);	
	}
}

void Shader::usarShader() {
	glUseProgram(shaderID);
}

void Shader::limparShader() {
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID;
	}

	uniformProj = 0;
	uniformModel = 0;
}

Shader::~Shader() {
	limparShader();
}
