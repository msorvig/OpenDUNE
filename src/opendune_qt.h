#include <QtGui/QtGui>

#ifdef QT_BUILD

class DuneWindow : public QWindow
{
    Q_OBJECT
public:
    DuneWindow();
    ~DuneWindow();
    void exposeEvent(QExposeEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    Q_INVOKABLE void render();
    QBackingStore *backingStore;
    QImage frameBuffer;
};

#endif
