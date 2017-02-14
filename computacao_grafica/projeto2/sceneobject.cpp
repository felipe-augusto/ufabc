#include "sceneobject.h"
#include <QVector4D>

SceneObject::SceneObject(QOpenGLWidget *W)
{
    w=W;
    initializeOpenGLFunctions();
    vertices = NULL;
    indices = NULL;
    vboVertices = NULL;
    vboNormals = NULL;
    vboIndices = NULL;
    vao = NULL;
    normals = NULL;
    colors = NULL;
    vboColors = NULL;
    //shaderProgram = NULL;
    //vertexShader = NULL;
    //fragmentShader = NULL;
    normals = NULL;
    vboNormals = NULL;
    currentShader = 0;
    rotationx = 0;
    rotationy = 0;
    rotationz = 0;
    scalex = 1.0;
    scaley = 1.0;
    scalez = 1.0;
    is_passable = NULL;
    texCoords = NULL ;
    texture = NULL ;
    vboTextCoord = NULL ;
}

SceneObject :: ~ SceneObject(){
    this->w->makeCurrent();
    destroyVBOs();
    destroyShaders();
}

void SceneObject :: destroyVBOs(){
    this->w->makeCurrent();
    if(vboVertices){
        vboVertices->release();
        vboVertices->destroy();
        delete vboVertices;
        vboVertices = NULL;
    }
    if (vboIndices){
        vboIndices->release();
        vboIndices->destroy();
        delete vboIndices;
        vboIndices = NULL;
    }
    if (vao){
        delete vao;
        vao = NULL;
    }
    if (vboNormals) {
        vboNormals->release();
        vboNormals->destroy();
        delete vboNormals ;
        vboNormals = NULL ;
    }
    if(vboColors){
        vboColors->release();
        vboColors->destroy();
        delete vboColors;
        vboColors = NULL;
    }
}

void SceneObject:: destroyShaders(){
    this->w->makeCurrent();
    if(vertexShader.size()!=0)
    for (uint i = 0;i<vertexShader.size(); i++)
    {
    if(vertexShader[i])
    {
    delete vertexShader[i];
    vertexShader[i] = NULL ;
    }
    }
    if(fragmentShader.size()!=0)
    for (uint i = 0;i<fragmentShader.size(); i++)
    {
    if(fragmentShader[i])
    {
    delete fragmentShader[i];
    fragmentShader[i] = NULL ;
    }
    }

    if(shaderProgram.size()!=0)
    for (uint i = 0;i<shaderProgram.size(); i++)
    {
    if(shaderProgram[i])
    {
    delete shaderProgram[i];
    shaderProgram[i] = NULL ;
    }
    }

    /*this->w->makeCurrent();
    delete vertexShader;
    vertexShader = NULL;
    delete fragmentShader;
    fragmentShader = NULL;
    if(shaderProgram){
        shaderProgram->release();
        delete shaderProgram;
        shaderProgram = NULL;
    }*/
}






void SceneObject::createVBOs(){
    this->w->makeCurrent();
    destroyVBOs();
    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    vboVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboVertices->create();
    vboVertices->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboVertices->bind();
    vboVertices->allocate(vertices, numVertices*sizeof(QVector4D));
    //shaderProgram->enableAttributeArray("vPosition");
    //shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT,0,4,0);
    vboVertices->release();
    delete [] vertices;
    vertices = NULL;
    vboIndices = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vboIndices->create();
    vboIndices->bind();
    vboIndices->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboIndices->allocate(indices,numFaces*3*sizeof(unsigned int));
    vboIndices->release();
    delete [] indices;
    indices = NULL;

    vboNormals = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboNormals->create();
    vboNormals->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboNormals->bind();
    vboNormals->allocate(normals, numVertices*sizeof(QVector3D));
    //shaderProgram->enableAttributeArray("normals");
    //shaderProgram->setAttributeBuffer("normals", GL_FLOAT,0,3,0);
    vboNormals->release();
    delete [] normals;
    normals = NULL;
    // cores
    vboColors = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboColors->create();
    vboColors->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboColors->bind();
    vboColors->allocate(colors, numVertices * sizeof(QVector4D));
    vboColors->release();
    delete [] colors;
    colors = NULL;

    vao->release();
    qDebug()<<"vbos created";
}

