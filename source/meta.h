#pragma once
#include "raylib.h"
#include <string>

using namespace std;

class Meta {

private:

	Texture2D textura;
	float escala;
	Vector2 posicion;

	//para ciclo de animacion con spritesheet

	int anchoFrame;
	int altoFrame;
	int totalFrames;
	int actualFrame;

	float frameTime; //tiempo entre cada frame
	float timer;

	Rectangle source; //rectangulo que se va a "pintar" con los sprites.

public:

	//constructor y destructor
	Meta(const string rutaTextura, float escala, Vector2 posicion);
	~Meta();

	void Dibujar();
};