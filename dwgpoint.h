#ifndef DWGPOINT_H
#define DWGPOINT_H

#include "dwgobject.h"

class DwgPoint : public DwgObject
{
    Q_OBJECT
public:
    explicit DwgPoint(QObject *parent = nullptr);

private:
    QPointF mpt;

    // DwgObject interface
public:
    virtual void Draw(QPainter *painter);
    virtual void SetData(QPointF pt1,QPointF pt2);
    virtual void SetPoint(QPointF ptpt);

public:
    virtual void Select(QPointF pt);
};

#endif // DWGPOINT_H
