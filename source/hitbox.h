#pragma once
#include "raylib.h"

class Hitbox {

private: 
	Rectangle hbox;	//tamaño real de la colision
	Vector2 offset;	//alineamiento con el sprite - la hbox puede ser mas chico o mas grande que el sprite
	bool debug;	//para testear

	//auxiliares para saber desde que direccion fue la colision
	//se colocan como funciones privadas por que son para logica interna de la clase
	float left()   const { return hbox.x; }
	float right()  const { return hbox.x + hbox.width; }
	float top()    const { return hbox.y; }
	float bottom() const { return hbox.y + hbox.height; }

public:

	//cnstructor
	Hitbox(float ancho, float alto, Vector2 offset = { 0,0 }, bool debug = false);

	void Sincro(Vector2 posSprite); //mueve la hitbox con el sprite

	Rectangle Getbox() const;	//devuelve hbox actual

	bool Intersectan(const Hitbox& objeto) const;	//es const por que solo devuelve informacion, no modifica

	//colisiones con hitbox de otro objeto - solo detectan si hubo colision y desde donde
	bool ColisionaArriba(const Hitbox& objeto) const;
	bool ColisionaAbajo(const Hitbox& objeto) const;
	bool ColisionaIzquierda(const Hitbox& objeto) const;
	bool ColisionaDerecha(const Hitbox& objeto) const;

	//debug
	void Draw() const;
	void DebugOn(bool activo);
};