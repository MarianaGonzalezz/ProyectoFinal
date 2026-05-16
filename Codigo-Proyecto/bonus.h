#ifndef BONUS_H
#define BONUS_H

#include "jugador.h"
#include <QPainter>
#include <QPixmap>
#include <QRectF>


class bonus{
private:
    float x,y;
    int valorTiempo;
    QPixmap sprite;
    bool activo;

public:

    bonus(float x, float y);
    ~bonus();

    // Metodos

    void actualizar();
    void dibujar(QPainter& painter);
    int aplicarEfecto(jugador& jugador);

    // Getters

    float getX() const;
    float getY() const;
    QRectF getHitbox() const;
    bool estaActivo() const;

    // setters

    void setActivo(bool estado);
};

#endif // BONUS_H
