#pragma once
#include "raylib.h"
#include <string>


using namespace std;

class Enemigo {

private:
	Texture2D textura;
	float escala;
	Vector2 posicion;

public:

	Enemigo(const string rutaTextura, float escala, Vector2 posicion);
	~Enemigo();

	void Dibujar();
};