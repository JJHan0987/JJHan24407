#ifndef DWGRACTANGLE_H
#define DWGRACTANGLE_H

#include "dwgobject.h"

class DwgRactangle : public DwgObject
{
    Q_OBJECT
public:
    explicit DwgRactangle(QObject *parent = nullptr);

private:
    qreal mx,my,mWidth,mHeight;

    // DwgObject interface
public:
    virtual void Draw(QPainter *painter);
    virtual void SetData(QPointF pt1, QPointF pt2);
    virtual void SetPoint(QPointF pt);

public:
    virtual void Select(QPointF pt);
};

#endif // DWGRACTANGLE_H
