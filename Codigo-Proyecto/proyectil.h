#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QPainter>
#include <QPixmap>

class proyectil
{
    float x;
    float y;

    float velocidadX;
    float velocidadY;

    float gravedad;

    float tiempoVida;

    QPixmap sprite;

public:

    proyectil(float x,
              float y,
              float velocidadX,
              float velocidadY);

    void actualizar(float deltaTime);

    void dibujar(QPainter& painter);

    float getX();
    float getY();
    QRectF getHitbox() const;

    float getTiempoVida() const;
};

#endif // PROYECTIL_H
