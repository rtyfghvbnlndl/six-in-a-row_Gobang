#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    black.load(":./res/black.png");
    black = black.scaled(ONE_POINT_SIZE, ONE_POINT_SIZE, Qt::KeepAspectRatio);
    white.load(":./res/white.png");
    white = white.scaled(ONE_POINT_SIZE, ONE_POINT_SIZE, Qt::KeepAspectRatio);
    resize(WINDOWS_SIZE,WINDOWS_SIZE);

    restart_btn = new QPushButton("重新开始",this);
    restart_btn->resize(120,40);
    restart_btn->move(WINDOWS_SIZE/2-60,WINDOWS_SIZE/2+40);
    restart_btn->hide();
    connect(restart_btn, &QPushButton::clicked, this, &Widget::restart);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for(int i=0; i<cb.maxsize; i++){
        if(cb.pdata[i].piece!=-1){
            if(cb.pdata[i].piece){
                painter.drawPixmap(cb.pdata[i].x,cb.pdata[i].y,white);
            }
            else{
                painter.drawPixmap(cb.pdata[i].x,cb.pdata[i].y,black);
            }
            //qDebug() << cb.pdata[i].piece <<cb.pdata[i].x <<cb.pdata[i].y;
        }
    }

    if(isFinshed!=-1){
        qDebug() << "Finished!" << isFinshed;
        QFont font = painter.font();
        font.setPixelSize(20);
        painter.setFont(font);

        const QRect rectangle = QRect(WINDOWS_SIZE/2-40, WINDOWS_SIZE/2-10, WINDOWS_SIZE/2+40, WINDOWS_SIZE/2+10);
        painter.setPen(QPen(Qt::red,20));
        if(isFinshed){
            painter.drawText(rectangle,"白子赢了");
        }
        else{
            painter.drawText(rectangle,"黑子赢了");
        }
        restart_btn->show();
    }
}
void Widget::mousePressEvent(QMouseEvent *event){
    if(isFinshed==-1){
        QPointF qpoint = event->position();
        cb.movePiece(qpoint);
        isFinshed = cb.isAnyoneWin();
        //qDebug() << qpoint.x();
    }
    update();
}

void Widget::restart(){
    for(int i=0; i<cb.maxsize; i++){
        cb.pdata[i].piece = -1;
    }
    isFinshed = -1;
    restart_btn->hide();
    update();
}

Widget::~Widget()
{
    delete ui;
}

