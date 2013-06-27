#include "helper.h"

const QPoint& Helper::toPoint(const QPoint& point, int size)
{
    float x = (float)point.x() / size +0.5;
    float y = (float)point.y() / size +0.5;
     
    return QPoint((int)x -1, (int)y -1);
}


const QPoint& Helper::toCoord(const QPoint& point, int size)
{
    int x = (point.x()+1) * size;
    int y = (point.y()+1) * size;
    
    return QPoint(x -size*10, y -size*10);
}

const QPoint& Helper::goToPoint(const string move)
{
    string tmp = move;
    int x = int(tmp[0]) - int('A');
    if(x > 7)
        x--;

    tmp.erase(0, 1);
    int y = atoi(tmp.c_str());
    y = 19 - y;

    return QPoint(x, y);
}

const string Helper::pointToGo(const QPoint& point)
{
    string tmp = "";
    int x = point.x();
    if(x > 7)
        x++;
    int y = 19 - point.y();

    tmp += char(x+int('A'));
    string yy;
    while(y)
    {
        yy += char(y%10 + int('0'));
        y = y/10;
    }
    reverse(yy.begin(), yy.end()); 
    tmp += yy;
    
    return tmp;
}

int Helper::d[2][4] = {{-1, 1, 0, 0}, {0, 0, -1, 1}};
