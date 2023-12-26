#include "TexturaGrama.h"

TexturaGrama::TexturaGrama() {
	Textura::Textura("Texturas/grama3.png");
	Textura::carregarTextura();
}

TexturaGrama::~TexturaGrama() {
	Textura::limparTextura();
}