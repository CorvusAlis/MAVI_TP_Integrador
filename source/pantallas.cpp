#include "pantallas.h"
#include "raylib.h"

Pantallas::Pantallas()
{
    estadoActual = MENU; //inicia en el menu principal
    reiniciarJuego = false;

    //se cargan las texturas en el metodo CargarTexturas()
    grimMenuTex = { 0 };
    metaMenuTex = { 0 };
}

Pantallas::~Pantallas()
{
    //daban error - incorrecto uso del UnloadTexture
    //UnloadTexture(grimMenuTex);
    //UnloadTexture(metaMenuTex);
}

void Pantallas::CargarTexturas()
{
    grimMenuTex = LoadTexture("assets/images/grim.png");
    metaMenuTex = LoadTexture("assets/images/flame.png");
}

void Pantallas::DescargarTexturas()
{
    if (grimMenuTex.id != 0) UnloadTexture(grimMenuTex);
    if (metaMenuTex.id != 0) UnloadTexture(metaMenuTex);
}

void Pantallas::SetEstado(EstadoPantalla nuevoEstado)
{
    estadoActual = nuevoEstado;
    reiniciarJuego = false;
}

EstadoPantalla Pantallas::GetEstado() const
{
    return estadoActual;
}

void Pantallas::Dibujar()
{
    switch (estadoActual)
    {
    case MENU:
        DibujarMenu();
        break;

    case JUEGO:
        break;

    case DERROTA:
        DibujarDerrota();
        break;

    case VICTORIA:
        DibujarVictoria();
        break;
    }
}

void Pantallas::DibujarMenu()
{
    ClearBackground(BLACK);
    CargarTexturas();
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    float escalaGrim = 300.0f / grimMenuTex.height;
    float escalaMeta = 150.0f / metaMenuTex.height;

    float offsetY = 300.0f;

    //dibuja a Grim a la izquierda
    DrawTextureEx(
        grimMenuTex,
        { 120.0f, screenH / 2.0f - (grimMenuTex.height * escalaGrim) / 2.0f + offsetY },
        0.0f,
        escalaGrim,
        Fade(WHITE, 0.85f)
    );

    //dibuja llamas a la derecha
    DrawTextureEx(
        metaMenuTex,
        { screenW - 120.0f - (metaMenuTex.width * escalaMeta),
          screenH / 2.0f - (metaMenuTex.height * escalaMeta) / 2.0f + offsetY },
        0.0f,
        escalaMeta,
        Fade(WHITE, 0.85f)
    );

    const char* titulo = "GRIM: EL ATRAPA-ALMAS";
    DrawText(titulo,
        GetScreenWidth() / 2 - MeasureText(titulo, 60) / 2,
        120,
        60,
        WHITE);

    // Botón Iniciar
    Rectangle botonJugar = { screenW / 2 - 150, screenH / 2 - 50, 300, 80 };
    bool hoverJugar = CheckCollisionPointRec(GetMousePosition(), botonJugar);

    DrawRectangleRec(botonJugar, hoverJugar ? DARKGREEN : GREEN);
    DrawRectangleLinesEx(botonJugar, 3, BLACK);

    const char* txtJugar = "JUGAR!";
    DrawText(txtJugar,
        botonJugar.x + botonJugar.width / 2 - MeasureText(txtJugar, 30) / 2,
        botonJugar.y + botonJugar.height / 2 - 15,
        30,
        WHITE);

    // Botón Salir
    Rectangle botonSalir = { screenW / 2 - 150, screenH / 2 + 60, 300, 80 };
    bool hoverSalir = CheckCollisionPointRec(GetMousePosition(), botonSalir);

    DrawRectangleRec(botonSalir, hoverSalir ? DARKGRAY : GRAY);
    DrawRectangleLinesEx(botonSalir, 3, BLACK);

    const char* txtSalir = "SALIR";
    DrawText(txtSalir,
        botonSalir.x + botonSalir.width / 2 - MeasureText(txtSalir, 30) / 2,
        botonSalir.y + botonSalir.height / 2 - 15,
        30,
        WHITE);

    //click boton
    if (hoverJugar && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SetEstado(JUEGO);
    }

    if (hoverSalir && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        DescargarTexturas();
        CloseWindow(); // Cierra el programa
    }
}

void Pantallas::DibujarVictoria()
{
    ClearBackground(LIME);

    const char* msg = "Grim alcanzo el alma!";
    DrawText(msg,
        GetScreenWidth() / 2 - MeasureText(msg, 50) / 2,
        GetScreenHeight() / 3,
        50,
        WHITE);

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    Rectangle botonRec = { screenW / 2 - 150, screenH / 2, 300, 80 };
    bool hover = CheckCollisionPointRec(GetMousePosition(), botonRec);

    DrawRectangleRec(botonRec, hover ? DARKGRAY : GRAY);
    DrawRectangleLinesEx(botonRec, 3, BLACK);

    const char* botonTxt = "MENU";
    DrawText(botonTxt,
        botonRec.x + botonRec.width / 2 - MeasureText(botonTxt, 30) / 2,
        botonRec.y + botonRec.height / 2 - 15,
        30,
        WHITE);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SetEstado(MENU); //vuelve al menu principal
    }
}

void Pantallas::DibujarDerrota()
{
    ClearBackground(RED);

    const char* msg = "Grim no logro alcanzar el alma...";
    const char* boton = "REINICIAR";

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    //texto principal
    DrawText(msg,
        screenW / 2 - MeasureText(msg, 50) / 2,
        screenH / 3,
        50,
        WHITE);

    //botón de reinicio
    Rectangle botonRec = {
        screenW / 2 - 150,
        screenH / 2,
        300,
        80
    };

    //hover
    bool hover = CheckCollisionPointRec(GetMousePosition(), botonRec);

    DrawRectangleRec(botonRec, hover ? DARKGRAY : GRAY);
    DrawRectangleLinesEx(botonRec, 3, BLACK);

    DrawText(boton,
        botonRec.x + botonRec.width / 2 - MeasureText(boton, 30) / 2,
        botonRec.y + botonRec.height / 2 - 15,
        30,
        WHITE);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        reiniciarJuego = true;
    }
}