#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QImage>
#include <QFileDialog>
#include <iostream>
#include <QtOpenGL>
#include <QMediaPlayer>

class OpenGLWidget : public QOpenGLWidget , protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

    void paintGL();
    void resizeGL(int w, int h);
    void initializeGL();
    void destroyVBOs();
    void createVBOs();
    void updateTexture();
    void createShaders();
    void destroyShaders();

private:
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vboVertices;
    QOpenGLBuffer *vboIndices;
    QOpenGLBuffer *vbocoordText;
    QOpenGLTexture * colorTexture;

    QVector2D *coordText;
    QVector4D *vertices;
    unsigned int *indices;

    QOpenGLShader *vertexShader;
    QOpenGLShader *fragmentShader;
    QOpenGLShaderProgram *shaderProgram;

    QImage image;
    QImage *imgOrig;

    float slider;
    float controler;
    float width;
    float height;
    unsigned int currentShader;

public slots:
    void setImage(QImage *img);
    void changeShader(int);
    void updateSlider();
    void passValue(int);
};

#endif // OPENGLWIDGET_H
