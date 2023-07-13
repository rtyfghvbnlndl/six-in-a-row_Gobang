#include "box.h"
#include <QDebug>

box::box(int x, int y, int a, QObject *parent):
    QObject{parent},
    round(0),
    a(a){
    _x = x/a;
    _y = y/a;
    maxsize = _x*_y;
    pdata = new point[maxsize];
    int k = 0;
    for(int i=0; i<_x; i++){
        for(int j=0; j<_y; j++){
            pdata[k].x = i*a;
            pdata[k].y = j*a;
            qDebug() << pdata[k].x<<pdata[k].y<<pdata[k].piece<<i<<j;
            k++;
        }
    }
    qDebug() <<"kshndkjshs";
}

point box::makePoint(QPointF qpoint){
    point result;
    result.x = qpoint.x()/a;
    result.y = qpoint.y()/a;
    return result;
}

bool box::movePiece(QPointF qpoint){
    point p = makePoint(qpoint);
    int num = findPoint(p);
    if(pdata[num].piece==-1){
        pdata[num].piece = round;
        round = !round;
        return true;
    }
    return false;
}

int box::findPoint(point p){
    return p.x*_x+p.y;
}

int box::isAnyoneWin(){
    int tmp, count, j;
    //竖着穷举
    for(int i=0; i<_x; i++){
        tmp = -1;
        count = 0;
        j = i;
        while(1){
            if(tmp==pdata[j].piece&&pdata[j].piece!=-1){
                count++;
            }
            else{
                tmp = pdata[j].piece;
                count = 1;
            }
            if(count == WIN_LENGTH){
                return tmp;
            }
            try{
                j = down(j);
            }catch(std::invalid_argument){
                break;
            }
        }
    }
    //横着穷举
    for(int i=0; i<maxsize; i+=_x){
        tmp = -1;
        count = 0;
        j = i;
        while(1){
            if(tmp==pdata[j].piece&&pdata[j].piece!=-1){
                count++;
            }
            else{
                tmp = pdata[j].piece;
                count = 1;
            }
            if(count == WIN_LENGTH){
                return tmp;
            }
            try{
                j = right(j);
            }catch(std::invalid_argument){
                break;
            }
        }
    }
    //向右下
    for(int i=0; i<_x; i++){
        tmp = -1;
        count = 0;
        j = i;
        while(1){
            if(tmp==pdata[j].piece&&pdata[j].piece!=-1){
                count++;
            }
            else{
                tmp = pdata[j].piece;
                count = 1;
            }
            if(count == WIN_LENGTH){
                return tmp;
            }
            try{
                j = lowerRight(j);
            }catch(std::invalid_argument){
                break;
            }
        }
    }
    for(int i=0; i<maxsize; i+=_x){
        tmp = -1;
        count = 0;
        j = i;
        while(1){
            if(tmp==pdata[j].piece&&pdata[j].piece!=-1){
                count++;
            }
            else{
                tmp = pdata[j].piece;
                count = 1;
            }
            if(count == WIN_LENGTH){
                return tmp;
            }
            try{
                j = lowerRight(j);
            }catch(std::invalid_argument){
                break;
            }
        }
    }
    //向左下
    for(int i=0; i<_x; i++){
        tmp = -1;
        count = 0;
        j = i;
        while(1){
            if(tmp==pdata[j].piece&&pdata[j].piece!=-1){
                count++;
            }
            else{
                tmp = pdata[j].piece;
                count = 1;
            }
            if(count == WIN_LENGTH){
                return tmp;
            }
            try{
                j = lowerLeft(j);
            }catch(std::invalid_argument){
                break;
            }
        }
    }
    for(int i=_x-1; i<=maxsize; i+=_x){
        tmp = -1;
        count = 0;
        j = i;
        while(1){
            if(tmp==pdata[j].piece&&pdata[j].piece!=-1){
                count++;
            }
            else{
                tmp = pdata[j].piece;
                count = 1;
            }
            if(count == WIN_LENGTH){
                return tmp;
            }
            try{
                j = lowerLeft(j);
            }catch(std::invalid_argument){
                break;
            }
        }
    }
    return -1;
}

int box::right(int p){
    if(p+1<p/_x*_x+_x){
        return ++p;
    }
    throw std::invalid_argument("out of range!");
}

int box::left(int p){
    if(p-1>=p/_x*_x){
        return --p;
    }
    throw std::invalid_argument("out of range!");
}

int box::down(int p){
    p = p+_x;
    if(p<maxsize){
        return p;
    }
    throw std::invalid_argument("out of range!");
}

int box::lowerRight(int p){
    return down(right(p));
}

int box::lowerLeft(int p){
    return down(left(p));
}