void SceneObject::createShaders(){
    this->w->makeCurrent();
    destroyShaders();
    QString vertexShaderFile[] = {":/shaders/vshader1.glsl",
                                ":/shaders/vflat.glsl",
                                ":/shaders/vgouraud.glsl",
                                ":/shaders/vphong.glsl"};

    QString fragmentShaderFile[] =  {":/shaders/fshader1.glsl",
                                     ":/shaders/fflat.glsl",
                                     ":/shaders/fgouraud.glsl",
                                     ":/shaders/fphong.glsl"};

    vertexShader.resize(nShaders);
    fragmentShader.resize(nShaders);
    shaderProgram.resize(nShaders);
    for (int i =0; i<nShaders ; i++)
    {
    vertexShader[i] = new QOpenGLShader(QOpenGLShader::Vertex);
    if (!vertexShader[i]->compileSourceFile(vertexShaderFile[i]))
        qWarning()<<vertexShader[i]->log();
    fragmentShader[i] = new QOpenGLShader(QOpenGLShader::Fragment);
    if (!fragmentShader[i]->compileSourceFile(fragmentShaderFile[i]))
        qWarning()<<fragmentShader[i]->log();
    shaderProgram[i] = new QOpenGLShaderProgram;
    shaderProgram[i]->addShader(vertexShader[i]);
    shaderProgram[i]->addShader(fragmentShader[i]);
    if (!shaderProgram[i]->link())
        qWarning()<<shaderProgram[i]->log()<<endl;
    qDebug()<<i;
    }
    /*vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    if(!vertexShader->compileSourceFile(vertexShaderFile)){
        qWarning()<<vertexShader->log();
    }
    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if(!fragmentShader->compileSourceFile(fragmentShaderFile)){
        qWarning()<<fragmentShader->log();
    }
    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);
    if(!shaderProgram->link()){
        qWarning()<<shaderProgram->log()<<endl;
    }*/
    qDebug()<<"shaders created ";
}

void SceneObject::drawObject(){
    this->w->makeCurrent();
    if(!vboVertices && !vao){
        return;
    }
    shaderProgram[currentShader]->bind();
    model.setToIdentity();

    model.scale(invDiag*scalex,invDiag*scaley,invDiag*scalez);
    model.rotate(rotationx,1,0,0);
    model.rotate(rotationy,0,1,0);
    model.rotate(rotationz,0,0,1);
    model.rotate(trackBall.getRotation());
    model.translate(-midPoint);

    shaderProgram[currentShader]->setUniformValue("model",model);
    shaderProgram[currentShader]->setUniformValue("normalMatrix",model.normalMatrix());
    shaderProgram[currentShader]->setUniformValue("shininess",static_cast<GLfloat>(material.shininess));
    vao->bind();
    vboIndices->bind();
    glDrawElements(GL_TRIANGLES, numFaces*3, GL_UNSIGNED_INT, 0);
    vboIndices->release();
    shaderProgram[currentShader]->release();
    vao->release();

}

void SceneObject :: createNormals()
{
normals = new QVector3D[numVertices];
QVector3D a, b, c, tmp;
for (unsigned int i = 0; i<numFaces ; i++) {
a = QVector3D(vertices[indices[i*3]]);
b = QVector3D(vertices[indices[i*3+1]]);
c = QVector3D(vertices[indices[i*3+2]]);
tmp = QVector3D::crossProduct((b-a),(c-b));
tmp.normalize();
// Calculates the face normal and acumulates on the  vertices
normals[indices[i*3]] += tmp ;
normals[indices[i*3+1]] += tmp ;
normals[indices[i*3+2]] += tmp ;
}
for (unsigned int i = 0; i<numVertices ; i++) {
normals[i].normalize();
}
}


void SceneObject :: destroyNormals ()
{
delete normals ;
normals = NULL ;
}


