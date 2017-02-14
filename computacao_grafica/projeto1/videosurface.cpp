#include "videosurface.h"

//Construtor
VideoSurface::VideoSurface( QObject *parent) : QAbstractVideoSurface(parent)
{
    rgbs = NULL;
    yuvs = NULL;
}

//Método chamado pelo player ou camera para exibir frame a frame da fonte na video surface
bool VideoSurface::present(const QVideoFrame& frame)
{
    if(frame.isValid()){

        QVideoFrame videoFrame(frame);
        QImage *img = NULL;

        //Mapeia o frame obtido atual
        if(videoFrame.map(QAbstractVideoBuffer::ReadOnly)){

            const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());

            //Verifica se o formato de codificação é válido, se sim gera imagem se não ajusta
            if(imageFormat == QImage::Format_Invalid){

                 //Ajusta o formato do antigo YUV para RGB
                if(frame.pixelFormat()==QVideoFrame::Format_YUV420P){

                    if(rgbs != NULL) delete rgbs;
                    if(yuvs != NULL) delete yuvs;

                    yuvs = videoFrame.bits();
                    int width  = videoFrame.width();
                    int height = videoFrame.height();

                    rgbs = new uchar[videoFrame.bytesPerLine()*videoFrame.height()*3];
                    int outPtr = 0;
                    int size = width * height;

                    //Percorre a matriz do frame convertendo os valores YUV para as componentes RGB
                    for(int i=0;i<height;i++){
                        for(int j=0;j<width;j++){
                            //Identifica valores de luminancia e crominancia
                            int Y = ((char)yuvs[i * width + j] & 0xff) ;
                            int Cr = ((char)yuvs[((i/2)*(width/2))+(j/2)+size] & 0xff) - 128;
                            int Cb = ((char)yuvs[((i/2)*(width/2))+(j/2)+size+(size/4)] & 0xff) - 128;
                            int R, G, B;
                            int C = Y-16;
                            int D = Cr;
                            int E = Cb;

                            //Gera as componentes RGB
                            B=((298*C)+(516*D)+128)>>8;
                            if(B < 0) B = 0;
                            else if(B > 255) B = 255;

                            G= ((298*C)-(100*D)-(208*E)+128)>>8;
                            if(G < 0) G = 0;
                            else if(G > 255) G = 255;

                            R=((C*298)+(E*409)+128) >>8;
                            if(R < 0) R = 0;
                            else if(R > 255) R = 255;

                            //Assumindo que a codificação little-endian
                            rgbs[outPtr++] = (uchar)R;
                            rgbs[outPtr++] = (uchar)G;
                            rgbs[outPtr++] = (uchar)B;
                        }
                    }
                    //Cria imagem com o formato RGB de canais
                    img = new QImage(rgbs,width,height, QImage::Format_RGB888);
                }
            }
            else{
                img =new QImage (frame.bits(),frame.width(),frame.height(),frame.bytesPerLine(),imageFormat);
            }
        }
        //Verifica se obteve imagem e avisa OpenGLWidget para atualizar
        if(img != NULL)
            emit signalSendImage(img);
        videoFrame.unmap();
    }
    return true;
}

//Ajuste no método isFormatSupported para validar o formato do vídeo se é RGB
bool VideoSurface::isFormatSupported(const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const
{
     Q_UNUSED(similar);

     QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
     QSize size = format.frameSize();

     return imageFormat != QImage::Format_Invalid
             && !size.isEmpty()
             && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

//Devolve os formatos suportados, RGB
QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const{
    return QList<QVideoFrame::PixelFormat>()
            << QVideoFrame::Format_RGB32
            << QVideoFrame::Format_ARGB32;
}
