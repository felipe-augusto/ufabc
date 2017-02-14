#ifndef SCENE_H
#define SCENE_H
#include <light.h>
#include <sceneobject.h>
#include <camera.h>

class Scene
{
public:
    Scene();
    ~ Scene();
    void drawScene();
    SceneObject *obj1;
    Camera camera;
    Light light;
};

#endif // SCENE_H
