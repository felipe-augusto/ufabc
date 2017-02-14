#include "mainwindow.h"
#include "ui_mainwindow.h"

//Construtor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria uma superficie de video
    VideoSurface *videoSurface = new VideoSurface;

    //Cria um media player e associa a saida com a superficie de video
    player = new QMediaPlayer(this);
    player->setVideoOutput(videoSurface);

    //Definição dos signals/slots
    QObject::connect(this, SIGNAL(signalSendImage(QImage *)),ui->openGLWidget,SLOT(setImage(QImage *)));
    QObject::connect(videoSurface, SIGNAL(signalSendImage(QImage *)),ui->openGLWidget,SLOT(setImage(QImage *)));

}

//Destrutor
MainWindow::~MainWindow()
{
    delete ui;
}

//Menu Open Image
void MainWindow::openImage(){
    QString imagePath = QFileDialog::getOpenFileName(  this,  tr("Open Image File"),
                                                       "",  tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ) );
    if(!imagePath.isEmpty()){
        emit signalSendImage(new QImage(imagePath));
    }
}

//Menu Open Video
void MainWindow::openVideo(){
    QString videoPath = QFileDialog::getOpenFileName(  this,  tr("Open Video File"),
                                                       "",  tr("MPEG4 (*.mp4);;AVI (*.avi)" ) );
    if(!videoPath.isEmpty()){
        player->setMedia(QUrl::fromLocalFile(videoPath));
        player->play();
    }
}
