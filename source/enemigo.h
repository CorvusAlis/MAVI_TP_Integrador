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

	Vector2 puntoA;
	Vector2 puntoB;
	float velocidad;
	int direccion;

	Hitbox hitbox;

public:

	Enemigo(const string rutaTextura, float escala, Vector2 puntoA, Vector2 puntoB, float velocidad);
	~Enemigo();

	void Dibujar();
	void ActualizarPos(float dTime);

	const Hitbox& GetHitbox() const { return hitbox; }
};