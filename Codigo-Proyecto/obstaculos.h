#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include "jugador.h"
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QRectF>

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
    ~obstaculos();

    void actualizar(float deltaTime);

    void dibujar(QPainter& painter);

    void aplicarEfecto(jugador& bob);

    float getX() const;
    float getY() const;
    float getvelocidad() const;
    QString getTipo() const;
    QRectF getHitbox() const;


    void setPosicion(float nx, float ny);
    void setVelocidad(float nuevaVelocidad);
};

#endif // OBSTACULOS_H