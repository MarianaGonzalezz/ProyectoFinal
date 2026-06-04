#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMediaPlayer>////Para audios largos
#include <QAudioOutput>////Para audios largos

#include <QSoundEffect>////Para efectos cortos

#include "juego.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_JUGAR_clicked();
    void on_btnReiniciar_clicked();
    void on_btnVolver_clicked();
    void on_SALIR_clicked();
    void on_SALIR2_clicked();
    void on_btnFacil_clicked();
    void on_btnDificil_clicked();

    void on_btnHISTORIA_clicked();
    void on_btnVolver2_clicked();
    void on_btnVolver3_clicked();
private:
    Ui::MainWindow *ui;
    juego* miJuego;

    QMediaPlayer* musicaMenu;
    QAudioOutput* audioMenu;
    QSoundEffect sonidoGameOver;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

};
#endif // MAINWINDOW_H
