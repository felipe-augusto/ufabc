#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();

    QVector3D eye;
    QVector3D up;
    QVector3D center;

    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;
    void computeViewMatrix();
};

#endif // CAMERA_H
