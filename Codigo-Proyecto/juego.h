#ifndef JUEGO_H
#define JUEGO_H

#include <Qwidget>
#include <QTimer>

#include "nivel.h"
#include "nivel1.h"
//#include "nivel2.h"

class juego : public QWidget
{
    Q_OBJECT

private:
    nivel* nivelActual;
    QTimer timer;
    int numeroNivel;

    void cambiarNivel(int numero);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public:
    juego(QWidget *parent = nullptr);
    ~juego();
    enum estadoJuego{INICIO, JUGANDO, GAMEOVER};

};

#endif // JUEGO_H
