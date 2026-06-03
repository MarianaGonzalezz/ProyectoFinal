#include "jugador.h"
#include <QDebug>

const float Velocidad_movimiento=400.0f;
const float Fuerza_salto=600.0f;
const float Ancho_normal=260.0f;
const float Alto_normal=260.0f;
const float Alto_agachado=30.0f;

const float gravedad = 1200.0f;
const float suelo = 370;

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
{
    animacionNivel2 = false;

    frameActual = 0;
    totalFrames = 1;

    tiempoAnimacion = 0;
    velocidadAnimacion = 0.1f;

    soltandoAgachado = false;

    //impactos = 0;
    animacionMuerteTerminada = false;
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
    , vivo(true), direccionActual(FRENTE)
{
    animacionNivel2 = false;

    frameActual = 0;
    totalFrames = 1;

    tiempoAnimacion = 0;
    velocidadAnimacion = 0.1f;

    soltandoAgachado = false;

    //impactos = 0;
    animacionMuerteTerminada = false;
}

// Destructor

jugador::~jugador(){
    qDebug() << "jugador destruido";
}

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

        if(animacionNivel2){
            estadoActual = SALTANDO;
        }
        qDebug() << "bob esponja salta!";
    }
}

void jugador::agacharse(){

    if(enSuelo && !agachado && vivo){

        agachado=true;
        //alto = 140;

        if(animacionNivel2){
            estadoActual = AGACHADO;
            frameActual = 0;
            soltandoAgachado = false;

            qDebug() << "Estado AGACHADO";
        }

        qDebug() << "Bob Esponja se agacha";
    }
}


void jugador::actualizar(float deltaTime){

    // Actualizar posición según velocidad
    x += velocidadX * deltaTime;
    y += velocidadY * deltaTime;

    velocidadY += gravedad * deltaTime; //Agg gravedad para que vuelva al suelo

    if(y >= suelo){
        y = suelo;
        velocidadY = 0;
        enSuelo = true;

        if(animacionNivel2 && !agachado && estadoActual != MUERTO){
            estadoActual = CORRIENDO;
        }
    }

    if(animacionNivel2)
    {
        // ANIMACION DE MUERTE
        if(estadoActual == MUERTO){

            if(animacionMuerteTerminada){
                return;
            }

            tiempoAnimacion += deltaTime;

            if(tiempoAnimacion >= velocidadAnimacion){

                tiempoAnimacion = 0;

                frameActual++;

                if(frameActual >= totalFrames){

                    frameActual = totalFrames - 1;

                    animacionMuerteTerminada = true;

                    vivo = false;

                    qDebug() << "Animacion muerte terminada";
                }
            }

            return;
        }
        // ANIMACIONES NORMALES
        tiempoAnimacion += deltaTime;

        if(tiempoAnimacion >= velocidadAnimacion)
        {
            tiempoAnimacion = 0;

            if(estadoActual == AGACHADO)
            {
                if(!soltandoAgachado)
                {
                    if(frameActual < 2)
                    {
                        frameActual++;
                    }
                }
                else
                {
                    if(frameActual < 4)
                    {
                        frameActual++;
                    }
                    else
                    {
                        estadoActual = CORRIENDO;
                        frameActual = 0;
                        soltandoAgachado = false;
                    }
                }
            }
            else
            {
                frameActual++;

                if(frameActual >= totalFrames)
                {
                    frameActual = 0;
                }
            }
        }
    }
}

void jugador::dibujar(QPainter& painter){

    //Animacion n2

    if(animacionNivel2){

        QPixmap* spriteActual;

        switch(estadoActual){
        case CORRIENDO:spriteActual = &spriteCorrer; break;
        case SALTANDO: spriteActual = &spriteSaltar; break;
        case AGACHADO: spriteActual = &spriteAgachar; break;
        case MUERTO: spriteActual = &spriteMuerte; break;
        }

        int frameWidth = spriteActual->width() / 5;
        int frameHeight = spriteActual->height();

        QRect origen (frameActual*frameWidth, 0, frameWidth, frameHeight);

        painter.drawPixmap(QRectF (x, y, ancho, alto),
                           *spriteActual, origen);

        //VISTA DEL HITBOX
        //painter.setPen(Qt::red);
        //painter.drawRect(getHitbox());

        return;
    }

    //Animacion n1

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

bool jugador::muerteTerminada() const{
    return animacionMuerteTerminada;
}

//int jugador::getImpactos() const{
  //  return impactos;
//}

QRectF jugador::getHitbox() const{

    //HB Agachado
    if(agachado){ return QRectF(x+40, y+100, 100, 50);}

    //HB Saltando
    else if(!enSuelo){ return QRectF(x+50, y+70, 70, 40);}

    return QRectF(x+50, y+50, 70, 125);
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

    if (!estado && agachado) {
        if(animacionNivel2){
            soltandoAgachado = true;
        }
        agachado = estado;
    }
}

void jugador::setAlto(float nuevoAlto) {
    alto = nuevoAlto;

    if(animacionNivel2 && enSuelo)
    {
        estadoActual = CORRIENDO;
    }
}
void jugador::setAncho(float nuevoAncho){
    ancho = nuevoAncho;
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

void jugador::activarAnimacionNivel2(int frames){
    animacionNivel2 = true;
    totalFrames = frames;

    frameActual = 0;
    tiempoAnimacion = 0;
}

void jugador::cargarSpritesNivel2(const QString &correr, const QString &saltar,
                                  const QString &agachar, const QString &muerte)
{
    spriteCorrer.load(correr);
    spriteSaltar.load(saltar);
    spriteAgachar.load(agachar);
    spriteMuerte.load(muerte);

    estadoActual = CORRIENDO;

}

void jugador::recibirImpacto(){

        estadoActual = MUERTO;

        frameActual = 0;

        tiempoAnimacion = 0;

        velocidadAnimacion = 0.40f;

        totalFrames = 5;

        vivo = false;

        animacionMuerteTerminada = false;

        qDebug() << "Animacion muerte";
}