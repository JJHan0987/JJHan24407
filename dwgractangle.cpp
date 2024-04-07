#include "dwgractangle.h"
#include <QtMath>

DwgRactangle::DwgRactangle(QObject *parent)
    : DwgObject{parent}
{}


void DwgRactangle::Draw(QPainter *painter)
{
    if(mDeleteed) return;
    if(mSelected)
    {
        painter->setPen(Qt::red);
    }
    painter->drawRect(mx,my,mWidth,mHeight);
    painter->setPen(Qt::black);
}

void DwgRactangle::SetData(QPointF pt1, QPointF pt2)
{
    mx = pt1.x();
    my = pt1.y();
    mWidth = pt2.x()-pt1.x();
    mHeight = pt2.y()-pt1.y();
}

void DwgRactangle::SetPoint(QPointF pt)
{}

void DwgRactangle::Select(QPointF pt)
{
    qreal dist = fabs(pt.x() - mx) + fabs(pt.x() - (mx + mWidth)) + fabs(pt.y() - my) + fabs(pt.y() - (my + mHeight));
    if(dist > (mWidth+mHeight))
        mSelected = true;
}
