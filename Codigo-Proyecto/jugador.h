#ifndef JUGADOR_H
#define JUGADOR_H

#include <Qpainter>
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

    QPixmap sprite;

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

    // Setters ( para que ambos niveles puedan modificar)

    void setPosicion(float nx, float ny);
    void setVelocidadX(float vx);
    void setVelocidadY(float vy);
    void setVivo(bool estado);
    void setEnSuelo(bool estado);
    void setAgachado(bool estado);
    void setAlto(float nuevoAlto);
    void setSprite(const QString& ruta);         // Para cambiar el sprite
    void resetear();

};

#endif // JUGADOR_H