#ifndef BOX_H
#define BOX_H
#include <QPointF>
#include <QDebug>
#include <QObject>
#define ONE_POINT_SIZE 25
#define WINDOWS_SIZE 500
#define WIN_LENGTH 6
#include <QPushButton>

typedef struct point{
    int x;
    int y;
    int piece = -1;
} point;
class box : public QObject
{
    Q_OBJECT
public:

    int maxsize=0;
    point* pdata;
    explicit box(int x, int y, int a, QObject *parent = nullptr);
    //判断点击的位置
    bool round;
    point makePoint(QPointF qpoint);
    bool movePiece(QPointF qpoint);
    int findPoint(point p);
    int isAnyoneWin();
    void restart();

    int a;
private:
    int _x;
    int _y;

    int right(int p);
    int left(int p);
    int down(int p);
    int lowerRight(int p);
    int lowerLeft(int p);
signals:

};

#endif // BOX_H
