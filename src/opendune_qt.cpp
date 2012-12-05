#include "opendune_interface_qt.h"
#include "opendune_qt.h"

#include <QtGui/QtGui>
#include <QtMultimedia/QtMultimedia>

#ifdef QT_BUILD

#include <signal.h>

// Globals
QMutex duneMutex;
QVector<QRgb> dunePalette;
QImage duneFrameBuffer;
class DuneWindow;
DuneWindow *duneWindow = 0;
QQueue<DuneEvent> eventQueue;

QAudioOutput *output = 0;
QByteArray *qtSoundCopy = 0;
QBuffer *qtSoundBuffer = 0;


// Qt to DOS key translation
unsigned char translateKey(int qtKey)
{
    switch (qtKey) {
        case Qt::Key_Escape : return 0x1; break;

        case Qt::Key_1 : return 0x2; break;
        case Qt::Key_2 : return 0x3; break;
        case Qt::Key_3 : return 0x4; break;
        case Qt::Key_4 : return 0x5; break;
        case Qt::Key_5 : return 0x6; break;
        case Qt::Key_6 : return 0x7; break;
        case Qt::Key_7 : return 0x8; break;
        case Qt::Key_8 : return 0x9; break;
        case Qt::Key_9 : return 0xA; break;
        case Qt::Key_0 : return 0xB; break;

        case Qt::Key_Q : return 0x10; break;
        case Qt::Key_W : return 0x11; break;
        case Qt::Key_E : return 0x12; break;
        case Qt::Key_R : return 0x13; break;
        case Qt::Key_T : return 0x14; break;
        case Qt::Key_Y : return 0x15; break;
        case Qt::Key_U : return 0x16; break;
        case Qt::Key_I : return 0x17; break;
        case Qt::Key_O : return 0x18; break;
        case Qt::Key_P : return 0x19; break;

        case Qt::Key_A : return 0x1E; break;
        case Qt::Key_S : return 0x1F; break;
        case Qt::Key_D : return 0x20; break;
        case Qt::Key_F : return 0x21; break;
        case Qt::Key_G : return 0x22; break;
        case Qt::Key_H : return 0x23; break;
        case Qt::Key_J : return 0x24; break;
        case Qt::Key_K : return 0x25; break;
        case Qt::Key_L : return 0x26; break;

        case Qt::Key_Z : return 0x2C; break;
        case Qt::Key_X : return 0x2D; break;
        case Qt::Key_C : return 0x2E; break;
        case Qt::Key_V : return 0x2F; break;
        case Qt::Key_B : return 0x30; break;
        case Qt::Key_N : return 0x31; break;
        case Qt::Key_M : return 0x32; break;

        case Qt::Key_Up : return 0x48; break;
        case Qt::Key_Down : return 0x50; break;
        case Qt::Key_Left : return 0x4B; break;
        case Qt::Key_Right : return 0x4D; break;

        case Qt::Key_Enter : return 0x1C; break;

        default:
        break;
    }
    return 0;
}

// Mouse event translation
struct DuneEvent createDuneMouseEvent(QMouseEvent *event)
{
    DuneEvent duneEvent;
    duneEvent.isKeyEvent = false;
    duneEvent.mouseX = qMax(0, event->x() * duneFrameBuffer.width() / duneWindow->size().width());
    duneEvent.mouseY = qMax(0, event->y() * duneFrameBuffer.height() / duneWindow->size().height());
    duneEvent.leftButton = (event->buttons() & Qt::LeftButton);
    duneEvent.rightButton = (event->buttons() & Qt::RightButton);

//    qDebug() << "crate mouse event" << duneEvent.mouseX << duneEvent.mouseY << duneEvent.leftButton << duneEvent.rightButton;
    return duneEvent;
}

void updateFrameBuffer()
{
    duneFrameBufferIndex8.setColorTable(dunePalette);
    duneFrameBuffer = duneFrameBufferIndex8.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    QMetaObject::invokeMethod(duneWindow, "render", Qt::QueuedConnection);
}

// Dune Window implementation
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
    DuneEvent duneEvent = createDuneMouseEvent(event);
    qtLockMutex();
    eventQueue.enqueue(duneEvent);
    qtUnlockMutex();
}

void DuneWindow::mouseReleaseEvent(QMouseEvent *event)
{
    DuneEvent duneEvent = createDuneMouseEvent(event);
    qtLockMutex();
    eventQueue.enqueue(duneEvent);
    qtUnlockMutex();
}

