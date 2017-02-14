#include "openglwidget.h"

//Construtor da classe
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    vertices = NULL;
    indices = NULL;
    coordText = NULL;
    colorTexture = NULL;

    //Inicia os VBOS e VAO apontando para NULL==========================
    vbocoordText = NULL;
    vboVertices = NULL;
    vboIndices = NULL;
    vao = NULL;
    //==================================================================

    //Inicia os shaders apontando para NULL=============================
    shaderProgram = NULL;

    vertexShader = NULL;
    fragmentShader = NULL;
    //==================================================================

    //Shader inicial = imagem original==================================
    currentShader = 0;

    //Imagem original vazia=============================================
    imgOrig = NULL;
    //==================================================================
    slider = NULL;
    controler = NULL;

    //INICIA WIDTH AND HEIGHT
    width = 0;
    height = 0;
}
//======================================================================

//Destrutor da classe
OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
    if(imgOrig) delete imgOrig;
}
//======================================================================

//Inicializa funções OpenGL
void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //Exibe informacoes sobre a versao do OpenGL e GLSL=================
    std :: cerr << " Version " << glGetString ( GL_VERSION ) <<" \n " ;
    std :: cerr << " GLSL " << glGetString ( GL_SHADING_LANGUAGE_VERSION );
    //==================================================================

    createShaders();
    createVBOs();
}
//======================================================================

//Resize
void OpenGLWidget::resizeGL(int w, int h)
{
    width = w;
    height = h;
    update();
}
//======================================================================

//Destroi Shaders
void OpenGLWidget::destroyShaders()
{
    delete vertexShader;
    vertexShader = NULL;

    delete fragmentShader;
    fragmentShader = NULL;

    if (shaderProgram) {
        shaderProgram->release();
        delete shaderProgram;
        shaderProgram = NULL;
    }
}
//======================================================================

//Cria Shaders
void OpenGLWidget::createShaders()
{
    makeCurrent();
    destroyShaders();

    //Shaders padrões: vshader e fshader================================
    QString vertexShaderFile[] = {":/shaders/vshader.glsl",
                                  ":/shaders/vinvert.glsl",
                                  ":/shaders/vedge.glsl",
                                  ":/shaders/vgauss.glsl",
                                  ":/shaders/vbloom.glsl",
                                  ":/shaders/vgamma.glsl",
                                  ":/shaders/vsniper.glsl",
                                  ":/shaders/vpixel.glsl"};

    QString fragmentShaderFile[] = {":/shaders/fshader.glsl",
                                    ":/shaders/finvert.glsl",
                                    ":/shaders/fedge.glsl",
                                    ":/shaders/fgauss.glsl",
                                    ":/shaders/fbloom.glsl",
                                    ":/shaders/fgamma.glsl",
                                    ":/shaders/fsniper.glsl",
                                    ":/shaders/fpixel.glsl"
                                   };
    //==================================================================

    qDebug() << "Chamando shader " << fragmentShaderFile[currentShader];

    vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    if (!vertexShader->compileSourceFile(vertexShaderFile[currentShader]))
        qWarning() << vertexShader->log();

    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if (!fragmentShader->compileSourceFile(fragmentShaderFile[currentShader]))
        qWarning() << fragmentShader->log();

    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);

    if (!shaderProgram->link())
        qWarning() << shaderProgram->log() << endl;
}
//======================================================================

//Destroi VBOs
void OpenGLWidget::destroyVBOs()
{
    //Destroi VBO de vertices
    if (vboVertices) {
        delete vboVertices;
        vboVertices = NULL;
    }
    //Destroi VBO de indices
    if (vboIndices) {
        delete vboIndices;
        vboIndices = NULL;
    }
    //Destroi VBO de coordenadas da textura
    if (vbocoordText) {
        delete vbocoordText;
        vbocoordText = NULL;
    }
    //Destroi VAO
    if ( vao )
    {
        delete vao ;
        vao = NULL ;
    }
}
//======================================================================