void SceneObject::readMazeFile(QString const & fileName){
    this->w->makeCurrent();
    QFile file(fileName.toUtf8());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);

    int count = 0;


    numVertices = 0;
    numFaces = 0;

    // descobre o numero de vetores necessarios para desenhar o labirinto
    while (!in.atEnd()) {
           QString line = in.readLine();
           QStringList list = line.split("");
           for (QStringList::iterator it = list.begin(); it != list.end(); ++it) {
               QString current = *it;
               int is_wall = QString::compare(current, "#", Qt::CaseInsensitive);
               if (is_wall == 0) {
                    numVertices += 8;
                    numFaces += 12;
               } else {
                   numVertices += 4;
                   numFaces += 2;
               }

           }

    }

    in.seek(0);

    delete [] vertices;
    vertices = new QVector4D [numVertices];
    // cada for vai 1 em x, cada while vai 1 em y
    int ind_id = 0 ;
    int coordX = 0;
    int coordY = 0;
    // processa linha por linha

    //vetor de indices
    delete [] indices ;
    indices = new unsigned int [numFaces * 3]; // 7866

    // cores
    delete [] colors;
    colors = new QVector4D [numVertices];

    // vetor de permissoes
    delete [] is_passable;
    is_passable = new int [57 * 23];
    while (!in.atEnd()) {
           QString line = in.readLine();
           QStringList list = line.split("");
            coordX = 0;
           // processa coluna por coluna
           for (QStringList::iterator it = list.begin(); it != list.end(); ++it) {
                   QString current = *it;
                   // verifica se é parade ou chao
                   int is_wall = QString::compare(current, "#", Qt::CaseInsensitive);
                   if (is_wall == 0) {
                       // SE FOR PAREDE TEM QUE CRIAR UMA PAULADA DE VETORES, DE CORES E TOPOLOGIAS
                       // AO INVES DE 4 VERTICES -> 8 VERTICES E 8 CORES
                       // 12 TRIANGULOS NO TOTAL (CADA TRIANGULO TEM 3 COORDENADAS) -> 3 PARA CADA
                       // inferior esquerda
                       vertices[count] = QVector4D(coordX, 0, coordY, 1.0);
                       vertices[count + 1] = QVector4D(coordX + 1, 0, coordY, 1.0);
                       vertices[count + 2] = QVector4D(coordX + 1, 0, coordY + 1, 1.0);
                       vertices[count + 3] = QVector4D(coordX, 0, coordY + 1, 1.0);
                       // vertices no alto
                       vertices[count + 4] = QVector4D(coordX, 1.5, coordY, 1.0);
                       vertices[count + 5] = QVector4D(coordX + 1, 1.5, coordY, 1.0);
                       vertices[count + 6] = QVector4D(coordX + 1, 1.5, coordY + 1, 1.0);
                       vertices[count + 7] = QVector4D(coordX, 1.5, coordY + 1, 1.0);
                       // cores
                       colors [count] = QVector4D (1 ,0 ,0 ,1) ;
                       colors [count + 2] = QVector4D (1 ,0 ,0 ,1) ;
                       colors [count + 3] = QVector4D (1 ,0 ,0 ,1) ;
                       colors [count + 4] = QVector4D (1 ,0 ,0 ,1) ;
                       colors [count + 5] = QVector4D (1 ,0 ,0 ,1) ;
                       colors [count + 6] = QVector4D (1 ,0 ,0 ,1) ;
                       colors [count + 7] = QVector4D (1 ,0 ,0 ,1) ;
                       // TOPOLOGIAS
                       // topologia do chao
                       indices[ind_id] = count;
                       indices[ind_id + 1] = count + 1;
                       indices[ind_id + 2] = count + 2;

                       indices[ind_id + 3] = count + 2;
                       indices[ind_id + 4] = count + 3;
                       indices[ind_id + 5] = count;
                       // topologia do topo
                       indices[ind_id + 6] = count + 6;
                       indices[ind_id + 7] = count + 7;
                       indices[ind_id + 8] = count + 4;

                       indices[ind_id + 9] = count + 4;
                       indices[ind_id + 10] = count + 5;
                       indices[ind_id + 11] = count + 6;
                       // topologia do esquerda
                       indices[ind_id + 12] = count + 3;
                       indices[ind_id + 13] = count;
                       indices[ind_id + 14] = count + 4;

                       indices[ind_id + 15] = count + 4;
                       indices[ind_id + 16] = count + 7;
                       indices[ind_id + 17] = count + 3;
                       // topologia do direita
                       indices[ind_id + 18] = count + 1;
                       indices[ind_id + 19] = count + 2;
                       indices[ind_id + 20] = count + 6;

                       indices[ind_id + 21] = count + 6;
                       indices[ind_id + 22] = count + 5;
                       indices[ind_id + 23] = count + 1;
                       // topologia da frente
                       indices[ind_id + 24] = count;
                       indices[ind_id + 25] = count + 1;
                       indices[ind_id + 26] = count + 5;

                       indices[ind_id + 27] = count + 5;
                       indices[ind_id + 28] = count + 4;
                       indices[ind_id + 29] = count;
                       // topologia de tras
                       indices[ind_id + 30] = count + 2;
                       indices[ind_id + 31] = count + 3;
                       indices[ind_id + 32] = count + 7;

                       indices[ind_id + 33] = count + 7;
                       indices[ind_id + 34] = count + 6;
                       indices[ind_id + 35] = count + 2;
                       ind_id += 36;
                       count += 8;
                       is_passable[coordY * 57 + coordX] = 1;
                   } else {
                       // desenha o chao
                       vertices[count] = QVector4D(coordX, 0, coordY, 1.0); // inferior esquerda
                       vertices[count + 1] = QVector4D(coordX + 1, 0, coordY, 1.0); // inferior direito
                       vertices[count + 2] = QVector4D(coordX + 1, 0, coordY + 1, 1.0);// superior direito
                       vertices[count + 3] = QVector4D(coordX, 0, coordY + 1, 1.0); // superior esquerdo
                       // verifica se é ponto de partida
                       int is_entrada = QString::compare(current, "E", Qt::CaseInsensitive);
                       if (is_entrada == 0) {
                            this->midPoint=QVector3D(coordX + 0.5, 0.5, coordY + 0.5) ;
                       }
                       colors [count] = QVector4D (0 ,1 ,0 ,1) ;
                       colors [count + 1] = QVector4D (0 ,1 ,0 ,1) ;
                       colors [count + 2] = QVector4D (0 ,1 ,0 ,1) ;
                       colors [count + 3] = QVector4D (0 ,1 ,0 ,1) ;
                       // topologia do chao
                       indices[ind_id] = count;
                       indices[ind_id + 1] = count + 1;
                       indices[ind_id + 2] = count + 2;

                       indices[ind_id + 3] = count + 2;
                       indices[ind_id + 4] = count + 3;
                       indices[ind_id + 5] = count;
                       ind_id += 6;
                       count += 4;
                       is_passable[coordY * 57 + coordX] = 0;
                   }
                   coordX++;

           }
           coordY++;

     }


    // arruma para sair para o direcao correta
    this->rotationy = 180;
    this->invDiag=1; //(max-min).length()
    qDebug() << invDiag;
    createShaders();

    createNormals();
    createVBOs();
    setShaderAttributes();


}


