#include "juego.h"
#include <QPainter>

juego::juego(QWidget *parent) : QWidget(parent), nivelActual(nullptr), numeroNivel(1)
{
    setFixedSize(1280, 720);
    cambiarNivel(1);

    connect(&timer, &QTimer::timeout, this, [=](){
        if (nivelActual){
            nivelActual->actualizar(0.016f);

            //Cambio de nivel
            if(nivelActual->estaTerminado()){
                qDebug()<< "Nivel terminado";

                //if(numeroNivel==1){
                  //  cambiarNivel(2);
                //}
            }
            update();
        }
    }
);
    timer.start(16);
}

juego::~juego(){
    delete nivelActual;
}

void juego::cambiarNivel(int numero){
    if(nivelActual){
        delete nivelActual;
        nivelActual = nullptr;
    }
    numeroNivel = numero;
    if(numero == 1){

        nivelActual = new nivel1();

    } //else if(numero == 2){

        //nivelActual = new nivel2();
    //}
    nivelActual ->iniciar();
}

void juego::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.fillRect(rect(), Qt::cyan);

    if(nivelActual){
        nivelActual->dibujar(painter);
    }
}

void juego::keyPressEvent(QKeyEvent *event){
    if (nivelActual){
        nivelActual->keyPressEvent(event);
    }
}

void juego::keyReleaseEvent(QKeyEvent *event){
    if (nivelActual){
        nivelActual ->keyReleaseEvent(event);
    }
}