#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
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

signals:
    void gameOver();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public:
    explicit juego(QWidget *parent = nullptr);
    ~juego();

    bool estaTerminado() const;

    void iniciarJuego();
};

#endif // JUEGO_H