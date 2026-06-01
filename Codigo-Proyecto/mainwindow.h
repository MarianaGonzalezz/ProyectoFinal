#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "juego.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_JUGAR_clicked();
    void on_btnReiniciar_clicked();
    void on_btnVolver_clicked();
    void on_SALIR_clicked();

private:
    Ui::MainWindow *ui;
    juego* miJuego;
};
#endif // MAINWINDOW_H
