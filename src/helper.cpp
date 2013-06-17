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

int Helper::d[2][4] = {{-1, 1, 0, 0}, {0, 0, -1, 1}};
