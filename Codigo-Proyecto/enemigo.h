#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include "proyectil.h"


class enemigo{
private:

    float x,y;
    QPixmap sprite;

    bool dificil;

    float intervaloDisparo;
    float velocidadProyectil;
    float tiempoDisparo;

    // Aprendizaje ( solo si se juega en nivel dificil)
    int aciertos;
    int fallos;
    float precisionActual;

public:
    enemigo(float x, float y, bool esDificil);
    ~enemigo();

    void actualizar(float deltaTime);
    void dibujar(QPainter& painter);
    proyectil* lanzarProyectil(float jugadorX, float jugadorY, float jugadorVelX);

    void registrarAcierto();
    void registrarFallo();

    float getX() const;
    float getY() const;
    QRectF getHitbox() const;

};

#endif // ENEMIGO_H
