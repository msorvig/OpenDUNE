#include "opendune_qt.h"

#include <QtGui/QtGui>

#ifdef QT_BUILD

#include <signal.h>

// Globals
QMutex duneMutex;
QImage duneFrameBufferIndex8;
QVector<QRgb> dunePalette;
QImage duneFrameBuffer;
class DuneWindow;
DuneWindow *duneWindow;

DuneWindow::DuneWindow()
{
    backingStore = new QBackingStore(this);
    duneWindow = this;
}

DuneWindow::~DuneWindow()
{
    delete backingStore;
}

void DuneWindow::exposeEvent(QExposeEvent *)
{
    render();
}

void DuneWindow::resizeEvent(QResizeEvent *)
{
    render();
}

void DuneWindow::mousePressEvent(QMouseEvent *event)
{

}

void DuneWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void DuneWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void DuneWindow::keyPressEvent(QKeyEvent *event)
{

}

void DuneWindow::keyReleaseEvent(QKeyEvent *event)
{

}

void DuneWindow::render()
{
    qDebug() << "render";
    QRect rect(QPoint(), geometry().size());
    backingStore->resize(rect.size());
    backingStore->beginPaint(rect);
    QPaintDevice *device = backingStore->paintDevice();
    QPainter p(device);
    p.drawImage(rect, duneFrameBuffer);
    backingStore->endPaint();
    backingStore->flush(rect);
}


extern "C" {
    void qtLockMutex() { duneMutex.lock(); }
    void qtUnlockMutex() { duneMutex.unlock(); }

    void qtFramebufferUpdate(unsigned char *frameBuffer, int width, int height)
    {
        qDebug() << "qtFramebufferUpdate" << width << height;
        duneFrameBufferIndex8 = QImage(frameBuffer, width, height, QImage::Format_Indexed8);
        duneFrameBuffer = duneFrameBufferIndex8.convertToFormat(QImage::Format_ARGB32_Premultiplied, dunePalette);
        QMetaObject::invokeMethod(duneWindow, "render", Qt::QueuedConnection);
    }

    extern void qtPaletteUpdate(unsigned char *palette, int from, int length)
    {
        if (dunePalette.size() != 256)
            dunePalette.resize(256);

        qDebug() << "qtPaletteUpdate" << from << length;

        // ## que

        /*for (int i = from; i < from + length; i++) {
            dunePalette[i] = qRgb(
                        ((*palette+) & 0x3F) * 4,
                        ((*palette++) & 0x3F) * 4,
                        ((*palette++) & 0x3F) * 4);
        }*/
    }

    extern int qt_main(int argc, char **argv);  // opendune main entry point. Called by DuneThread below.
}
class DuneThread : public QThread
{
public:
    void run()
    {
        qDebug() << "Your battle for Dune begins...now.";
        char **argv;
        qt_main(0, argv);
    }
};

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    DuneWindow window;
    window.resize(640, 480);
    window.setPosition(400, 400);
    window.show();

    DuneThread thread;
    thread.start();


    // OpenDune implements times using SIGALRM. Prevent that signal
    // from being delivered to the Qt thread.
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    int s;
    s = pthread_sigmask(SIG_BLOCK, &set, NULL);
    if (s != 0)
        qDebug() << "pthread_sigmask error";

    return app.exec();
    thread.terminate();
}

#endif


