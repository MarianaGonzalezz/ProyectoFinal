#include "nivel1.h"
#include <QDebug>

const int nivel1::Tiempo_inicial=60;


nivel1::nivel1()
    : nivel()
    , tiempoRestante(Tiempo_inicial)
    , tiempoAcumulado(0.0f)

{
    timerJuego= new Qtimer(this);
    qDebug() << "nivel 1 creado";
}

nivel1::~nivel1()
{
    for (auto obs : obstaculos) delete obs;
    for (auto moneda : monedas) delete moneda;
    obstaculos.clear();
    monedas.clear();

    qDebug() << "Nivel 1 destruido";
}


void nivel1::iniciar()
{
    qDebug() << "Iniciando Nivel 1";

    terminado = false;
    victoria = false;
    tiempoRestante = Tiempo_inicial;
    tiempoAcumulado = 0.0f;
    monedasRecogidas = 0;

}
