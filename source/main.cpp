#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "grim.h"

int main(void)
{
    //init de pantalla
    InitWindow(1024, 768, "Jumping Grim");
    SetTargetFPS(60);

    //init de audio
    InitAudioDevice();
 
    Grim grim("assets/images/grim.png", { 50, 500 }, 0.5f, 0.0f, 10.0f, true);


    while (!WindowShouldClose())
    {
        grim.ActualizarPos();   //control del movimiento en cada frame

        BeginDrawing();
            
            grim.MostrarInfo({ 20,20 });    //muestra las coordenadas actuales de Grim o se ocultan, con la tecla M

            ClearBackground(RAYWHITE);

            grim.Dibujar();     //render del sprite

        EndDrawing();
    }

    //cerrar sist de audio
    CloseAudioDevice();

    CloseWindow();

    return 0;
}

