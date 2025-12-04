#include "Grim.h"

using namespace std;

//crear un Grim
//las variables despues de : inicializan los atributos de clase ANTES de que se ejecute el cuerpo del constr, asi no se repiten asignaciones inncesarias
//como las variables para el salto son fijas, las asigno en esta lista
Grim::Grim(const string rutaTextura, Vector2 pos, float escala, float rotacion, bool direccion, bool mostrando, float vel, bool saltando, bool subiendo, float alturaSalto, float velocidadSalto, float pisoBase)
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
    pisoBase(pisoBase),
    pisoActual(pisoBase),
    posInicioSalto(pos.y),
    enPlataforma(false),
    velocidadY(0.0f),
    velocidadX(0.0f),
    gravedad(0.25f),
    hitbox(100, 120, { 35, 30 }, true)   //inicializa hitbox
{       
    //carga de ruta de textura y filtro
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);    //este filtro para pixelart

    //carga de sonidos
    salto = LoadSound("assets/sound/salto.wav");
    SetSoundVolume(salto, 0.5f);    //por las dudas

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

    //hitbox.Draw();  //debug
}

//deprecado - rompe las colisiones - ahora se usa velocidadX y velocidadY para mejores calculos
//void Grim::Mover(float x, float y)
//{
//    posicion.x += x;
//    posicion.y += y;
//
//}

void Grim::ActualizarPos(const Plataforma plataformas[], int cantidad) {

    velocidadX = 0.0f;
    enPlataforma = false;

    if (IsKeyPressed(KEY_SPACE) && !saltando) Saltar(); //trigger del salto
    Salto();    //accion efectiva del salto

    if (((IsKeyDown(KEY_RIGHT)) || (IsKeyDown(KEY_D)))) {
        velocidadX = velocidad;
        direccion = true;
    }
    if (((IsKeyDown(KEY_LEFT)) || (IsKeyDown(KEY_A)))){
        velocidadX = -velocidad;
        direccion = false;
    }

    posicion.x += velocidadX;

    if (IsKeyPressed(KEY_R)) { ReiniciarPos(); }

    if (!subiendo && !enPlataforma)
        velocidadY += gravedad;
    else if (enPlataforma)
        velocidadY = 0;

    posicion.y += velocidadY;

    hitbox.Sincro(posicion);

    for (int i = 0; i < cantidad; i++)
    {
        ColisionPlataforma(plataformas[i]);
    }

    //para que no pase de largo en el borde inferior
    if (posicion.y + hitbox.Getbox().height > pisoBase) {
        posicion.y = pisoBase - hitbox.Getbox().height;
        velocidadY = 0;
        subiendo = false;
        saltando = false;
        enPlataforma = true;
        pisoActual = pisoBase;
    }

    //para evitar que se vaya por los laterales
    float margenIzq = 15.0f;
    float margenDer = GetScreenWidth() - 25.0f;

    float anchoGrim = hitbox.Getbox().width;

    //evita que se salga por la izquierda
    if (posicion.x < margenIzq)
        posicion.x = margenIzq;

    //evita que se salga por la derecha
    if (posicion.x + anchoGrim > margenDer)
        posicion.x = margenDer - anchoGrim;

    hitbox.Sincro(posicion); 
}

void Grim::ColisionPlataforma(const Plataforma& plataforma)
{
    const Hitbox& hbPlat = plataforma.GetHitbox();

    //mejora de colisiones y hitbox
    Rectangle rPlat = hbPlat.Getbox();
    Rectangle rGrim = hitbox.Getbox();

    if (!hitbox.Intersectan(hbPlat))
        return;
    
    //auxiliares
    float arribaGrim = rGrim.y;
    float abajoGrim = rGrim.y + rGrim.height;
    float arribaPlat = rPlat.y;
    float abajoPlat = rPlat.y + rPlat.height;

    float overlapY = min(abajoGrim, abajoPlat) - max(arribaGrim, arribaPlat);

    //pisa la plataforma - no pasa de largo
    if (velocidadY > 0 && abajoGrim <= arribaPlat + overlapY)
    {
        posicion.y -= overlapY;
        velocidadY = 0;
        saltando = false;
        subiendo = false;
        enPlataforma = true;
        pisoActual = arribaPlat;
        hitbox.Sincro(posicion);
        return;
    }

    //choca contra el techo, no permite atravesar desde abajo
    if (velocidadY < 0)
    {
        //cuánto se metió Grim dentro del techo
        float penetracion = abajoPlat - arribaGrim;

        //si hay penetración (penetracion > 0) significa que Grim está metiéndose en el techo
        if (penetracion > 0 && abajoGrim > abajoPlat)
        {
            //corregir posición empujando hacia abajo
            posicion.y += penetracion;

            velocidadY = 0;
            subiendo = false;

            hitbox.Sincro(posicion);
            return;
        }
    }

    //colision izquierda
    if (velocidadX > 0 &&
        rGrim.x + rGrim.width > rPlat.x &&
        rGrim.x < rPlat.x)
    {
        posicion.x = rPlat.x - rGrim.width;
        velocidadX = 0;
        hitbox.Sincro(posicion);
        return;
    }

    //colision derecha - rebota (falta ver alguna solucion para esto)
    if (velocidadX < 0 &&
        rGrim.x < rPlat.x + rPlat.width &&
        rGrim.x + rGrim.width > rPlat.x + rPlat.width)
    {
        posicion.x = rPlat.x + rPlat.width;
        velocidadX = 0;
        hitbox.Sincro(posicion);
        return;
    }
}

void Grim::Saltar() {

    //control para evitar spam de salto
    //mientras este en medio del salto, apretar el espacio no hace que salte nuevamente
    if (!saltando) {
        saltando = true;
        subiendo = true;
        posInicioSalto = posicion.y;
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

            //posInicioSalto - alturaSalto = controlo la "altura" del salto - con los valores fijos actuales "salta" hasta y=420 (noice)
            if (posicion.y <= posInicioSalto - alturaSalto)
                subiendo = false;   //si llego al limite indicado por la altura del salto, termino de subir
        }

        else {
            //si ya llego al limite, subiendo = false (cambia el control del segundo if)
            //ahora se suma la posicion actual y la velocidad para moverlo hacia abajo
            if (!enPlataforma) {    //se fija si no esta en la plataforma
                posicion.y += velocidadSalto;
            }

            if (posicion.y >= pisoBase) { //es decir, si ya llego al piso
                posicion.y = pisoBase; //evita que el Grim se hunda en el piso - el final del salto lo coloca en y = valor sin importar la suma de velocidadSalto (basicamente es un control de colision con el piso)
                saltando = false;   //ya no esta saltando, puede volver a saltar
            }
        }
    }
}

void Grim::ReiniciarPos() {

    SetPosicion({ 50, 600 });
    direccion = true; //lo pongo mirando a la derecha, por si se reinicia mirando a la izquierda

}

void Grim::MostrarInfo(Vector2 posicionInfo) {
    
    if (IsKeyPressed(KEY_M)) mostrando = !mostrando;

    if (mostrando) {
        DrawText(TextFormat("Posicion: (%.0f, %.0f)", posicion.x, posicion.y), posicionInfo.x, posicionInfo.y, 20, BLACK);
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