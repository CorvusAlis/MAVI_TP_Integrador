#pragma once
#include "raylib.h"
#include "hitbox.h"
#include <string>


using namespace std;

class Enemigo {

private:
	Texture2D textura;
	float escala;
	Vector2 posicion;

	Hitbox hitbox;

public:

	Enemigo(const string rutaTextura, float escala, Vector2 posicion);
	~Enemigo();

	void Dibujar();

	const Hitbox& GetHitbox() const { return hitbox; }
};