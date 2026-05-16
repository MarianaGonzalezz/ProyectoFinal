#include "nivel2.h"
#include "QDebug"
#include <cstdlib>
#include <ctime>


nivel2::nivel2()
    : calamardo (1000, 300),
    tiempoDisparo(0),
    intervaloDisparo(2.0f),
    dificultad(1.0f)
{
    srand(time(nullptr));
}

nivel2::~nivel2(){
    for (proyectil* p : proyectiles){
        delete p;
    }
    proyectiles.clear();
}

void nivel2::iniciar(){
    bob.setPosicion(100,500);

    terminado = false;
    victoria=false;
}

void nivel2::actualizar(float deltaTime){

    //Movimiento automatico
    bob.setVelocidadX(300);

    bob.actualizar(deltaTime);

    tiempoDisparo += deltaTime;

    if(tiempoDisparo >= intervaloDisparo){
        lanzarCangreburger();
        tiempoDisparo =0;
    }
    for (proyectil* p : proyectiles){
        p->actualizar(deltaTime);
    }
    verificarColisiones();
    aumentarDificultad();
}

void nivel2::dibujar(QPainter &painter){
    bob.dibujar(painter);
    calamardo.dibujar(painter);

    for(proyectil* p : proyectiles){
        p->dibujar(painter);
    }
}

void nivel2::lanzarCangreburger(){
    float objetivoY = bob.getY();
    float error = (rand() % 100) - 50;
    objetivoY += error/dificultad;

    float velocidadY = (objetivoY - calamardo.getY()) * 2;
    proyectiles.push_back(

        new proyectil(
            calamardo.getX(),
            calamardo.getY(),
            -500,
            velocidadY
            )
        );
    qDebug()<<"cangreburger lanzada";
}

void nivel2::verificarColisiones(){
    for (proyectil* p : proyectiles){

        if(p->getHitbox().intersects(
                bob.getHitbox()))
        {
            bob.setVivo(false);
            terminado = true;
            victoria = false;
        }
    }
}

void nivel2::aumentarDificultad(){
    dificultad += 0.001f;
    intervaloDisparo = 2.0f/dificultad;
    if (intervaloDisparo< 0.4f){
        intervaloDisparo = 0.4f;
    }
}

void nivel2::keyPressEvent(QKeyEvent *event){
    if(event ->key() == Qt::Key_W){
        bob.saltar();
    }
    if(event->key() == Qt::Key_S){
        bob.agacharse();
    }
}

void nivel2::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_S){
        bob.setAgachado(false);
    }
}