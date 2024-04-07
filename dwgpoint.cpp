#include "dwgpoint.h"
#include <QtMath>

DwgPoint::DwgPoint(QObject *parent)
    : DwgObject{parent}
{}

void DwgPoint::SetPoint(QPointF ptpt)
{
    mpt = ptpt;
}

void DwgPoint::Select(QPointF pt)
{
    qreal dist = sqrt((pt.x()-mpt.x())*(pt.x()-mpt.x())
                      +(pt.y()-mpt.y())*(pt.y()-mpt.y()));
    if(fabs(dist) < 3)
        mSelected = true;
}

void DwgPoint::Draw(QPainter *painter)
{
    if(mDeleteed) return;
    if(mSelected)
    {
        painter->setPen(Qt::red);
    }
    painter->drawLine(mpt.x()-2,mpt.y(),mpt.x()+2,mpt.y());
    painter->drawLine(mpt.x(),mpt.y()-2,mpt.x(),mpt.y()+2);

    painter->setPen(Qt::black);
}

void DwgPoint::SetData(QPointF pt1, QPointF pt2)
{}

