#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "juego.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sonidoGameOver.setSource(
        QUrl("qrc:/sonidos/aTarde.wav"));

    //Sonido de fondo en el menu
    audioMenu = new QAudioOutput (this);
    musicaMenu = new QMediaPlayer (this);

    musicaMenu->setAudioOutput(audioMenu);
    audioMenu->setVolume(0.5);

    musicaMenu->setSource(QUrl("qrc:/sonidos/menu.mp3"));

    musicaMenu->play();

    connect(musicaMenu, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus status)
            {
                if(status == QMediaPlayer::EndOfMedia)
                {
                    musicaMenu->setPosition(0);
                    musicaMenu->play();
                }
            });

    //Tamaño de la ventana
    setFixedSize(1280, 720);

    //Creacion del juego dentro del widgetJuego
    miJuego = new juego(ui->widgetJuego);

    miJuego->setGeometry(
        0,
        0,
        1280,
        720
        );


    //Coneccion de los botones
    connect(miJuego, &juego::gameOver, this, [this](){

        sonidoGameOver.play();

        ui->stackedWidget->setCurrentWidget(ui->pageGameover);
    });

    connect(miJuego, &juego::mostrarTransicion, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->pageTransicion);
    });

    connect(miJuego, &juego::victoriaFinal, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->pageVictoria);
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
    musicaMenu->stop();

    miJuego ->iniciarJuego();
    ui->stackedWidget->setCurrentWidget(ui->pageJuego);

    miJuego->setFocus();
}


void MainWindow::on_btnReiniciar_clicked()
{
    qDebug() << "CLICK REINICIAR";
    qDebug() << "Nivel actual:" << miJuego->getNumeroNivel();


    if(miJuego->getNumeroNivel() == 2){

        qDebug() << "Mostrando transicion";

        ui->stackedWidget->setCurrentWidget(ui->pageTransicion);

    } else {

        qDebug() << "Reiniciando nivel";
        miJuego -> reinciarNivelActual();

        ui->stackedWidget->setCurrentWidget(ui->pageJuego);
        miJuego->setFocus();
    }
}

void MainWindow::on_btnVolver_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_SALIR_clicked(){
    close();
}
void MainWindow::on_SALIR2_clicked(){
    close();
}

void MainWindow::on_btnFacil_clicked()
{
    miJuego->setDificultadNivel2(1);

    miJuego->cambiarNivel(2);

    ui->stackedWidget->setCurrentWidget(ui->pageJuego);

    miJuego->setFocus();
}

void MainWindow::on_btnDificil_clicked()
{
    miJuego->setDificultadNivel2(2);

    miJuego->cambiarNivel(2);

    ui->stackedWidget->setCurrentWidget(ui->pageJuego);

    miJuego->setFocus();
}
void MainWindow::on_btnHISTORIA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageHistoria);
}
void MainWindow::on_btnVolver2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}
void MainWindow::on_btnVolver3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}