#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <fstream>
#include <limits>
#include <iostream>
#include <material.h>
#include <trackball.h>

class SceneObject : public QOpenGLFunctions
{
public:
    QVector2D * texCoords;
    QOpenGLTexture * texture ;
    QImage image ;
    QOpenGLBuffer * vboTextCoord ;
    QMatrix4x4 model ;
    QVector3D midPoint ;
    double invDiag;
    double scalex;
    double scaley;
    double scalez;
    int rotationx;
    float rotationy;
    int * is_passable;
    int rotationz;
    Material material;
    int currentShader;
    const int nShaders = 4;
    QVector3D *normals;
    SceneObject(QOpenGLWidget *W);
    ~ SceneObject();
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vboVertices;
    QOpenGLBuffer *vboNormals;
    QOpenGLBuffer *vboIndices;
    QOpenGLBuffer *vboColors;
    QVector4D *vertices;
    QVector4D *colors;
    QVector3D last_position;
    unsigned int *indices;
    //QOpenGLShader *vertexShader;
    //QOpenGLShader *fragmentShader;
    //QOpenGLShaderProgram *shaderProgram;
    TrackBall trackBall;
    std::vector<QOpenGLShader*>vertexShader ;
    std::vector<QOpenGLShader*>fragmentShader ;
    std::vector<QOpenGLShaderProgram*>shaderProgram ;
    QOpenGLWidget *w;
    unsigned int numVertices;
    unsigned int numFaces;
    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void drawObject();
    void createNormals();
    void destroyNormals();
    void readOFFFile(QString const & filename);
    void readMazeFile(QString const & filename);
    void setShaderAttributes();
    void updateSceneObject(int);
    void createTextCoords ();
    void createTexture ( QString const & fileName );
};

#endif // SCENEOBJECT_H
