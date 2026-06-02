#include "nivel2.h"
#include "QDebug"
#include <cstdlib>
#include <ctime>


nivel2::nivel2()
    : calamardo (900, 350, true){
    fondo.load(":/sprites/fondoN2.png");
    fondo = fondo.scaled(
        1280,
        700,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation);
    fondoOffset = 0;
    srand(time(nullptr));
}

nivel2::~nivel2(){
    for (proyectil* p : proyectiles){
        delete p;
    }
    proyectiles.clear();
}

void nivel2::iniciar(){

    bob.cargarSpritesNivel2(":/sprites/correr.png",
                            ":/sprites/saltar5.png",
                            ":/sprites/agacharse.png",
                            ":/sprites/muerte.png"
                            );
    bob.activarAnimacionNivel2(5);

    bob.setPosicion(400,370);

    bob.setAncho(180);
    bob.setAlto(180);

    terminado = false;
    victoria=false;
}

void nivel2::actualizar(float deltaTime){

    bob.actualizar(deltaTime);

    if(bob.muerteTerminada()){

        terminado = true;
        victoria = false;

        return;
    }

    // Si Bob esta muriendo:
    // congelar TODO excepto su animacion
    if(!bob.estaVivo()){
        return;
    }

    // ---------- JUEGO NORMAL ----------

    calamardo.actualizar(deltaTime);

    fondoOffset += 2;

    if(fondoOffset >= fondo.width()){
        fondoOffset = 0;
    }

    proyectil* nuevo = calamardo.lanzarProyectil(
        bob.getX(),
        bob.getY(),
        bob.getVelocidadX()
        );

    if(nuevo){
        proyectiles.push_back(nuevo);
    }

    for(proyectil* p : proyectiles){
        p->actualizar(deltaTime);
    }

    verificarColisiones();
}

void nivel2::dibujar(QPainter &painter){

    painter.drawPixmap(-fondoOffset, 0, fondo);
    painter.drawPixmap(fondo.width() - fondoOffset, 0, fondo);

    bob.dibujar(painter);
    calamardo.dibujar(painter);

    for(proyectil* p : proyectiles){
        p->dibujar(painter);
    }
}

void nivel2::verificarColisiones(){

    for(auto it = proyectiles.begin();
         it != proyectiles.end(); ){

        proyectil* p = *it;

        //Acierto
        if(p->getHitbox().intersects(bob.getHitbox())){
            calamardo.registrarAcierto();

            bob.recibirImpacto();

            delete p;

            it= proyectiles.erase(it);
            continue;
        }
        //Fallo
        if(p->getY() > 720 || p->getX() < -100 || p->getX() > 1280){

            calamardo.registrarFallo();

            delete p;

            it = proyectiles.erase(it);

            continue;
            }

        if(p->getTiempoVida() > 3.0f){
            calamardo.registrarFallo();

            delete p;

            it = proyectiles.erase(it);
            continue;
        }
        ++it;
    }

}

void nivel2::keyPressEvent(QKeyEvent *event){

    if(event->isAutoRepeat())
        return;

    if(event ->key() == Qt::Key_W){
        bob.saltar();
    }
    if(event->key() == Qt::Key_S){
        bob.agacharse();
    }
}

void nivel2::keyReleaseEvent(QKeyEvent *event){

    if(event->isAutoRepeat())
        return;

    if(event->key() == Qt::Key_S){
        bob.setAgachado(false);
    }
}
