#ifndef NIVEL1_H
#define NIVEL1_H


#include <QTimer>
#include <QPoint>
#include <QVector>
#include <vector>

#include "nivel.h"
#include "jugador.h"
#include "obstaculos.h"
#include "bonus.h"



class nivel1 : public nivel
{
private:

    // Elementos del nivel

    std::vector<obstaculos*> vectorObstaculos;
    std::vector<bonus*> monedas;

    // Timer
    QTimer* timerJuego;
    int tiempoRestante;
    float tiempoAcumulado;

    static const int Tiempo_inicial=60;

    // Metodos privados

    void crearObstaculos();
    void crearMonedas();
    void verificarColisiones();
    void generarObjetoAleatorio();

public:
    nivel1();
    ~nivel1();

    void iniciar() override;
    void actualizar(float deltaTime) override;
    void dibujar(QPainter& painter) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    QPixmap fondo;
    float vistasetY;
    float velocidadFondo;

    QVector<QPixmap> framesFondoPrincipal;
    QVector<QPixmap> offsetsFramesFondoPrincipal;

    int frameActualFondo;
    float tiempoAnimacionFondo;
    float duracionFrameFondo;

    float tiempoSpawn;
    float intervaloSpawn;
};

#endif // NIVEL1_H
