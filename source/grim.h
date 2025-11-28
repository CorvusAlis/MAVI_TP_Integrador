#pragma once
#include "raylib.h"
#include <string>

using namespace std;

class Grim {

private:
	//atributos para render de imagen

	Texture2D textura; //imagen que se va a mostrar
	float escala;
	float rotacion;
	bool direccion; //true = derecha - false = izquierda
	bool mostrando;	//si se esta mostrando info en pantalla o no

	//atributos para control de movimiento
	Vector2 posicion;
	float velocidad;

	//atributos para controlar el salto
	bool saltando;
	bool subiendo;
	float alturaSalto;
	float velocidadSalto;
	float pisoY;

	//atributos de sonido
	Sound salto;

public:

	//constructor
	Grim(const string rutaTextura, Vector2 pos,
		float escala = 1.0f, float rotacion = 0.0f,
		bool direccion = true, bool mostrando = true, float vel = 3.0f,
		bool saltando = false, bool subiendo = false,
		float alturaSalto = 150.0f, float velocidadSalto = 7.0f, float pisoY = 500.0f);


	//destructor
	~Grim();

	void Dibujar();	//render de la imagen

	void Mover(float x, float y);

	void Saltar();
	
	void Salto();

	void ReiniciarPos();

	void SetPosicion(Vector2 pos);

	//controlador principal de movimiento
	//movimiento con flecjhas derecha e izquierda - salto con barra de espacio - reiinicio de posicion con R
	void ActualizarPos();	

	void MostrarInfo(Vector2 posicionInf);	//mostrar y ocultar coordenadas de posicion con M

	Vector2 GetPosicion() const; //devuelve la posicion actual de la imagen
};