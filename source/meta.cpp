#include "Meta.h"

using namespace std;

Meta::Meta(const string rutaTextura, float escala, Vector2 posicion) :
	escala(escala), posicion(posicion)
{
	textura = LoadTexture(rutaTextura.c_str());
	SetTextureFilter(textura, TEXTURE_FILTER_POINT);

	//configuracion inicial de animacion con spritesheet
	totalFrames = 8;
	anchoFrame = textura.width / totalFrames;
	altoFrame = textura.height;
	actualFrame = 0; //empieza en el frame 0
	frameTime = 0.15f; //tiempo que dura cada frame (rapidez de la animacion)
	timer = 0;

	source = { 0, 0, (float)anchoFrame, (float)altoFrame };
}

Meta::~Meta() {
	UnloadTexture(textura);
}

void Meta::Dibujar() {

	//manejo de la animacion por spirtesheet
	timer += GetFrameTime();

	if (timer >= frameTime) {
		timer = 0;
		actualFrame++; //avanza al siguiente frame
		if (actualFrame >= totalFrames) actualFrame = 0; //vuelve al frame del principio para empezar el loop

		source.x = actualFrame * anchoFrame;	//mueve al siguiente frame del sprite
	}

	Rectangle dest{
		posicion.x,
		posicion.y,
		anchoFrame * escala,
		altoFrame * escala
	};

	Vector2 origin = { 0,0 };

	DrawTexturePro(textura, source, dest, origin, 0.0f, WHITE);

}