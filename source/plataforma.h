#pragma once
#include "raylib.h"
#include <string>

using namespace std;

class Plataforma {

private:
	Texture2D textura;
	float escala;
	Vector2 posicion;

public:

	Plataforma(const string rutaTextura, float escala, Vector2 posicion);
	~Plataforma();

	void Dibujar();
};