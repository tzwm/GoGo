#ifndef __HELPER_H__
#define __HELPER_H__

#include <QPoint>

class Helper
{
public:
    static const QPoint& toPoint(const QPoint& point, int size);
    static const QPoint& toCoord(const QPoint& point, int size);
};

#endif
