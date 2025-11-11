#include "Grim.h"

using namespace std;

//crear un Grim
//las variables despues de : inicializan los atributos de clase ANTES de que se ejecute el cuerpo del constr, asi no se repiten asignaciones inncesarias
//como las variables para el salto son fijas, las asigno en esta lista
Grim::Grim(const string rutaTextura, Vector2 pos, float escala, float rotacion, bool direccion, bool mostrando, float vel, bool saltando, bool subiendo, float alturaSalto, float velocidadSalto, float pisoY)
    : posicion(pos),
    escala(escala),
    rotacion(rotacion),
    velocidad(vel),
    direccion(direccion),   //para donde mira
    mostrando(mostrando),   //info
    saltando(saltando),        //controlan si esta saltando para no spammear el salto en el aire infinitamente
    subiendo(subiendo),
    alturaSalto(alturaSalto),     //cuanto sube - techo de salto en el eje Y
    velocidadSalto(velocidadSalto),    //que "tan rapido" sube o baja - cuantos pixeles incrementa o decrementa en Y por unidad de tiempo
    pisoY(pisoY)          //piso inferior
{
    //carga de ruta de textura y filtro
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);    //este filtro para pixelart

    //carga de sonidos
    salto = LoadSound("assets/sound/salto.wav");

}

Grim::~Grim()
{
    //DESTRUCTOR DE GRIMS!!
    UnloadTexture(textura);
    UnloadSound(salto);
}

//render de Grim 
void Grim::Dibujar()
{   
    //dibuja todo el ancho y alto de la imagen "textura" (el sprite) y lo renderiza desde el pixel(?) 0,0
    //osea crea un cuadrado con el tamaño del sprite
    Rectangle grim = { 0, 0, (float)textura.width, (float)textura.height };

    //controlo para donde esta mirando, e invierte el ancho del rectángulo fuente (grim), la imagen queda "espejada", segun a donde mire
    if (!direccion)
        grim.width = -grim.width;

    //controlo la posicion en pantalla
    Rectangle dest = { posicion.x, posicion.y, textura.width * escala, textura.height * escala };
    Vector2 origen = { 0, 0 }; //usa 0,0 del sprite para rotarlo

    //con WHITE en Color se muestra el color original de la imagen
    DrawTexturePro(textura, grim, dest, origen, rotacion, WHITE);

    //con DrawTexturePro se puede renderizar una imagen completa o una parte (VER PARA SPRITE SHEETS)
}

void Grim::Mover(float x, float y)
{
    posicion.x += x;
    posicion.y += y;
}

void Grim::ActualizarPos() {

    //salto con barra espaciadora
    if (IsKeyPressed(KEY_SPACE) && !saltando) Saltar(); //trigger del salto
    Salto();    //accion efectiva del salto

    //movimiento con las flechas del teclado
    if (IsKeyDown(KEY_RIGHT)) { 
        Mover(velocidad, 0); 
        direccion = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        Mover(-velocidad, 0);
        direccion = false;
    }

    if (IsKeyPressed(KEY_R)) { ReiniciarPos(); }

}

void Grim::Saltar() {

    //control para evitar spam de salto
    //mientras este en medio del salto, apretar el espacio no hace que salte nuevamente
    if (!saltando) {
        saltando = true;
        subiendo = true;
        PlaySound(salto);
    }
}

void Grim::Salto(){
    
    if (!saltando) return;  //si no esta saltando, vuelve

    if (saltando) {
        if (subiendo) {
            //raylib tiene los ojos al reves asi que los calculos son restando los valores a la posicion actual
            
            //velocidad del salto - que tantos pixeles "sube" por unidad de tiempo
            posicion.y -= velocidadSalto;

            //pisoY - alturaSalto = controlo la "altura" del salto - con los valores fijos actuales "salta" hasta y=420 (noice)
            if (posicion.y <= pisoY - alturaSalto) 
                subiendo = false;   //si llego al limite indicado por la altura del salto, termino de subir
        }

        else {
            //si ya llego al limite, subiendo = false (cambia el control del segundo if)
            //ahora se suma la posicion actual y la velocidad para moverlo hacia abajo
            posicion.y += velocidadSalto;

            if (posicion.y >= pisoY) { //es decir, si ya llego al piso
                posicion.y = pisoY; //evita que el Grim se hunda en el piso - el final del salto lo coloca en y = 500 sin importar la suma de velocidadSalto (basicamente es un control de colision con el piso)
                saltando = false;   //ya no esta saltando, puede volver a saltar
            }
        }
    }
}

void Grim::ReiniciarPos() {

    SetPosicion({ 50, 500 });
    direccion = true; //lo pongo mirando a la derecha, por si se reinicia mirando a la izquierda

}

void Grim::MostrarInfo(Vector2 posicionInfo) {
    
    if (IsKeyPressed(KEY_M)) mostrando = !mostrando;

    if (mostrando) {
        DrawText(TextFormat("Posicion: (%.0f, %.0f)", posicion.x, posicion.y), posicionInfo.x, posicionInfo.y, 20, DARKGRAY);
    }

}

void Grim::SetPosicion(Vector2 pos)
{
    posicion = pos;
}

Vector2 Grim::GetPosicion() const
{
    return posicion;
}