#include "obstaculos.h"


obstaculos::obstaculos(float x, float y, float velocidad, QString tipo) {
    this -> x = x;
    this -> y = y;
    this -> velocidad = velocidad;
    this -> tipo = tipo;

    if(tipo == "caja"){
        sprite.load(":/sprites/O1caja.png");
    } else if (tipo == "bache"){
        sprite.load(":/sprites/O3baches.png");
    } else if (tipo == "medusas"){
        sprite.load(":/sprites/O2medusas.png");
    }
}

obstaculos :: ~obstaculos(){}

void obstaculos::actualizar(float deltaTime){
    y += velocidad * deltaTime;
}

void obstaculos :: dibujar (QPainter &painter){
    painter.drawPixmap( QRectF(x, y, 120, 120),
    sprite,
    QRectF(0,0,sprite.width(), sprite.height()));
}

void obstaculos::aplicarEfecto(jugador &jugador)
{
    //Game over si choca con cajas
    if(tipo == "caja"){
        jugador.setVivo(false);
    }

    //Friccion
    else if (tipo == "bache"){
        jugador.setVelocidadX(jugador.getVelocidadX()* 0.7);
    }
    else if (tipo == "medusas"){
        jugador.setVelocidadX(jugador.getVelocidadX()*0.5);
    }

}

float obstaculos::getX() const{
    return x;
}
float obstaculos::getY() const{
    return y;
}

QString obstaculos::getTipo() const{
    return tipo;
}

float obstaculos::getVelocidad() const
{
    return velocidad;
}

QRectF obstaculos::getHitbox() const{
    return QRectF (x+20, y+20, 60, 60);
}
void obstaculos::setPosicion(float nx, float ny)
{
    x = nx;
    y = ny;
}

void obstaculos::setVelocidad(float nuevaVelocidad)
{
    velocidad = nuevaVelocidad;
}
