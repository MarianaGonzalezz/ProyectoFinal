#include "juego.h"
#include <QPainter>
#include <QDebug>

juego::juego(QWidget *parent)
    : QWidget(parent),
    nivelActual(nullptr),
    numeroNivel(1)
{
    setFixedSize(1280,720);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    connect(&timer, &QTimer::timeout, this, [=]()
            {
                if(nivelActual)
                {
                    nivelActual->actualizar(0.016f);

                    if(nivelActual->estaTerminado())
                    {
                        qDebug() << "Nivel terminado";

                        emit gameOver();

                        timer.stop();
                    }

                    update();
                }
            });
}

juego::~juego()
{
    delete nivelActual;
}

void juego::iniciarJuego(){
    cambiarNivel(1);
    timer.start(16);
    setFocus();
}
void juego::cambiarNivel(int numero)
{
    if(nivelActual)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }

    numeroNivel = numero;

    if(numero == 1)
    {
        nivelActual = new nivel1();
    }

    else if(numero == 2)
    {
        nivelActual = new nivel2();
    }

    nivelActual->iniciar();
}

void juego::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    if(nivelActual)
    {
        nivelActual->dibujar(painter);
    }
}

void juego::keyPressEvent(QKeyEvent *event)
{
    if(nivelActual)
    {
        nivelActual->keyPressEvent(event);
    }
}

void juego::keyReleaseEvent(QKeyEvent *event)
{
    if(nivelActual)
    {
        nivelActual->keyReleaseEvent(event);
    }
}

bool juego::estaTerminado() const
{
    if(nivelActual)
    {
        return nivelActual->estaTerminado();
    }

    return false;
}