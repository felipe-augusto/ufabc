#include "camera.h"

Camera::Camera()
{
    eye = QVector3D (0.0 , 0.0 , 0.5) ;
    center = QVector3D (0.0 , 0.0 , 0.0) ;
    up = QVector3D (0.0 , 1.0 , 0.0) ;
    projectionMatrix . setToIdentity () ;
    computeViewMatrix () ;

}

void Camera :: computeViewMatrix ()
{
    viewMatrix.setToIdentity () ;
    viewMatrix.lookAt(eye, center, up) ;
}
