#ifndef NIVEL2_H
#define NIVEL2_H

#include <vector>
using namespace std;

#include "nivel.h"
#include "enemigo.h"
#include "proyectil.h"

class nivel2 : public nivel
{
private:

    enemigo calamardo;
    vector<proyectil*> proyectiles;
    float tiempoDisparo;
    float intervaloDisparo;
    float dificultad;
    void lanzarCangreburger();
    void verificarColisiones();
    void aumentarDificultad();

public:
    nivel2();
    ~nivel2();

    void iniciar() override;
    void actualizar(float deltaTime) override;
    void dibujar(QPainter &painter) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};

#endif // NIVEL2_H
