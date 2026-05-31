#include "enemigo.h"
#include "QDebug"
#include <cstdlib>
#include <cmath>
#include <ctime>

enemigo::enemigo(float x, float y, bool esDificil)
    : x(x)
    , y(y)
    , dificil(esDificil)
    , tiempoDisparo(0)
    , aciertos(0)
    , fallos(0)
    , precisionActual(0)
{
    /*
    if (!sprite.load(":/sprites/calamardo.png")) {
        sprite = QPixmap(50, 50);
        sprite.fill(Qt::cyan);
    }
    */

    if (dificil) {
        intervaloDisparo = 1.2f;
        velocidadProyectil = 450.0f;
        precisionActual = 0.85f;
    } else {
        intervaloDisparo = 2.5f;
        velocidadProyectil = 300.0f;
        precisionActual = 0.50f;
    }

    // iniciar semilla

    static bool semillaInicializada=false;
    if (!semillaInicializada) {
        srand(time(nullptr));
        semillaInicializada=true;
    }

}

enemigo::~enemigo()
{
    qDebug() << "Calamardo - Aciertos:" << aciertos << "Fallos:" << fallos;
}

void enemigo::actualizar(float deltaTime)
{
    tiempoDisparo += deltaTime;
}

void enemigo::dibujar(QPainter& painter)
{
    painter.drawPixmap(int(x), int(y), sprite);
}

proyectil* enemigo::lanzarProyectil(float jugadorX, float jugadorY, float jugadorVelX)
{
    if(tiempoDisparo<intervaloDisparo){
        return nullptr;
    }

    tiempoDisparo=0;

    float dx = jugadorX - x;
    float dy = jugadorY - y;
    float velX, velY;

    if(!dificil){
        //  Modo facil, angulo aleatorio

        int anguloAleatorio= (rand() % 120)-60;

        float imprecisionX = (rand() % 200) - 100;
        float dxFinal = dx + imprecisionX;

        if (dxFinal > 250) dxFinal = 250;
        if (dxFinal < -250) dxFinal = -250;

        velX = dxFinal * 2.0f;
        velY = -150.0f + (rand() % 100);

        if(jugadorY<400){
            velY= -250.0f + (rand()%80);
        }

    }else{
        // Modo dificil

        float precisionUsar=precisionActual;

        if(aciertos>fallos+5){
            precisionUsar=precisionActual+0.08f;
            if(precisionUsar>0.98f)precisionUsar=0.98f;
        }

        if(fallos>aciertos+8){
            precisionUsar=precisionUsar-0.05f;
            if (precisionUsar < 0.70f) precisionUsar = 0.70f;
        }

        // Prediccion: calcular donde estara Bob

        float tiempoVuelo= sqrt(dx * dx + dy * dy) / velocidadProyectil;
        float prediccionX = jugadorX + (jugadorVelX * tiempoVuelo);
        float dxPredicho = prediccionX - x;

        // Imprecision

        int rango=(1.0f-precisionUsar)*80;
        int imprecision = (rand() % (rango * 2)) - rango;
        float dxFinal = dxPredicho + imprecision;

        if(dxFinal>350)dxFinal=350;
        if(dxFinal<-350)dxFinal=-350;

        velX=dxFinal*2.8f;

        if(jugadorY<400){
            velY=-300.0f;
        }else{
            velY=-200.0f;
        }
    }

    return new proyectil(x + 25, y+25, velX, velY);
}

// Aprendizaje


void enemigo::registrarAcierto(){

    if(dificil){
        aciertos++;
        precisionActual=precisionActual+0.02f;
        if (precisionActual > 0.98f) precisionActual = 0.98f;
        qDebug() << "Acierto! Precisión:" << int(precisionActual * 100) << "%";
    }
}

void enemigo::registrarFallo(){
    if (dificil) {
        fallos++;
        if (fallos > aciertos + 5) {
            precisionActual = precisionActual - 0.02f;
            if (precisionActual < 0.70f) precisionActual = 0.70f;
            qDebug() << "Fallo. Precisión:" << int(precisionActual * 100) << "%";
        }
    }
}

// Getters

float enemigo::getX() const{
    return x;
}

float enemigo::getY() const{
    return y;
}

QRectF enemigo::getHitbox() const
{
    return QRectF(x, y, 50, 50);
}




