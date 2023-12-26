#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Textura
{
public:
	Textura();
	Textura(const char* arqvLoc);

	bool carregarTextura();
	bool carregarTexturaAlpha();


	void usarTextura();
	void limparTextura();



	~Textura();

private:
	GLuint texturaId;
	int width, height, bitDepth;

	const char* arquivoLoc;
};

