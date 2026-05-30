#include "nivel1.h"
#include <QDebug>
#include <cstdlib>

nivel1::nivel1()
    : nivel()
    , tiempoRestante(Tiempo_inicial)
    , tiempoAcumulado(0.0f)
    ,frameActualFondo(0), tiempoAnimacionFondo(0.0f), duracionFrameFondo(0.20f)

{
    timerJuego= new QTimer();
    qDebug() << "nivel 1 creado";

    const QString rutasFrames[] = {
        ":/sprites/sprite_0.png",
        ":/sprites/sprite_1.png",
        ":/sprites/sprite_2.png"
    };

    for(const QString& ruta : rutasFrames){
        QPixmap frame;
        if(frame.load(ruta)){
            framesFondoPrincipal.push_back(frame);
        }
    }
    vistasetY = 0;
    velocidadFondo = 40.0f;

    tiempoSpawn = 0.0f;
    intervaloSpawn = 1.0f;
}

nivel1::~nivel1()
{
    for (auto obs : vectorObstaculos)
    delete obs;
    for (auto moneda : monedas)
    delete moneda;

    vectorObstaculos.clear();
    monedas.clear();

    qDebug() << "Nivel 1 destruido";
}


void nivel1::iniciar()
{

    bob.setSprite(":/sprites/carrito.png");
    bob.setPosicion(550, 400);
    //vectorObstaculos.push_back(new obstaculos(700, 500, 0, "caja"));

    //vectorObstaculos.push_back(new obstaculos(900,500,0,"medusas"));

    //monedas.push_back(new bonus(430,350));

    qDebug() << "Iniciando Nivel 1";

    terminado = false;
    victoria = false;
    tiempoRestante = Tiempo_inicial;
    tiempoAcumulado = 0.0f;
    //monedasRecogidas = 0;

}

void nivel1::verificarColisiones(){
    for(obstaculos* obs: vectorObstaculos){
        if (obs->getHitbox().intersects(bob.getHitbox())){
            obs->aplicarEfecto(bob);
        }
    };
    for (bonus* moneda:monedas){
        if(moneda->estaActivo() &&
            moneda->getHitbox().intersects(bob.getHitbox())){
            tiempoRestante += moneda->aplicarEfecto(bob);
        }
    };
}

void nivel1::actualizar(float deltaTime){

    //Dificultad progresiva
    if (intervaloSpawn > 0.3){
        intervaloSpawn -= 0.0001f;
    }

    tiempoSpawn += deltaTime;

    if (tiempoSpawn >= intervaloSpawn){
        tiempoSpawn = 0.0f;
        generarObjetoAleatorio();
    }

    bob.actualizar(deltaTime);

    //Limites de la carretera

    const float limiteIzquierdo = 120;
    const float limiteDerecho = 1250;
    if(bob.getX() < limiteIzquierdo){
        bob.setPosicion(limiteIzquierdo, bob.getY());
    }

    if(bob.getX()> limiteDerecho - bob.getAncho()){
        bob.setPosicion(limiteDerecho - bob.getAncho(), bob.getY());
    }


    for(obstaculos* obs : vectorObstaculos){
        obs->actualizar(deltaTime);
    }
    for(bonus* moneda : monedas){
        moneda ->actualizar(deltaTime);
    }

    verificarColisiones();
    vistasetY = 0;

    if (!framesFondoPrincipal.isEmpty()){
        tiempoAnimacionFondo += deltaTime;

        if(tiempoAnimacionFondo >= duracionFrameFondo){
            tiempoAnimacionFondo -= duracionFrameFondo;

            frameActualFondo = (frameActualFondo + 1) % framesFondoPrincipal.size();
        }
    }
}

void nivel1::dibujar(QPainter &painter){
    //Fondo
    const QPixmap& fondoEnUso = framesFondoPrincipal.isEmpty() ? fondo
                                                               : framesFondoPrincipal[frameActualFondo];


    painter.drawPixmap(0,0,1280,720,fondoEnUso);

    //Jugador
    bob.dibujar(painter);

    //obstaculos
    for(obstaculos* obs : vectorObstaculos){
        obs -> dibujar(painter);
    };

    //monedas
    for(bonus* moneda: monedas){
        moneda->dibujar(painter);
    };

}

void nivel1::generarObjetoAleatorio(){

    int tipo = rand()%4;
    float x = 350 + (rand() % 500);
    float velocidad = 250.0f;

    switch(tipo){
    case 0: vectorObstaculos.push_back(new obstaculos(x, 160, velocidad, "caja")); break;
    case 1: vectorObstaculos.push_back(new obstaculos(x, 160, velocidad, "bache")); break;
    case 2: vectorObstaculos.push_back(new obstaculos(x, 160, velocidad, "medusas")); break;
    case 3: monedas.push_back(new bonus(x, 200)); break;
    }

}
void nivel1::keyPressEvent(QKeyEvent *event){
    if (event->key()== Qt::Key_A){
        bob.moverIzq();
    }

    if (event->key()== Qt::Key_D){
        bob.moverDer();
    }
}

void nivel1::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_D){
        bob.setVelocidadX(0);
        bob.mirarFrente();
    }
}
