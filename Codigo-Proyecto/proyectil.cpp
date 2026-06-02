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
    tiempoVida = 0;

    if(!sprite.load(":/sprites/cangreburger.png")){

        qDebug() << "ERROR cargando cangreburger";
    }

}

void proyectil ::actualizar(float deltaTime){

    x += velocidadX * deltaTime;
    y += velocidadY * deltaTime;

    tiempoVida += deltaTime;
    velocidadY += gravedad * deltaTime;
}

void proyectil::dibujar(QPainter &painter){
    painter.drawPixmap(QRect(x, y, 60,60), sprite, sprite.rect());

    //VISTA DEL HITBOX
    //painter.setPen(Qt::red);
    //painter.drawRect(getHitbox());

}

float proyectil::getX(){
    return x;
}

float proyectil::getY(){
    return y;
}
QRectF proyectil::getHitbox() const{
    return QRectF (x+10, y+10, 35, 50);

}
float proyectil::getTiempoVida()const{
    return tiempoVida;
}