//Cria os VBOs
void OpenGLWidget::createVBOs()
{
    makeCurrent();
    //Destroi os VBOs existentes
    destroyVBOs();

    //Cria vertices para montar a face==================================
    vertices = new QVector4D[4];

    vertices [0] = QVector4D ( -1, -1, 0, 1);
    vertices [1] = QVector4D (  1, -1, 0, 1);
    vertices [2] = QVector4D (  1,  1, 0, 1);
    vertices [3] = QVector4D ( -1,  1, 0, 1);

    //Cria dois triângulos para montar a face===========================
    indices = new unsigned int[2*3];
    indices[0]=0; indices[1]=1; indices[2]=2;
    indices[3]=2; indices[4]=3; indices[5]=0;
    //==================================================================

    //Define coordenadas da textura=====================================
    coordText = new QVector2D[4];
    coordText[3]= QVector2D(0,0);
    coordText[2]= QVector2D(1,0);
    coordText[1]= QVector2D(1,1);
    coordText[0]= QVector2D(0,1);
    //==================================================================

    shaderProgram->bind();

    //Cria o VAO========================================================
    vao = new QOpenGLVertexArrayObject () ;
    vao -> create () ;
    vao -> bind () ;

    //Transefere os Vértices para a GPU=================================
    vboVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboVertices ->create();
    vboVertices ->bind();
    vboVertices ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboVertices ->allocate(vertices , 4 *sizeof(QVector4D));

    shaderProgram->enableAttributeArray("vPosition");
    shaderProgram->setAttributeBuffer("vPosition",GL_FLOAT, 0,4,0);

    vboVertices->release();
    delete vertices;
    vertices = NULL;
    //==================================================================

    //Transfere as coordenadas da textura para a GPU====================
    vbocoordText = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbocoordText ->create();
    vbocoordText ->bind();
    vbocoordText ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbocoordText ->allocate(coordText, 4*sizeof(QVector2D));

    shaderProgram->enableAttributeArray("vcoordText");
    shaderProgram->setAttributeBuffer("vcoordText",GL_FLOAT, 0,2,0);

    vbocoordText ->release();
    delete coordText;
    coordText = NULL;
    //==================================================================    

    //Transfere a face para GPU=========================================
    vboIndices =new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vboIndices ->create();
    vboIndices ->bind();
    vboIndices ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboIndices ->allocate(indices , 2 * 3 *sizeof(unsigned int));

    vboIndices ->release();
    delete [] indices;
    indices = NULL;
    //==================================================================

    vao->release();
    shaderProgram->release();
}
//======================================================================

//Modifica a imagem exibida. Vale para imagens e video
void OpenGLWidget::setImage(QImage *img)
{
    makeCurrent();
    if(img==NULL) return;

    imgOrig = img;
    update();
}
//======================================================================

//Atualiza a textura exibida
void OpenGLWidget::updateTexture()
{
    if(colorTexture){
        delete colorTexture;
    }

    //Cria a Textura a partir da imagem=================================
    colorTexture = new QOpenGLTexture(*imgOrig);
    colorTexture->bind();
    colorTexture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    colorTexture->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::MirroredRepeat);
    colorTexture->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::MirroredRepeat);

    shaderProgram->bind();
    shaderProgram->setUniformValue("colorTexture", 0);
    // testando isso
    shaderProgram->setUniformValue("slider", slider);
    shaderProgram->setUniformValue("controler", controler);
    shaderProgram->setUniformValue("width", width);
    shaderProgram->setUniformValue("height", height);
    shaderProgram->release();
    //==================================================================
}
//======================================================================

//PaintGL
void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    makeCurrent();

    if(!imgOrig) return;

    updateTexture();

    shaderProgram->bind();
    vao->bind();

    colorTexture->bind();
    vboIndices->bind();
    glDrawElements(GL_TRIANGLES,2*3,GL_UNSIGNED_INT,0);
    vboIndices->release();
    colorTexture->release();

    vao->release();
    shaderProgram->release();
}
//======================================================================


//Modifica shader com base na lista da combobox
void OpenGLWidget::changeShader(int shader)
{
    currentShader = shader;
    qDebug() << shader;

    createShaders();
    createVBOs();
    update();
}
//======================================================================

void OpenGLWidget :: updateSlider(){
    QSlider* sliderWidget = parent()->findChild<QSlider*>("horizontalSlider");
    slider = sliderWidget->value();
    update();
}

void OpenGLWidget :: passValue(int value){
    controler = value;
    update();
}
