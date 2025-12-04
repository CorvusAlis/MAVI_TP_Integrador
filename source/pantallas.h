#pragma once
#include "raylib.h"

//manejo de los estados posibles del juego para dibujar las pantallas correspondientes
enum EstadoPantalla {
    MENU,
    JUEGO,
    DERROTA,
    VICTORIA
};

class Pantallas
{
private:
    EstadoPantalla estadoActual;

public:
    bool reiniciarJuego;
    //Texture2D grimMenuTex;
    //Texture2D metaMenuTex;

    Pantallas();
    ~Pantallas();

    void SetEstado(EstadoPantalla nuevoEstado);
    EstadoPantalla GetEstado() const;

    //cargar las texturas en el menu esta dando problemas - quizas en otro momento lo arregle, por ahora el menu queda sin dibujos
    //void CargarTexturas();
    //void DescargarTexturas();

    void Dibujar();

    void DibujarMenu();
    void DibujarVictoria();
    void DibujarDerrota();
};
