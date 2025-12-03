#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "grim.h"
#include "meta.h"
#include "plataforma.h"
#include "enemigo.h"

//funcion para controlar colisiones y condicion de victoria/derrota
bool CheckColision(const Hitbox& a, const Hitbox& b)
{
    return a.Intersectan(b);
}


int main(void)
{
    InitWindow(1900, 1000, "Jumping Grim");
    SetTargetFPS(60);
    InitAudioDevice();

    //variables

    bool victoria = false;
    bool derrota = false;

    //objetos

    Grim grim("assets/images/grim.png", { 50, 600 }, 0.5f, 0.0f, 10.0f, true);
    Meta meta("assets/images/flame.png", 0.5f, { 700, 500 });

    //Plataforma(const string rutaTextura, float escala, Vector2 posicion);
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

        //control de derrota
        if (
            CheckColision(grim.GetHitbox(), eHorizontal.GetHitbox()) ||
            CheckColision(grim.GetHitbox(), eVertical.GetHitbox()) ||
            CheckColision(grim.GetHitbox(), eDiagonal.GetHitbox())
            )
        {
            derrota = true;
        }

        //control de victoria
        if (CheckColision(grim.GetHitbox(), meta.GetHitbox())) {
            victoria = true;
        }

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

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

