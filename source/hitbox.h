#pragma once
#include "raylib.h"

class Hitbox {

private: 
	Rectangle hbox;	//tamaño real de la colision
	Vector2 offset;	//alineamiento con el sprite - la hbox puede ser mas chico o mas grande que el sprite
	bool debug;	//para testear

public:

	//cnstructor
	Hitbox(float ancho, float alto, Vector2 offset = { 0,0 }, bool debug = false);

	void Sincro(Vector2 posSprite); //mueve la hitbox con el sprite

	Rectangle Getbox() const;	//devuelve hbox actual

	bool Intersectan(const Hitbox& objeto) const;	//es const por que solo devuelve informacion, no modifica

	//debug
	void Draw() const;
	void DebugOn(bool activo);
};