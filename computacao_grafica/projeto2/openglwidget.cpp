#include <QTimer>
#include <QtMath>
#include "openglwidget.h"
#include <math.h>

OpenGLWidget::OpenGLWidget(QWidget *parent): QOpenGLWidget (parent)
{
    scene = NULL;
    timerx = new QTimer(this->parent());
    timery = new QTimer(this->parent());
    timerz = new QTimer(this->parent());
    this->grabKeyboard();
    this->setFocusPolicy(Qt::TabFocus);
    //timer->setInterval(30);
    //timer->setSingleShot(false);

}



OpenGLWidget::~ OpenGLWidget(){
    if(scene){
        delete scene;
        scene = NULL;
    }
}

void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    std::cerr<<"Version"<<glGetString(GL_VERSION)<<"\n";
    std::cerr<<"GLSL"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<"\n";
    glEnable(GL_DEPTH_TEST);
    // create timer
    connect (& timer , SIGNAL ( timeout () ) , this , SLOT ( animate ()) ) ;
    timer.start(0) ;

}
void OpenGLWidget::resizeGL(int w, int h){
    glViewport (0 , 0 , w , h ) ;
    if( scene ) {
        scene -> camera.projectionMatrix.setToIdentity () ;
        scene -> camera.projectionMatrix.perspective (60.0 , static_cast < qreal >( w ) / static_cast < qreal >( h ) , 0.1 ,20.0) ;
        scene -> obj1 -> trackBall.resizeViewport(w , h);
    }
    update () ;

}

void OpenGLWidget::paintGL(){
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(scene){
        scene->drawScene();
    }

}
/* Rotacao com Sliders na mesma função
void OpenGLWidget :: onUpdateBar(){
    QSlider* slx = parent()->findChild<QSlider*>("Sliderx");
    QSlider* sly = parent()->findChild<QSlider*>("Slidery");
    QSlider* slz = parent()->findChild<QSlider*>("Sliderz");
    scene->obj1->rotationx = slx->value();
    scene->obj1->rotationy = sly->value();
    scene->obj1->rotationz = slz->value();
    update();
}
*/
//Rotações com Sliders individualmente
void OpenGLWidget :: rotatex(){
    QSlider* slx = parent()->findChild<QSlider*>("Sliderx");
    scene->obj1->rotationx = slx->value();
    //.setToIdentity();
    update();
}

void OpenGLWidget :: rotatey(){
    QSlider* sly = parent()->findChild<QSlider*>("Slidery");
    scene->obj1->rotationy = sly->value();
    update();
}

void OpenGLWidget :: rotatez(){
    QSlider* slz = parent()->findChild<QSlider*>("Sliderz");
    scene->obj1->rotationz = slz->value();
    update();
}

//Scale X
void OpenGLWidget :: rescalex(){
    QDoubleSpinBox* scx = parent()->findChild<QDoubleSpinBox*>("scalex");
    scene->obj1->scalex = scx->value();
    update();
}

//Scale Y
void OpenGLWidget :: rescaley(){
    QDoubleSpinBox* scy = parent()->findChild<QDoubleSpinBox*>("scaley");
    scene->obj1->scaley = scy->value();
    update();
}

//Scale Z
void OpenGLWidget :: rescalez(){
    QDoubleSpinBox* scz = parent()->findChild<QDoubleSpinBox*>("scalez");
    scene->obj1->scalez = scz->value();
    update();
}

//Auto Rotate em X

void OpenGLWidget :: startRotationx (){
    if(scene == NULL || scene->obj1 == NULL)
        return;
    scene->obj1->rotationx += 1;
    update();
}

void OpenGLWidget :: stopRotationx (){
    QSlider* slx = parent()->findChild<QSlider*>("Sliderx");
    if(scene == NULL || scene->obj1 == NULL)
        return;
    scene->obj1->rotationx = slx->value();
    update();
}

