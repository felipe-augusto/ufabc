#include "scene.h"

Scene::Scene()
{
//    projectionMatrix.setToIdentity();
//    projectionMatrix.ortho( -1 ,1 , -1 ,1 , -1 ,1);
//    cameraMatrix.setToIdentity () ;
}

Scene :: ~ Scene(){
    if(obj1){
        delete obj1;
        obj1 = NULL;
    }
}

void Scene::drawScene(){
    /*if(obj1){
        obj1->drawObject();
    }*/
    if( obj1 ) {
    QOpenGLShaderProgram*ptrSProgram=obj1->shaderProgram[obj1->currentShader];
    ptrSProgram->bind();
    ptrSProgram -> setUniformValue ("projection", camera.projectionMatrix ) ;
    ptrSProgram -> setUniformValue ("view", camera.viewMatrix ) ;
//    ptrSProgram->setUniformValue("projection",projectionMatrix);
//    ptrSProgram->setUniformValue("view",cameraMatrix);
    QVector4D ambientProduct = light.ambient*obj1->material.ambient;
    QVector4D diffuseProduct = light.diffuse*obj1->material.diffuse;
    QVector4D specularProduct = light.specular*obj1->material.specular;
    ptrSProgram->setUniformValue("lightPosition",light.position);
    ptrSProgram->setUniformValue("ambientProduct",ambientProduct);
    ptrSProgram->setUniformValue("diffuseProduct",diffuseProduct);
    ptrSProgram->setUniformValue("specularProduct",specularProduct);
    obj1->drawObject();
    ptrSProgram->release();
    }


    }
