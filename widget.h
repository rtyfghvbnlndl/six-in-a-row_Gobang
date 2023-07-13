#ifndef WIDGET_H
#define WIDGET_H

#include <qpixmap.h>
#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QPointF>
#include <box.h>
#include <qstring.h>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    void restart();
    int isFinshed = -1;
    box cb = box(500, 500, ONE_POINT_SIZE);
    QPixmap black;
    QPixmap white;
    QPushButton* restart_btn;
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

