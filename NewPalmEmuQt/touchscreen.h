#include <QLabel>
#include <QMouseEvent>
#include <QTouchEvent>
#ifndef TOUCHSCREEN
#define TOUCHSCREEN

class TouchScreen : public QLabel
{
Q_OBJECT
public:
    explicit TouchScreen(QWidget* parent=0 );
    ~TouchScreen();
protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

	//void touchReleaseEvent(QTouchEvent* ev);
};

#endif // TOUCHSCREEN

