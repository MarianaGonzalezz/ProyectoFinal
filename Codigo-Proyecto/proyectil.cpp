#include <QDebug>
#include "proyectil.h"

proyectil::proyectil(float x,
                     float y,
                     float velocidadX,
                     float velocidadY)
{

    this->x = x;
    this->y = y;

    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;

    gravedad = 900.0f;

    if(!sprite.load(":/sprites/cangreburger.png")){

        qDebug() << "ERROR cargando cangreburger";
    }

}

void proyectil ::actualizar(float deltaTime){

    x += velocidadX * deltaTime;
    y += velocidadY * deltaTime;

    velocidadY += gravedad * deltaTime;
}

void proyectil::dibujar(QPainter &painter){
    painter.drawPixmap(x, y, sprite);

}

float proyectil::getX(){
    return x;
}

float proyectil::getY(){
    return y;
}
QRectF proyectil::getHitbox() const{
    return QRectF (x, y,
                  sprite.width(), sprite.height());

}