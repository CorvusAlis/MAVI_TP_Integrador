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

    Grim grim("assets/images/grim.png", { 300, 500 },
        0.5f,          // escala
        0.0f,          // rotación
        true,          // dirección
        true,          // mostrar info
        10.0f,         // velocidad
        false,         // saltando
        false,         // subiendo
        150.0f,        // alturaSalto
        7.0f,          // velocidadSalto
        900.0f        // pisoBase
    );

    Meta meta("assets/images/flame.png", 0.5f, { 950, 570 });

    //Plataforma(const string rutaTextura, float escala, Vector2 posicion);
    Plataforma plataformas[10] = {

        // --- NIVEL 1 (Cerca del piso, más separados) ---
        {"assets/images/floor-long-new.png",     1.0f, {   80, 900 }},
        {"assets/images/floor-short-ruined.png", 1.0f, {  900, 880 }},
        {"assets/images/floor-long-ruined.png",  1.0f, { 1700, 910 }},

        // --- NIVEL 2 (subido y más espaciado) ---
        {"assets/images/floor-short-new.png",    1.0f, {  200, 740 }},
        {"assets/images/floor-long-new.png",     1.0f, { 1050, 720 }},
        {"assets/images/floor-short-ruined.png", 1.0f, { 1850, 740 }},

        // --- NIVEL 3 (más altos y separados) ---
        {"assets/images/floor-short-new.png",    1.0f, {  150, 580 }},
        {"assets/images/floor-long-ruined.png",  1.0f, { 1100, 560 }},
        {"assets/images/floor-short-new.png",    1.0f, { 1950, 580 }},

        // --- NIVEL 4 (superior, más arriba) ---
        {"assets/images/floor-long-new.png",     1.0f, {  700, 380 }}
    };

    //Enemigo(const string rutaTextura, float escala, Vector2 puntoA, Vector2 puntoB, float velocidad);
    Enemigo enemigos[3] = {
    {"assets/images/enemy-wings.png", 0.5f, { 450, 200 }, { 1700, 200 }, 150},
    {"assets/images/enemy-wings.png", 0.5f, { 300, 100 }, { 300, 800 }, 120},
    {"assets/images/enemy-wings.png", 0.5f, { 1000, 300 }, { 1700, 800 }, 130}
    };

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        float dTime = GetFrameTime();

        grim.ActualizarPos(plataformas, 10);

        for (int i = 0; i < 3; i++) {
            enemigos[i].ActualizarPos(dTime);
        }

        //control de derrota
        for (int i = 0; i < 3; i++) {
            if (CheckColision(grim.GetHitbox(), enemigos[i].GetHitbox()))
            derrota = true;
        }

        //control de victoria
        if (CheckColision(grim.GetHitbox(), meta.GetHitbox())) {
            victoria = true;
        }

        BeginDrawing();   

            //grim.MostrarInfo({ 20,20 });    //muestra las coordenadas actuales de Grim o se ocultan, con la tecla M
            grim.Dibujar();
            meta.Dibujar();

            for (int i = 0; i < 10; i++) {
                plataformas[i].Dibujar();
            }

            for (int i = 0; i < 3; i++) {
                enemigos[i].Dibujar();
            }

            if (victoria) ClearBackground(LIME);
            else 
            if (derrota) ClearBackground(RED);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

