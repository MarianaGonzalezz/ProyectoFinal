#include "enemigo.h"
#include <QDebug>
#include <cstdlib>
#include <cmath>
#include <ctime>

enemigo::enemigo(float x, float y, bool esDificil)
    : x(x)
    , y(y)
    , dificil(esDificil)
    , tiempoDisparo(0)
    , aciertos(0)
    , fallos(0)
    , precisionActual(0)
{
    /*
    if (!sprite.load(":/sprites/calamardo.png")) {
        sprite = QPixmap(50, 50);
        sprite.fill(Qt::cyan);
    }
    */

    if (dificil) {
        intervaloDisparo = 1.2f;
        velocidadProyectil = 450.0f;
        precisionActual = 0.85f;
    } else {
        intervaloDisparo = 2.5f;
        velocidadProyectil = 300.0f;
        precisionActual = 0.50f;
    }

}

enemigo::~enemigo()
{
    qDebug() << "Calamardo - Aciertos:" << aciertos << "Fallos:" << fallos;
}

void enemigo::actualizar(float deltaTime)
{
    tiempoDisparo += deltaTime;
}

void enemigo::dibujar(QPainter& painter)
{
    painter.drawPixmap(int(x), int(y), sprite);
}
