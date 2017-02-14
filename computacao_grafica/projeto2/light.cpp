#include "light.h"

Light::Light()
{
    position = QVector4D(0, -15.0, 0 ,1);
    ambient = QVector4D(1, 1, 1, 1.0);
    diffuse = QVector4D(1, 1, 1, 1.0);
    specular = QVector4D(1, 1, 1, 1.0);
}
