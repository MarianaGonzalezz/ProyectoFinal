#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QTimer>

#include "nivel.h"
#include "nivel1.h"
#include "nivel2.h"

class juego : public QWidget
{
    Q_OBJECT

private:
    nivel* nivelActual;
    QTimer timer;
    int numeroNivel;
    int dificultadNivel2;

signals:
    void gameOver();
    void mostrarTransicion();
    void victoriaFinal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public:
    explicit juego(QWidget *parent = nullptr);
    ~juego();

    bool estaTerminado() const;

    void iniciarJuego();

    void reinciarNivelActual();

    void cambiarNivel(int numero);

    void setDificultadNivel2(int dificultad);

    int getNumeroNivel() const;
};

#endif // JUEGO_H