void OpenGLWidget :: autoRotatex(bool rotate){
    if(rotate == 1){
        connect(timerx, SIGNAL(timeout()), this, SLOT(startRotationx()));
        timerx->start(30);
    }else{
        timerx->stop();
        stopRotationx();

    }
}

//Auto Rotate em Y

void OpenGLWidget :: startRotationy (){
    if(scene == NULL || scene->obj1 == NULL)
        return;
    scene->obj1->rotationy += 1;
    update();
}

void OpenGLWidget :: stopRotationy (){
    QSlider* sly = parent()->findChild<QSlider*>("Slidery");
    if(scene == NULL || scene->obj1 == NULL)
        return;
    scene->obj1->rotationy = sly->value();
    update();
}

void OpenGLWidget :: autoRotatey(bool rotate){
    if(rotate == 1){
        connect(timery, SIGNAL(timeout()), this, SLOT(startRotationy()));
        timery->start(30);
    }else{
        timery->stop();
        stopRotationy();

    }
}

//Auto Rotate Z

void OpenGLWidget :: startRotationz (){
    if(scene == NULL || scene->obj1 == NULL)
        return;
    scene->obj1->rotationz += 1;
    update();
}

void OpenGLWidget :: stopRotationz (){
    QSlider* slz = parent()->findChild<QSlider*>("Sliderz");
    if(scene == NULL || scene->obj1 == NULL)
        return;
    scene->obj1->rotationz = slz->value();
    update();
}

void OpenGLWidget :: autoRotatez(bool rotate){
    if(rotate == 1){
        connect(timerz, SIGNAL(timeout()), this, SLOT(startRotationz()));
        timerz->start(30);
    }else{
        timerz->stop();
        stopRotationz();

    }
}

void OpenGLWidget :: loadMaze () {
    makeCurrent () ;
    QByteArray fileFormat = "txt";
    QString fileName;
    fileName = QFileDialog :: getOpenFileName(this,"Open File",QDir::homePath(),QString("\%1 Files (*.\%2)").arg(QString(fileFormat.toUpper())).arg(QString(fileFormat)));
    int curShader = 0;
    if (!fileName.isEmpty()) {
        if(scene) {
            delete scene ;
        }
        scene = new Scene();
        scene->obj1 = new SceneObject(this);
        scene->obj1->currentShader = curShader ;
        //scene->camera.projectionMatrix.setToIdentity();
        scene->obj1->readMazeFile(fileName);
        scene -> camera.projectionMatrix.setToIdentity () ;
        scene -> camera.projectionMatrix.perspective(60.0 , static_cast < qreal >(this -> width () ) / static_cast <qreal>(this -> height () ) , 0.1 , 20.0);

        scene->obj1->trackBall.resizeViewport(this->width(),this->height());
        emit statusBarMessage(QString(" Vertices: \%1, Faces: \%2 ").arg(scene->obj1->numVertices).arg(scene->obj1->numFaces));
        emit enableComboShaders(true);
    }
    update () ;
}

void OpenGLWidget :: showFileOpenDialog ()
{
    makeCurrent () ;
    QByteArray fileFormat = "off";
    QString fileName;
    fileName = QFileDialog :: getOpenFileName(this,"Open File",QDir::homePath(),QString("\%1 Files (*.\%2)").arg(QString(fileFormat.toUpper())).arg(QString(fileFormat)));
    int curShader = 0;
    if (!fileName.isEmpty()) {
        if(scene) {
            delete scene ;
        }
        scene = new Scene();
        scene->obj1 = new SceneObject(this);
        scene->obj1->currentShader = curShader ;
        //scene->camera.projectionMatrix.setToIdentity();
        scene->obj1->readOFFFile(fileName);
        scene -> camera.projectionMatrix.setToIdentity () ;
        scene -> camera.projectionMatrix.perspective(60.0 , static_cast < qreal >(this -> width () ) / static_cast <qreal>(this -> height () ) , 0.1 , 20.0);

        scene->obj1->trackBall.resizeViewport(this->width(),this->height());
        emit statusBarMessage(QString(" Vertices: \%1, Faces: \%2 ").arg(scene->obj1->numVertices).arg(scene->obj1->numFaces));
        emit enableComboShaders(true);
    }
    update () ;
}

