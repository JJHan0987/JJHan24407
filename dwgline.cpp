#include "dwgline.h"
#include <QtMath>

DwgLine::DwgLine(QObject *parent)
    : DwgObject{parent}
{

}

void DwgLine::SetData(QPointF pt1, QPointF pt2)
{
    mStartPt = pt1,mEndPt = pt2;
}

void DwgLine::SetPoint(QPointF pt)
{}


void DwgLine::Draw(QPainter *painter)
{
    if(mDeleteed) return;
    if(mSelected)
    {
        painter->setPen(Qt::red);
    }
    painter->drawLine(mStartPt,mEndPt);
    painter->setPen(Qt::black);
}


void DwgLine::Select(QPointF pt)
{
    qreal Length,dist2,dist1;
    Length = sqrt((mStartPt.x()-mEndPt.x())*(mStartPt.x()-mEndPt.x()) +
                  (mStartPt.y()-mEndPt.y())*(mStartPt.y()-mEndPt.y()));
    dist1 = sqrt((mStartPt.x()-pt.x())*(mStartPt.x()-pt.x()) +
                 (mStartPt.y()-pt.y())*(mStartPt.y()-pt.y()));
    dist2 = sqrt((pt.x()-mEndPt.x())*(pt.x()-mEndPt.x()) +
                 (pt.y()-mEndPt.y())*(pt.y()-mEndPt.y()));

    if(fabs(Length -(dist1+dist2)) < 3.0)
        mSelected = true;
}
