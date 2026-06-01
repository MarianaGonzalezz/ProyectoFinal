#include "jugador.h"
#include <QDebug>

const float Velocidad_movimiento=400.0f;
const float Fuerza_salto=600.0f;
const float Ancho_normal=260.0f;
const float Alto_normal=260.0f;
const float Alto_agachado=30.0f;

// Constructores

jugador::jugador()
    : x(0.0f)
    , y(0.0f)
    , velocidadX(0.0f)
    , velocidadY(0.0f)
    , enSuelo(true)
    , agachado(false)
    , ancho(Ancho_normal)
    , alto(Alto_normal)
    , vivo(true), direccionActual(FRENTE)
{}

jugador::jugador(float xInicial, float yInicial)
    : x(xInicial)
    , y(yInicial)
    , velocidadX(0.0f)
    , velocidadY(0.0f)
    , enSuelo(true)
    , agachado(false)
    , ancho(Ancho_normal)
    , alto(Alto_normal)
    , vivo(true), direccionActual(FRENTE)
{}

// Destructor

jugador::~jugador(){
    qDebug() << "jugador destruido";
}


// Metodos

void jugador::moverIzq(){
    direccionActual = IZQUIERDA;
    velocidadX=-Velocidad_movimiento;
}

void jugador::moverDer(){
    direccionActual = DERECHA;
    velocidadX=Velocidad_movimiento;
}

void jugador::mirarFrente(){
    direccionActual = FRENTE;
}
void jugador::saltar(){
    if(enSuelo && !agachado && vivo){
        velocidadY=-Fuerza_salto;
        enSuelo=false;
        qDebug() << "bob esponja salta!";
    }
}

void jugador::agacharse(){
    if(enSuelo && !agachado && vivo){
        agachado=true;
        alto=Alto_agachado;
        qDebug() << "Bob Esponja se agacha";
    }
}


void jugador::actualizar(float deltaTime){
    if (!vivo) return;

    // Actualizar posición según velocidad
    x += velocidadX * deltaTime;
    y += velocidadY * deltaTime;
}

void jugador::dibujar(QPainter& painter){

    if(!vivo) return;

    int frameWidth = sprite.width() / 3;
    int frameHeight = sprite.height();

    int frameX =0;

    switch(direccionActual){
    case FRENTE: frameX = 0; break;
    case DERECHA: frameX = frameWidth; break;
    case IZQUIERDA: frameX = frameWidth * 2; break;
    }

    QRect frameActual(frameX, 0, frameWidth, frameHeight);

    painter.drawPixmap(QRectF (x, y, ancho, alto),
                       sprite, frameActual);
}

// Getters

float jugador::getX() const { return x; }
float jugador::getY() const { return y; }
float jugador::getVelocidadX() const { return velocidadX; }
float jugador::getVelocidadY() const { return velocidadY; }

QRectF jugador::getHitbox() const{
    return QRectF(x+20, y+20, 100, 100);
}

bool jugador::estaVivo() const { return vivo; }
bool jugador::estaEnSuelo() const { return enSuelo; }
bool jugador::estaAgachado() const { return agachado; }
float jugador::getAncho() const { return ancho; }
float jugador::getAlto() const { return alto; }

// Setters


void jugador::setPosicion(float nx, float ny){
    x=nx;
    y=ny;
}

void jugador::setVelocidadX(float vx) {
    velocidadX = vx;
}

void jugador::setVelocidadY(float vy) {
    velocidadY = vy;
}

void jugador::setVivo(bool estado){
    vivo=estado;
    if(!vivo){
        qDebug() << "GAME OVER - Bob Esponja ha muerto";
    }
}

void jugador::setEnSuelo(bool estado){
    enSuelo=estado;
}

void jugador::setAgachado(bool estado) {
    agachado = estado;
    if (!agachado) {
        alto = Alto_normal;
    }
}

void jugador::setAlto(float nuevoAlto) {
    alto = nuevoAlto;
}

void jugador::setSprite(const QString& ruta) {
    if (!sprite.load(ruta)) {
        qDebug() << "Error: No se pudo cargar el sprite desde" << ruta;
    } else{
            qDebug() << "Sprite cargado correctamente";
            qDebug() << "Ancho:" << sprite.width();
            qDebug() << "Alto:" << sprite.height();
    }
}


void jugador::resetear() {
    x = 0.0f;
    y = 0.0f;
    velocidadX = 0.0f;
    velocidadY = 0.0f;
    enSuelo = true;
    agachado = false;
    ancho = Ancho_normal;
    alto = Alto_normal;
    vivo = true;
    qDebug() << "Jugador reseteado";
}
