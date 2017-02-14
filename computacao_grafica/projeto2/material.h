#ifndef MATERIAL_H
#define MATERIAL_H
#include <QVector4D>

class Material
{
public:
    Material();
    QVector4D ambient ;
    QVector4D diffuse ;
    QVector4D specular ;
    double shininess ;
};

#endif // MATERIAL_H
