#include "Textura.h"

Textura::Textura() {
	texturaId = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	arquivoLoc = "";
}

Textura::Textura(const char* arqvLoc) {
	texturaId = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	arquivoLoc = arqvLoc;
}

bool Textura::carregarTextura() {
	unsigned char* texturaData = stbi_load(arquivoLoc, &width, &height, &bitDepth, 0);
	if (!texturaData) {
		printf("Erro ao carregar a textura: %s", arquivoLoc);
		return false;
	}

	glGenTextures(1, &texturaId);
	glBindTexture(GL_TEXTURE_2D, texturaId);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texturaData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texturaData);

	return true;
}

bool Textura::carregarTexturaAlpha() {
	unsigned char* texturaData = stbi_load(arquivoLoc, &width, &height, &bitDepth, 0);
	if (!texturaData) {
		printf("Erro ao carregar a textura: %s", arquivoLoc);
		return false;
	}

	glGenTextures(1, &texturaId);
	glBindTexture(GL_TEXTURE_2D, texturaId);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturaData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texturaData);

	return true;
}

void Textura::usarTextura() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaId);
}

void Textura::limparTextura() {
	glDeleteTextures(1, &texturaId);
	texturaId = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	arquivoLoc = "";	
}

Textura::~Textura() {
	limparTextura();
}