#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QObject>
#include <QVideoFrame>
#include <QAbstractVideoSurface>
#include <QAbstractVideoBuffer>
#include <QList>
#include <QDebug>
#include <QImage>
#include <QSize>
#include <QVideoSurfaceFormat>

class VideoSurface : public QAbstractVideoSurface
{
     Q_OBJECT

public:
    explicit VideoSurface(QObject *parent = 0);
    bool present(const QVideoFrame& frame);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const;
    QImage *img;
public slots:

signals:
    void signalSendImage(QImage *img);

private:
    uchar *rgbs;
    uchar *yuvs;
};

#endif // VIDEOSURFACE_H
