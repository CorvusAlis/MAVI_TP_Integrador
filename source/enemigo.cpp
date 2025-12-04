#include "Enemigo.h"

using namespace std;

Enemigo::Enemigo(const string rutaTextura, float escala,
	Vector2 puntoA, Vector2 puntoB,
	float velocidad) :
	escala(escala),
	puntoA(puntoA),
	puntoB(puntoB),
	velocidad(velocidad),
	direccion(1),
	hitbox(120, 90, { 5, 15 }, true)
{
	textura = LoadTexture(rutaTextura.c_str());
	SetTextureFilter(textura, TEXTURE_FILTER_POINT);

	posicion = puntoA;
}

Enemigo::~Enemigo() {
	UnloadTexture(textura);
}

void Enemigo::ActualizarPos(float dTime)
{
    Vector2 objetivo = (direccion == 1) ? puntoB : puntoA;  //si va o vuelve entre A y B

    //direccion hacia el objetivo
    Vector2 delta = {
        objetivo.x - posicion.x,
        objetivo.y - posicion.y
    };

    //distancia al objetivo - "largo" del vector
    float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);

    if (dist < velocidad * dTime) {
        posicion = objetivo;
        direccion *= -1;    // invertir dirección
        return;
    }

    //normalizar vector - hace que la velocidad sea constante independiente de la distacna
    Vector2 normal = { delta.x / dist, delta.y / dist };

    posicion.x += normal.x * velocidad * dTime;
    posicion.y += normal.y * velocidad * dTime;

    hitbox.Sincro(posicion);
}


void Enemigo::Dibujar() {

	DrawTextureEx(textura, { posicion.x, posicion.y }, 0.0f, escala, WHITE);

	//hitbox.Draw();

}

void Enemigo::Resetear()
{
    posicion = puntoA;
    direccion = 1;      // comienza yendo hacia puntoB
    hitbox.Sincro(posicion);
}