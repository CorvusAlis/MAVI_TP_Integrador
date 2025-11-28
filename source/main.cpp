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

    Grim grim("assets/images/grim.png", { 50, 500 }, 0.5f, 0.0f, 10.0f, true);
    Meta meta("assets/images/flame.png", 0.5f, { 700, 500 });
    Plataforma plataformaRota("assets/images/floor-long-ruined.png", 1.0f, { 100,100 });
    Plataforma plataformaSana("assets/images/floor-long-new.png", 1.0f, { 250,300 });
    Enemigo enemigo1("assets/images/enemy-wings.png", 0.5f, { 750, 120 });
    

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);

        grim.ActualizarPos();   //control del movimiento en cada frame

        BeginDrawing();   

            //grim.MostrarInfo({ 20,20 });    //muestra las coordenadas actuales de Grim o se ocultan, con la tecla M
            grim.Dibujar();     //render del sprite
            meta.Dibujar();
            plataformaRota.Dibujar();
            plataformaSana.Dibujar();
            enemigo1.Dibujar();

        EndDrawing();
    }

    //cerrar sist de audio
    CloseAudioDevice();

    CloseWindow();

    return 0;
}

