#include "Plataforma.h"

using namespace std;

Plataforma::Plataforma(const string rutaTextura, float escala, Vector2 posicion) :
	escala(escala), posicion(posicion)
{
	textura = LoadTexture(rutaTextura.c_str());
	SetTextureFilter(textura, TEXTURE_FILTER_POINT);
};

Plataforma::~Plataforma() {
	UnloadTexture(textura);
}

void Plataforma::Dibujar(){

	DrawTextureEx(textura, { posicion.x, posicion.y }, 0.0f, escala, WHITE);	//con DrawTextureEx controlo escala y rotacion

}