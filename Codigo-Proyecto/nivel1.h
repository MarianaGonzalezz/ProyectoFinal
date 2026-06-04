#ifndef NIVEL1_H
#define NIVEL1_H


#include <QTimer>
#include <QElapsedTimer>
#include <QPoint>
#include <QVector>
#include <vector>

#include <QSoundEffect>////Para audios cortos
#include <QMediaPlayer>
#include <QAudioOutput>

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

    QSoundEffect sonidoGolpe;

    bool esperandoGameOver = false;
    float tiempoDerrota = 0.0f;

    QMediaPlayer* musicaFondo;
    QAudioOutput* salidaAudio;

    // Timer
    QTimer* timerJuego;
    int tiempoRestante;
    float tiempoAcumulado;

    QElapsedTimer cronometroNivel;
    static const qint64 TIEMPO_LICENCIA_MS = 60000;
    bool licenciaYaGenerada;

    static const int Tiempo_inicial=60;

    //elementos de la licencia
    bool licenciaActiva;
    float licenciaX;
    float licenciaY;
    float velocidadLicencia;
    float destinoLicenciaY;
    QPixmap spriteLicencia;
    float progresoLicencia;

    // Metodos privados

    void crearObstaculos();
    void crearMonedas();
    void verificarColisiones();
    void generarObjetoAleatorio();

    //Sacudida de camara
    bool sacudiendoCamara = false;
    float tiempoSacudida = 0.0f;

    int offsetCamaraX = 0;
    int offsetCamaraY = 0;

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
