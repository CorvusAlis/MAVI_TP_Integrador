#include "Enemigo.h"

using namespace std;

Enemigo::Enemigo(const string rutaTextura, float escala, Vector2 posicion) :
	escala(escala), posicion(posicion)
{
	textura = LoadTexture(rutaTextura.c_str());
	SetTextureFilter(textura, TEXTURE_FILTER_POINT);
};

Enemigo::~Enemigo() {
	UnloadTexture(textura);
}

void Enemigo::Dibujar() {

	DrawTextureEx(textura, { posicion.x, posicion.y }, 0.0f, escala, WHITE);

}