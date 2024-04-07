#include "dwgcircle.h"
#include <QtMath>

DwgCircle::DwgCircle(QObject *parent)
    : DwgObject{parent}
{

}

void DwgCircle::SetData(QPointF pt1, QPointF pt2)
{
    mCenPt = pt1;
    mRad = qSqrt((pt2.x()-pt1.x())*(pt2.x()-pt1.x())+
                 (pt2.y()-pt1.y())*(pt2.y()-pt1.y()));

}

void DwgCircle::SetPoint(QPointF pt)
{}

void DwgCircle::Draw(QPainter *painter)
{
    if(mDeleteed) return;
    if(mSelected)
    {
        painter->setPen(Qt::red);
    }
    painter->drawEllipse(mCenPt,mRad,mRad);
    painter->drawLine(mCenPt.x()-2,mCenPt.y(),mCenPt.x()+2,mCenPt.y());
    painter->drawLine(mCenPt.x(),mCenPt.y()-2,mCenPt.x(),mCenPt.y()+2);

    painter->setPen(Qt::black);
}

void DwgCircle::Select(QPointF pt)
{
    qreal dist = sqrt((pt.x()-mCenPt.x())*(pt.x()-mCenPt.x())
                      +(pt.y()-mCenPt.y())*(pt.y()-mCenPt.y()));
    if(fabs(dist-mRad) < 3)
        mSelected = true;
}
