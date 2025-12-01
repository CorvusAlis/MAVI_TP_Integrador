#pragma once
#include "raylib.h"
#include "hitbox.h"
#include <string>

using namespace std;

class Plataforma {

private:
	Texture2D textura;
	float escala;
	Vector2 posicion;

	Hitbox hitbox;

public:

	Plataforma(const string rutaTextura, float escala, Vector2 posicion);
	~Plataforma();

	void Dibujar();

	const Hitbox& GetHitbox() const { return hitbox; }
};