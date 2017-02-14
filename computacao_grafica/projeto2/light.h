#ifndef LIGHT_H
#define LIGHT_H
#include <QVector4D>
class Light
{
public:
    Light();
    QVector4D position;
    QVector4D ambient ;
    QVector4D diffuse ;
    QVector4D specular ;
};

#endif // LIGHT_H
