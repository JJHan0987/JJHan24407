#ifndef DWGLINE_H
#define DWGLINE_H

#include "dwgobject.h"

class DwgLine : public DwgObject
{
    Q_OBJECT
public:
    explicit DwgLine(QObject *parent = nullptr);

private:
    QPointF mStartPt,mEndPt;

    // DwgObject interface
public:
    virtual void Draw(QPainter *painter);
    virtual void SetData(QPointF pt1,QPointF pt2);
    virtual void SetPoint(QPointF pt);

    // DwgObject interface
public:
    virtual void Select(QPointF pt);
};

#endif // DWGLINE_H
