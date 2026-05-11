#include "obstaculos.h"



obstaculos::obstaculos(float x, float y, float velocidad) {
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

void obstaculo::actualizar(){
    y += velocidad;
}

void obstaculos :: dibujar (Qpainter &painter){
    painter.drawPixmap(x, y, sprite);
}

void obstaculos::aplicarEfecto(Jugador &jugador)
{
    //Game over si choca con cajas
    if(tipo == "caja"){
        jugador.setVivo(false);
    }

    //Friccion
    else if (tipo == "bache"){
        jugador.setVelocidad(jugador.getVelocidad()* 0.7);
    }
    else if (tipo == "medusa"){
        jugador.setVelocidad(jugador.getVelocidad()*0.5);
    }

}

float obstaculos::getX(){
    return x;
}
float obstaculos::getY(){
    return y;
}

QString obstaculos::getTipo(){
    return tipo;
}
