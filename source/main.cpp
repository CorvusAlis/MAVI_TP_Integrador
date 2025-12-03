#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "grim.h"
#include "meta.h"
#include "plataforma.h"
#include "enemigo.h"

int main(void)
{
    //init de pantalla
    InitWindow(1900, 1000, "Jumping Grim");
    SetTargetFPS(60);

    //init de audio
    InitAudioDevice();

    //variables

    bool victoria = false;
    bool derrota = false;

    //objetos

    Grim grim("assets/images/grim.png", { 50, 600 }, 0.5f, 0.0f, 10.0f, true);
    Meta meta("assets/images/flame.png", 0.5f, { 700, 500 });
    Plataforma plataformaRota("assets/images/floor-long-ruined.png", 1.0f, { 100,100 });
    Plataforma plataformaSana("assets/images/floor-long-new.png", 1.0f, { 250,300 });

    //Enemigo(const string rutaTextura, float escala, Vector2 puntoA, Vector2 puntoB, float velocidad);
    Enemigo eHorizontal("assets/images/enemy-wings.png", 0.5f, { 450, 200 }, { 1700, 200 }, 150);
    Enemigo eVertical("assets/images/enemy-wings.png", 0.5f, { 300, 100 }, { 300, 800 }, 120);
    Enemigo eDiagonal("assets/images/enemy-wings.png", 0.5f, { 1000, 300 }, { 1700, 800 }, 130);

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        float dTime = GetFrameTime();

        grim.ActualizarPos();   //control del movimiento en cada frame
        eHorizontal.ActualizarPos(dTime);
        eVertical.ActualizarPos(dTime);
        eDiagonal.ActualizarPos(dTime);

        if (grim.GetHitbox().Intersectan(meta.GetHitbox())) {
            victoria = true;
        }

        //if (grim.GetHitbox().Intersectan(enemigo1.GetHitbox())) {
        //    derrota = true;
        //}

        BeginDrawing();   

            //grim.MostrarInfo({ 20,20 });    //muestra las coordenadas actuales de Grim o se ocultan, con la tecla M
            grim.Dibujar();     //render del sprite
            meta.Dibujar();
            plataformaRota.Dibujar();
            plataformaSana.Dibujar();
            eHorizontal.Dibujar();
            eVertical.Dibujar();
            eDiagonal.Dibujar();

            if (victoria) ClearBackground(LIME);
            if (derrota) ClearBackground(RED);

        EndDrawing();
    }

    //cerrar sist de audio
    CloseAudioDevice();

    CloseWindow();

    return 0;
}

