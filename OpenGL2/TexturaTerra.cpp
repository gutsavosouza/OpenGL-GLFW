#include "TexturaTerra.h"

TexturaTerra::TexturaTerra() {
	Textura::Textura("Texturas/terra3.png");
	Textura::carregarTextura();
}

TexturaTerra::~TexturaTerra() {
	Textura::limparTextura();
}