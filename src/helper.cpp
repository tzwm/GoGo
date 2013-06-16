#include "helper.h"

const QPoint& Helper::toPoint(const QPoint& point, int size)
{
    float x = (float)point.x() / size +0.5;
    float y = (float)point.y() / size +0.5;
     
    return QPoint((int)x, (int)y);
}
