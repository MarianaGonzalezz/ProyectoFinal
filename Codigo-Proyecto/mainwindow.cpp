#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "juego.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1280, 720);

    //Creacion del juego dentro del widgetJuego
    miJuego = new juego(ui->widgetJuego);

    miJuego->setGeometry(
        0,
        0,
        1280,
        720
        );

    connect(miJuego, &juego::gameOver, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->pageGameover);
    });

    //Mostrar menu al iniciar
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_JUGAR_clicked()
{
    miJuego ->iniciarJuego();
    ui->stackedWidget->setCurrentWidget(ui->pageJuego);

    miJuego->setFocus();
}

/*
void MainWindow::on_btnReiniciar_clicked()
{
    delete miJuego;

    miJuego = new juego(ui->widgetJuego);

    miJuego->setGeometry(
        0,
        0,
        1280,
        720
        );

    connect(miJuego, &juego::gameOver, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->pageGameover);
    });

    ui->stackedWidget->setCurrentWidget(ui->pageJuego);
    miJuego->setFocus();
}
*/

void MainWindow::on_btnVolver_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_SALIR_clicked(){
    close();
}