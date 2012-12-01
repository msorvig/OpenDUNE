#include <QtGui/QtGui>

#ifdef QT_BUILD

class DuneWidnow : public QWindow
{

};

extern "C" {
    extern int qt_main(int argc, char **argv);
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

    DuneWidnow window;
    window.resize(640, 480);
    window.setPosition(400, 400);
    window.show();

    DuneThread thread;
    thread.start();

    return app.exec();
}

#endif
