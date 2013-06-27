#ifndef __HELPER_H__
#define __HELPER_H__

#include <cstdlib>
#include <string>
#include <algorithm>

#include <QPoint>

using namespace std;

class Helper
{
public:
    static const QPoint& toPoint(const QPoint& point, int size);
    static const QPoint& toCoord(const QPoint& point, int size);
    static const QPoint& goToPoint(const string move);
    static const string pointToGo(const QPoint& point);
    static int d[2][4];
};

#endif