void SceneObject::readOFFFile(QString const & fileName){
    this->w->makeCurrent();
    std::ifstream stream;
    stream.open(fileName.toUtf8(),std::ifstream::in);
    if(!stream.is_open()){
        qWarning("Cannot open file");
        return;
    }
    std::string line;
    stream>>line;
    // first line of OFF file
    stream>>numVertices>>numFaces>>line;
    delete [] vertices;
    vertices = new QVector4D [numVertices];
    delete [] indices ;
    indices = new unsigned int [numFaces*3];
    if (numVertices>0){
        double minLim = std::numeric_limits<double>::min();
        double maxLim = std::numeric_limits<double>::max();
        QVector4D max(minLim , minLim , minLim ,1.0);
        QVector4D min(maxLim , maxLim , maxLim ,1.0);
        for (unsigned int i = 0; i<numVertices ; i++){
            double x, y, z;
            stream>>x>>y>>z;
            max.setX(qMax<double>(max.x(),x));
            max.setY(qMax<double>(max.y(),y));
            max.setZ(qMax<double>(max.z(),z));
            min.setX(qMin<double>(min.x(),x));
            min.setY(qMin<double>(min.y(),y));
            min.setZ(qMin<double>(min.z(),z));
            vertices[i] = QVector4D(x, y, z, 1.0);
        }
        /*QVector4D midpoint = (min + max)*0.5;
        double invdiag = 1/(max - min).length();
        for ( unsigned int i = 0; i < numVertices; i++){
            vertices[i] = (vertices[i] - midpoint)*invdiag;
            vertices[i].setW(1);
        }Versão Antiga*/
        this->midPoint=QVector3D((min+max)*0.5) ;
        this->invDiag=1/(max-min).length();
    }
    for (unsigned int i = 0; i<numFaces; i++){
        unsigned int a, b, c;
        stream>>line>>a>>b>>c;
        indices[i*3] = a;
        indices[i*3+1] = b;
        indices[i*3+2] = c;
     }
     stream.close();
     createNormals();
     createShaders();
     createVBOs();
     setShaderAttributes();
     // do some transformations here :

}

void SceneObject::updateSceneObject(int Shader)
{
currentShader = Shader ;
setShaderAttributes();
}


void SceneObject :: setShaderAttributes ()
{
this->w->makeCurrent();
shaderProgram[currentShader]->bind();
vao->bind();
vboVertices->bind();
shaderProgram[currentShader]->enableAttributeArray("vPosition");
shaderProgram[currentShader]->setAttributeBuffer("vPosition", GL_FLOAT , 0 , 4 , 0);
vboVertices->release() ;

vboNormals->bind() ;
shaderProgram[currentShader]->enableAttributeArray("vNormals");
shaderProgram[currentShader]->setAttributeBuffer("vNormals",GL_FLOAT , 0 , 3 , 0) ;
vboNormals->release() ;
// cores

vboColors->bind() ;
shaderProgram[currentShader]->enableAttributeArray("vColors");
shaderProgram[currentShader]->setAttributeBuffer("vColors",GL_FLOAT , 0 , 4 , 0) ;
vboColors->release() ;

vao->release();
shaderProgram[currentShader]->release();
}
