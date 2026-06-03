#ifndef JUGADOR_H
#define JUGADOR_H

#include <QPainter>
#include <QPixmap>
#include <QRectF>


class jugador{
private:
    float x,y;
    float velocidadX, velocidadY;

    // Estado interno

    bool enSuelo;
    bool agachado;
    float ancho,alto;
    bool vivo;


    //Animacion nivel2
    QPixmap spriteCorrer;
    QPixmap spriteSaltar;
    QPixmap spriteAgachar;
    QPixmap spriteMuerte;

    enum estadoAnimacion{
        CORRIENDO,
        SALTANDO,
        AGACHADO,
        MUERTO
    };
    estadoAnimacion estadoActual;

    bool animacionNivel2;

    int frameActual;
    int totalFrames;

    float tiempoAnimacion;
    float velocidadAnimacion;

    bool soltandoAgachado;
    bool animacionMuerteTerminada;

    //Animacion nivel1

    QPixmap sprite;
    enum Direccion{
        FRENTE, DERECHA, IZQUIERDA
    };
    Direccion direccionActual;

public:

    jugador();
    jugador(float xInicial, float yInicial);
    ~jugador();

    // Metodos

    void moverIzq();
    void moverDer();
    void saltar();
    void agacharse();
    void actualizar(float deltaTime);
    void dibujar(QPainter& painter);

    void mirarFrente();
    void activarAnimacionNivel2(int frames);
    void cargarSpritesNivel2(
        const QString& correr,
        const QString& saltar,
        const QString& agachar,
        const QString& muerte);

    // Getters

    float getX() const;
    float getY() const;
    float getVelocidadX() const;
    float getVelocidadY() const;
    QRectF getHitbox() const;
    bool estaVivo() const;
    bool estaEnSuelo() const;
    bool estaAgachado() const;
    float getAncho() const;
    float getAlto() const;
    int getImpactos() const;
    void recibirImpacto();
    bool muerteTerminada() const;

    // Setters ( para que ambos niveles puedan modificar)

    void setPosicion(float nx, float ny);
    void setVelocidadX(float vx);
    void setVelocidadY(float vy);
    void setVivo(bool estado);
    void setEnSuelo(bool estado);
    void setAgachado(bool estado);
    void setAlto(float nuevoAlto);
    void setAncho(float nuevoAncho);
    void setSprite(const QString& ruta);         // Para cambiar el sprite
    void resetear();

};

#endif // JUGADOR_H