void DuneWindow::mouseMoveEvent(QMouseEvent *event)
{
    DuneEvent duneEvent = createDuneMouseEvent(event);
    qtLockMutex();
    eventQueue.enqueue(duneEvent);
    qtUnlockMutex();
}

void DuneWindow::keyPressEvent(QKeyEvent *event)
{
    DuneEvent duneEvent;
    duneEvent.isKeyEvent = true;
    duneEvent.key = translateKey(event->key());
    duneEvent.isPress = true;
    qtLockMutex();
    eventQueue.enqueue(duneEvent);
    qtUnlockMutex();
}

void DuneWindow::keyReleaseEvent(QKeyEvent *event)
{
    DuneEvent duneEvent;
    duneEvent.isKeyEvent = true;
    duneEvent.key = translateKey(event->key());
    duneEvent.isPress = false;
    qtLockMutex();
    eventQueue.enqueue(duneEvent);
    qtUnlockMutex();
}

void DuneWindow::render()
{
    QRect rect(QPoint(), geometry().size());
    backingStore->resize(rect.size());
    backingStore->beginPaint(rect);
    QPaintDevice *device = backingStore->paintDevice();
    QPainter p(device);
    p.drawImage(rect, duneFrameBuffer);
    backingStore->endPaint();
    backingStore->flush(rect);
}

// opendune_interface.h implementation. These are called from
// the Dune thread.
extern "C" {
    void qtLockMutex() { duneMutex.lock(); }
    void qtUnlockMutex() { duneMutex.unlock(); }

    bool qtHasEvent()
    {
        return !eventQueue.isEmpty();
    }

    struct DuneEvent qtNextEvent()
    {
        return eventQueue.dequeue();
    }

    void qtFramebufferUpdate(unsigned char *frameBuffer, int width, int height)
    {
        duneFrameBufferIndex8 = QImage(frameBuffer, width, height, QImage::Format_Indexed8);
        updateFrameBuffer();
    }

    void qtPaletteUpdate(unsigned char *palette, int from, int length)
    {
        if (dunePalette.size() != 256)
            dunePalette.resize(256);

        for (int i = from; i < from + length; i++) {
            dunePalette[i] = qRgb(
                        ((*palette++) & 0x3F) * 4,
                        ((*palette++) & 0x3F) * 4,
                        ((*palette++) & 0x3F) * 4);
        }
        updateFrameBuffer();
    }

    void qtCreateSoundSystem()
    {
        QAudioFormat format = QAudioFormat();
        format.setSampleRate(11025);
        format.setSampleType(QAudioFormat::UnSignedInt);
        format.setSampleSize(8);
        format.setChannelCount(1);
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setCodec(QStringLiteral("audio/pcm"));

        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
        if (!info.isFormatSupported(format)) {
            qWarning() << "Default format not supported - trying to use nearest";
            format = info.nearestFormat(format);
        }

        if (!format.isValid())
            qWarning() << "sound format not valid" << format.isValid();

        output = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    }

    void qtDestroySoundSystem()
    {
        delete output;
    }

    void qtPlaySound(unsigned char *soundBuffer, int length, int frequency)
    {
        // qDebug() << "qtPlaySound" << length << frequency;
        qtSoundCopy = new QByteArray((const char *)soundBuffer, length);
        qtSoundBuffer = new QBuffer(qtSoundCopy);
        qtSoundBuffer->open(QIODevice::ReadOnly);
        output->start(qtSoundBuffer);
    }

    void qtStopSound()
    {
        output->stop();
        delete qtSoundCopy;
        qtSoundCopy = 0;
        delete qtSoundBuffer;
        qtSoundBuffer = 0;
    }

    bool qtIsPlaying()
    {
        return (output->state() & QAudio::ActiveState);
    }

    extern int qt_main(int argc, char **argv);  // opendune main entry point. Called by DuneThread below.
}

class DuneThread : public QThread
{
public:
    void run()
    {
        qDebug() << "Your battle for Dune begins...now.";
        char **argv = 0;
        qt_main(0, argv);
    }
};

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    qApp->setOverrideCursor( QCursor( Qt::BlankCursor ) );

    // Create Dune Window
    DuneWindow window;
    window.resize(640, 480);
    window.setPosition(400, 400);
    window.show();

    // Start Dune thread
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
    thread.terminate(); // pull the rug
}

#endif


