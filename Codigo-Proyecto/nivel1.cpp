#include "nivel1.h"
#include <QDebug>
#include <cstdlib>

nivel1::nivel1()
    : nivel()
    , tiempoRestante(Tiempo_inicial)
    , tiempoAcumulado(0.0f)
    ,frameActualFondo(0), tiempoAnimacionFondo(0.0f), duracionFrameFondo(0.20f)
    , licenciaYaGenerada(false)
{

    sonidoGolpe.setSource(QUrl("qrc:/sonidos/choque.wav"));
    sonidoGolpe.setVolume(0.8);

    musicaFondo = new QMediaPlayer;
    salidaAudio = new QAudioOutput;

    musicaFondo->setAudioOutput(salidaAudio);

    musicaFondo->setSource(QUrl("qrc:/sonidos/nivel1.mp3"));

    salidaAudio->setVolume(0.5);

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

    licenciaActiva = false;
    spriteLicencia.load(":/sprites/licencia.png");
}

nivel1::~nivel1()
{
    delete musicaFondo;
    delete salidaAudio;
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

    musicaFondo->play();

    bob.setSprite(":/sprites/carrito.png");
    bob.setPosicion(550, 400);

    qDebug() << "Iniciando Nivel 1";

    esperandoGameOver = false;
    tiempoDerrota = 0.0f;

    terminado = false;
    victoria = false;
    tiempoRestante = Tiempo_inicial;
    tiempoAcumulado = 0.0f;
    //monedasRecogidas = 0;
    licenciaActiva = false;
    licenciaYaGenerada=false;
    cronometroNivel.start();
    progresoLicencia = 0.0f;

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
            progresoLicencia += 5000;
        }
    };

    if(licenciaActiva){
        QRectF hitboxLicencia(licenciaX, licenciaY, 80, 80);

        if(hitboxLicencia.intersects(bob.getHitbox())){

            musicaFondo->stop();

            licenciaActiva = false;
            terminado = true;
            victoria = true;

            qDebug() << "Licencia Recogida";
        }
    }
}

void nivel1::actualizar(float deltaTime){

    //Dificultad progresiva
    if (intervaloSpawn > 0.3){
        intervaloSpawn -= 0.0001f;
    }


    if(!licenciaYaGenerada){
        tiempoSpawn += deltaTime;

        if (tiempoSpawn >= intervaloSpawn){
            tiempoSpawn = 0.0f;
            generarObjetoAleatorio();
        }
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

    progresoLicencia += deltaTime * 1000;

    if(licenciaActiva && licenciaY < destinoLicenciaY){
        licenciaY += velocidadLicencia * deltaTime;
        if(licenciaY > destinoLicenciaY){
            licenciaY = destinoLicenciaY;
        }
    }

    if (!licenciaYaGenerada &&
        progresoLicencia >= TIEMPO_LICENCIA_MS)
    {
        licenciaYaGenerada = true;

        licenciaActiva = true;
        licenciaX= 600;
        licenciaY = 100;
        destinoLicenciaY = 350;
        velocidadLicencia = 100;

        //Eliminar obstaculos
        for(obstaculos* obs : vectorObstaculos){ delete obs; }
        vectorObstaculos.clear();

        //Eliminar monedas
        for(bonus* moneda : monedas){delete moneda;}
        monedas.clear();

        qDebug()<<"LicenciaGenerada";

    }

    verificarColisiones();

    if(!bob.estaVivo() && !esperandoGameOver){

        musicaFondo->stop();

        sonidoGolpe.stop();
        sonidoGolpe.play();

        sacudiendoCamara = true;
        tiempoSacudida = 0.0f;

        esperandoGameOver = true;
        tiempoDerrota = 0.0f;

    }

    if(esperandoGameOver){
        tiempoDerrota += deltaTime;

        if(sacudiendoCamara){
            tiempoSacudida += deltaTime;

            offsetCamaraX = (rand()%21)-10;
            offsetCamaraY = (rand()%21)-10;

            if(tiempoSacudida >= 0.3f){
                sacudiendoCamara = false;

                offsetCamaraX = 0;
                offsetCamaraY = 0;
            }
        }

        if(tiempoDerrota >= 0.8f){

            sonidoGolpe.stop();
            terminado = true;
            victoria= false;
        }
        return;
    }

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

    painter.save();
    painter.translate(offsetCamaraX,offsetCamaraY);


    //Fondo
    const QPixmap& fondoEnUso = framesFondoPrincipal.isEmpty() ? fondo
                                                               : framesFondoPrincipal[frameActualFondo];


    painter.drawPixmap(0,0,1280,720,fondoEnUso);

    /////// BARRA DE LICENCIA ///////

    float progreso = progresoLicencia /TIEMPO_LICENCIA_MS;
    if(progreso > 1.0f){
        progreso = 1.0f;
    }
    //FondoBarra
    painter.setBrush(Qt::gray);
    painter.drawRect(20,20,300,25);

    //ParteLlena
    painter.setBrush(Qt::green);
    painter.drawRect(20,20,int(300*progreso),25);

    //Texto
    painter.setPen(Qt::white);
    painter.drawText(20, 70, QString("Licencia en: %1 s ").arg(int(progreso*100)));



    ////Jugador
    bob.dibujar(painter);

    //obstaculos
    for(obstaculos* obs : vectorObstaculos){
        obs -> dibujar(painter);
    };

    //monedas
    for(bonus* moneda: monedas){
        moneda->dibujar(painter);
    };

    //licencia
    if(licenciaActiva){
        painter.drawPixmap(licenciaX,licenciaY, 120, 120,spriteLicencia);
    }

    painter.restore();

}

void nivel1::generarObjetoAleatorio(){

    int tipo = rand()%8;
    float x = 350 + (rand() % 500);
    float velocidad = 250.0f;

    switch(tipo){
    case 0: vectorObstaculos.push_back(new obstaculos(x, 160, velocidad, "caja")); break;
    case 1:
    case 2:
    case 3:
        vectorObstaculos.push_back(new obstaculos(x, 160, velocidad, "bache")); break;
    case 4:
    case 5:
    case 6:
    vectorObstaculos.push_back(new obstaculos(x, 160, velocidad, "medusas")); break;

    case 7: monedas.push_back(new bonus(x, 200)); break;
    }

}
void nivel1::keyPressEvent(QKeyEvent *event){

    qDebug() << "Tecla:" << event->key();

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
