#ifndef NIVEL_H
#define NIVEL_H

#include <QPainter>
#include <QKeyEvent>
#include "jugador.h"

class nivel
{
protected:
    jugador bob;

    bool terminado;

    bool victoria;

public:
    nivel();

    virtual ~nivel();

    virtual void iniciar() = 0;

    virtual void actualizar (float deltaTime) = 0;

    virtual void dibujar (QPainter& painter) = 0;

    virtual void keyPressEvent (QKeyEvent* event) = 0;

    virtual void keyReleaseEvent (QKeyEvent* event) = 0;


    bool estaTerminado() const;

    bool hayVictoria() const;

    jugador& getJugador();

    void setTerminado(bool estado);

    void setVictoria(bool estado);

};

#endif // NIVEL_H
