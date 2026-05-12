#include "jugador.h"
#include <QDebug>

const float Velocidad_movimiento=400.0f;
const float Fuerza_salto=600.0f;
const float Ancho_normal=50.0f;
const float Alto_normal=50.0f;
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
    , vivo(true)
{
    // Cargar el sprite de bob esponja
    if (!sprite.load(":/sprites/bob_esponja.png")) {
        qDebug() << "Error: No se pudo cargar la imagen de Bob Esponja";
    }
    qDebug() << "Jugador creado en posición (0, 0)";
}

jugador::jugador(float xInicial, float yInicial)
    : x(xInicial)
    , y(yInicial)
    , velocidadX(0.0f)
    , velocidadY(0.0f)
    , enSuelo(true)
    , agachado(false)
    , ancho(Ancho_normal)
    , alto(Alto_normal)
    , vivo(true)
{
    // Cargar el sprite de bob esponja
    if (!sprite.load(":/sprites/bob_esponja.png")) {
        qDebug() << "Error: No se pudo cargar la imagen de Bob Esponja";
    }
    qDebug() << "Jugador creado en posición (" << x << "," << y << ")";
}

// Destructor

jugador::~jugador(){
    qDebug() << "jugador destruido";
}


// Metodos

void jugador::moverIzq(){
    velocidadX=-Velocidad_movimiento;
}

void jugador::moverDer(){
    velocidadX=Velocidad_movimiento;
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
    if(vivo){
        painter.drawPixmap(static_cast<int>(x), static_cast<int>(y), sprite);
    }
}

// Getters

float jugador::getX() const { return x; }
float jugador::getY() const { return y; }
float jugador::getVelocidadX() const { return velocidadX; }
float jugador::getVelocidadY() const { return velocidadY; }

QRectF jugador::getHitbox() const{
    return QRectF(x, y, ancho, alto);
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













