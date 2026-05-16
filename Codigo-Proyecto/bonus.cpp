#include "bonus.h"
#include <QDebug>


const int Tiempo_bonus= 5;
const float Ancho_moneda= 30.0f;
const float Alto_moneda=30.0f;


bonus::bonus(float x, float y )
    : x(x), y(y), valorTiempo(Tiempo_bonus), activo(true)
{
    if (!sprite.load(":/sprites/moneda.png")) {
        qDebug() << "Error: No se pudo cargar la imagen de la moneda";
        sprite = QPixmap(Ancho_moneda, Alto_moneda);
        sprite.fill(Qt::yellow);
    }
    qDebug() << "Bonus creado en (" << x << "," << y << ")";
}

bonus::~bonus(){
    qDebug() << "Bonus destruido";
}

void bonus::actualizar(){
    // Moneda fija - no se mueve
}

void bonus::dibujar(QPainter& painter){
    if (!activo) return;
    painter.drawPixmap(static_cast<int>(x), static_cast<int>(y), sprite);
}

int bonus::aplicarEfecto(jugador& jugador){
    if(!activo) return 0;

    if (jugador.estaVivo()) {
        activo = false;
        qDebug() << "¡Moneda recogida! +" << valorTiempo << "segundos";
        return valorTiempo;
    }
    return 0;
}

// Getters

float bonus::getX() const{
    return x;
}

float bonus::getY() const{
    return y;
}

QRectF bonus::getHitbox() const{
    return QRectF(x,y, Ancho_moneda, Alto_moneda);
}

bool bonus::estaActivo() const{
    return activo;
}

// Setters

void bonus::setActivo(bool estado){
    activo=estado;
}



