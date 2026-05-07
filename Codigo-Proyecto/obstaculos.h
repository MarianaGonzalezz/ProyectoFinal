#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include "jugador.h"
#include <QPainter>
#include <QPixmap>
#include <QString>

class obstaculos
{
private:
    float x;
    float y;

    float velocidad;

    QString tipo;
    QPixmap sprite;

public:
    obstaculos(float x, float y, float velocidad, QString tipo);

    void actualizar();

    void dibujar(Qpainter& painter);

    void aplicarEfecto(Jugador& jugador);

    float getX;
    float getY;

    QString getTipo();
};

#endif // OBSTACULOS_H
