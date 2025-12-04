#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "grim.h"
#include "meta.h"
#include "plataforma.h"
#include "enemigo.h"
#include "pantallas.h"

//funcion para controlar colisiones y condicion de victoria/derrota
bool CheckColision(const Hitbox& a, const Hitbox& b)
{
    return a.Intersectan(b);
}


int main(void)
{
    InitWindow(1900, 1000, "Grim: El atrapa-almas");
    SetTargetFPS(60);
    InitAudioDevice();

    //pantallas
    Pantallas pantallas;
    pantallas.SetEstado(MENU); //inicia mostrando el menu principal

    //variables
    float offsetArriba = 200.0f;
    bool victoria = false;
    bool derrota = false;

    //objetos

    Grim grim("assets/images/grim.png", { 840, 750 },
        0.4f,          // escala
        0.0f,          // rotación
        true,          // dirección
        true,          // mostrar info
        3.0f,          // velocidad
        false,         // saltando
        false,         // subiendo
        180.0f,        // alturaSalto
        5.0f,          // velocidadSalto
        940.0f         // pisoBase
    );

    Meta meta("assets/images/flame.png", 0.5f, { 840, 320 - offsetArriba });

    //Plataforma(const string rutaTextura, float escala, Vector2 posicion);
    Plataforma plataformas[10] = {

        //nivel 1
        {"assets/images/floor-long-new.png",     1.0f, { 200, 920 - offsetArriba }},   // 730
        {"assets/images/floor-long-ruined.png",  1.0f, { 750, 900 - offsetArriba }},   // 740
        {"assets/images/floor-long-new.png",     1.0f, {1300, 920 - offsetArriba }},   // 730

        //nivel 2
        {"assets/images/floor-short-new.png",    1.0f, { 150, 690 - offsetArriba }},   // 540
        {"assets/images/floor-short-ruined.png", 1.0f, {1550, 690 - offsetArriba }},   // 540

        {"assets/images/floor-long-new.png",     1.0f, { 600, 670 - offsetArriba }},   // 520
        {"assets/images/floor-long-new.png",     1.0f, {1100, 670 - offsetArriba }},   // 520

        //nivel 3
        {"assets/images/floor-short-ruined.png", 1.0f, { 400, 480 - offsetArriba }},   // 330
        {"assets/images/floor-short-ruined.png", 1.0f, {1300, 480 - offsetArriba }},   // 330

        {"assets/images/floor-long-new.png",     1.0f, { 750, 460 - offsetArriba }},   // 310
    };

    Plataforma piso[8] = {
        {"assets/images/floor-long-new.png", 1.0f, {   0, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, { 256, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, { 512, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, { 768, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, {1024, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, {1280, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, {1536, 940 }},
        {"assets/images/floor-long-new.png", 1.0f, {1900 - 256, 940 }}
    };

    //Enemigo(const string rutaTextura, float escala, Vector2 puntoA, Vector2 puntoB, float velocidad);
    Enemigo enemigos[4] = {
        //Enemigo diagonal 1
        { "assets/images/enemy-wings.png", 0.5f, { 200, 150 }, { 1700, 750 }, 250 },
        //Enemigo diagonal 2
        { "assets/images/enemy-wings.png", 0.5f, { 1700, 150 }, { 200, 750 }, 250 },
        //Enemigo vertical (centro)
        { "assets/images/enemy-wings.png", 0.5f, { 950, 150 }, { 950, 850 }, 150 },
        //Enemigo horizontal (superior)
        { "assets/images/enemy-wings.png", 0.5f,{ 200, 120 }, { 1700, 120 }, 140 }
    };

    //guardo las posiciones para el rinicio del juego
    Vector2 enemigosPosA[4];
    Vector2 enemigosPosB[4];

    for (int i = 0; i < 4; i++) {
        enemigosPosA[i] = enemigos[i].GetPuntoA();
        enemigosPosB[i] = enemigos[i].GetPuntoB();
    }

    //LOOP DE JUEGO//

    while (!WindowShouldClose())
    {
        float dTime = GetFrameTime();

        if (pantallas.GetEstado() == JUEGO)
        {
            grim.ActualizarPos(plataformas, 10);
            grim.ActualizarPos(piso, 8);

            for (int i = 0; i < 4; i++) {
                enemigos[i].ActualizarPos(dTime);
            }

            for (int i = 0; i < 3; i++) {
                if (CheckColision(grim.GetHitbox(), enemigos[i].GetHitbox()))
                {
                    pantallas.SetEstado(DERROTA);
                }
            }

            if (CheckColision(grim.GetHitbox(), meta.GetHitbox()))
            {
                pantallas.SetEstado(VICTORIA);
            }
        }

        //REINICIO DE JUEGO
        if (pantallas.reiniciarJuego)
        {
            //Reiniciar posicion de Grim
            grim.SetPosicion({ 300, 500 });

            //Reiniciar posicion de enemigos
            for (int i = 0; i < 4; i++) {
                enemigos[i].SetPuntos(enemigosPosA[i], enemigosPosB[i]);  // NUEVO MÉTODO
                enemigos[i].Resetear(); // vuelve dirección y posición exacta
            }

            pantallas.reiniciarJuego = false;
            pantallas.SetEstado(JUEGO);
        }

        //RENDER//

        BeginDrawing();   
        ClearBackground(RAYWHITE);
        
        //posibles estados de juego y render de pantallas
        switch (pantallas.GetEstado())
        {
        case MENU:
            pantallas.DibujarMenu();
            break;

        case JUEGO:
            grim.Dibujar();
            meta.Dibujar();

            for (int i = 0; i < 10; i++) plataformas[i].Dibujar();
            for (int i = 0; i < 8; i++) piso[i].Dibujar();
            for (int i = 0; i < 4; i++) enemigos[i].Dibujar();
            break;

        case VICTORIA:
        case DERROTA:
            pantallas.Dibujar();  // muestra pantalla correspondiente
            break;
        }

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

