#include "Hitbox.h"

Hitbox::Hitbox(float ancho, float alto, Vector2 off, bool dbg)
    : hbox{ 0, 0, ancho, alto }, 
    offset(off), 
    debug(dbg)
{
}

void Hitbox::Sincro(Vector2 posSprite)
{
    //toma la posicion del sprite y la sincroniza con la hbox
    //en el constructor, x e y se inician en 0,0 - ahora se le asignan los valores
    hbox.x = posSprite.x + offset.x;
    hbox.y = posSprite.y + offset.y;
}

Rectangle Hitbox::Getbox() const
{
    return hbox;
}

bool Hitbox::Intersectan(const Hitbox& objeto) const
{
    return CheckCollisionRecs(hbox, objeto.hbox);   //detecta la colision entre el objeto que tiene la hitbox, y la hitbox de otro objeto
}

void Hitbox::Draw() const
{
    if (debug)
    {
        DrawRectangleLines(hbox.x, hbox.y, hbox.width, hbox.height, RED);   //dibuja un rectangulo rojo para mostrar el area de la hbox
    }
}

void Hitbox::DebugOn(bool activo)
{
    debug = activo;
}
