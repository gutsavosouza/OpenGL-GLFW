#include "TexturaFerro.h"

TexturaFerro::TexturaFerro() {
	Textura::Textura("Texturas/metal1.png");
	Textura::carregarTextura();
}

TexturaFerro::~TexturaFerro() {
	Textura::limparTextura();
}