void OpenGLWidget :: changeShader (int shader )
{

    if(scene && scene->obj1) {
    scene->obj1->updateSceneObject(shader);
    update();
    }
}

void OpenGLWidget :: animate ()
{
    update () ;
}

void OpenGLWidget :: mouseMoveEvent ( QMouseEvent * event )
{
    if( scene && scene -> obj1 ) {
    scene -> obj1 -> trackBall.mouseMove ( event -> localPos () ) ;
    }
}

void OpenGLWidget :: mousePressEvent ( QMouseEvent * event )
{
    if( scene && scene -> obj1 ) {
        if ( event -> button () & Qt :: LeftButton )
            scene -> obj1 -> trackBall . mousePress ( event -> localPos () ) ;
        }
}

void OpenGLWidget :: mouseReleaseEvent ( QMouseEvent * event )
{
    if( scene && scene -> obj1 ) {
        if ( event -> button () == Qt :: LeftButton )
        scene -> obj1 -> trackBall . mouseRelease ( event ->localPos () ) ;
        }
}

void OpenGLWidget::keyPressEvent( QKeyEvent * event)
{
    if( scene && scene -> obj1 ) {
        float y_correct = scene->obj1->midPoint.y();
        if ( event->key() == Qt::Key_A) {
            // antes de rotacionar, tenha certeza que esta no meio do quadrado
            float x_correct = qFloor(scene->obj1->midPoint.x()) + 0.5;
            float z_correct = qFloor(scene->obj1->midPoint.z()) + 0.5;
            scene->obj1->midPoint = QVector3D(x_correct, y_correct, z_correct);
            scene->obj1->rotationy -= 2.0;
        }
        if ( event->key() == Qt::Key_D) {
            // antes de rotacionar, tenha certeza que esta no meio do quadrado
            float x_correct = qFloor(scene->obj1->midPoint.x()) + 0.5;
            float z_correct = qFloor(scene->obj1->midPoint.z()) + 0.5;
            scene->obj1->midPoint = QVector3D(x_correct, y_correct, z_correct);
            scene->obj1->rotationy += 2.0;
        }
        float z_walk = cos(qDegreesToRadians(scene->obj1->rotationy));
        float x_walk = sin(qDegreesToRadians(scene->obj1->rotationy));
        if ( event->key() == Qt::Key_W) {
            // anda
            scene->obj1->midPoint += QVector3D(x_walk * 0.1, 0 , -z_walk * 0.1);
            // verifica se pode andar
            int x = qFloor(scene->obj1->midPoint.x());
            int z = qFloor(scene->obj1->midPoint.z());
            // verifica se essa eh uma posicao valida
            if (scene->obj1->is_passable[z * 57 + x] == 1) {
                // se nao for retorna para a last_position
                 scene->obj1->midPoint = scene->obj1->last_position;
            } else {
                scene->obj1->last_position = scene->obj1->midPoint;
            }

        }
        if ( event->key() == Qt::Key_S) {
            scene->obj1->midPoint += QVector3D(-x_walk  * 0.1, 0 , z_walk  * 0.1);
            // verifica se pode andar
            int x = qFloor(scene->obj1->midPoint.x());
            int z = qFloor(scene->obj1->midPoint.z());
            // verifica se essa eh uma posicao valida
            if (scene->obj1->is_passable[z * 57 + x] == 1) {
                // se nao for retorna para a last_position
                 scene->obj1->midPoint = scene->obj1->last_position;
            } else {
                scene->obj1->last_position = scene->obj1->midPoint;
            }
        }
        update();
    }
}
