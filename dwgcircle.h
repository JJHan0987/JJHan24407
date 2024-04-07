#ifndef DWGCIRCLE_H
#define DWGCIRCLE_H

#include "dwgobject.h"

class DwgCircle : public DwgObject
{
    Q_OBJECT
public:
    explicit DwgCircle(QObject *parent = nullptr);

private:
    QPointF mCenPt;
    qreal mRad;

    // DwgObject interface
public:
    virtual void Draw(QPainter *painter);
    virtual void SetData(QPointF pt1,QPointF pt2);
    virtual void SetPoint(QPointF pt);

    // DwgObject interface
public:
    virtual void Select(QPointF pt);
};

#endif // DWGCIRCLE_H
