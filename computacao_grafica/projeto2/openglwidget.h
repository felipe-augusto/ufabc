#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

# include <QWidget>
# include <QTimer>
# include <QtOpenGL>
# include <QOpenGLWidget>
# include <QOpenGLFunctions>
#include <scene.h>
class OpenGLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT
signals:
    void statusBarMessage(QString);
    void enableComboShaders(bool);

public slots:
    void showFileOpenDialog();
    void loadMaze();
    void changeShader(int);
    //void onUpdateBar();
    void startRotationx();
    void stopRotationx();
    void startRotationy();
    void stopRotationy();
    void startRotationz();
    void stopRotationz();
    void autoRotatex(bool);
    void autoRotatey(bool);
    void autoRotatez(bool);
    void rescalex();
    void rescaley();
    void rescalez();
    void rotatex();
    void rotatey();
    void rotatez();
    void animate();
public:
    QTimer *timerx;
    QTimer *timery;
    QTimer *timerz;
    void mouseMoveEvent ( QMouseEvent * event ) ;
    void mousePressEvent ( QMouseEvent * event ) ;
    void mouseReleaseEvent ( QMouseEvent * event ) ;
    void keyPressEvent ( QKeyEvent * event);
    QTimer timer ;
    explicit OpenGLWidget(QWidget *parent = 0);
    ~ OpenGLWidget();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    Scene *scene;

};


#endif // OPENGLWIDGET_H
