#ifndef DWGOBJECT_H
#define DWGOBJECT_H

#include <QColor>
#include <QObject>
#include <QPainter>


class DwgObject : public QObject
{
    Q_OBJECT
public:
    explicit DwgObject(QObject *parent = nullptr);
    ~DwgObject() {};

    virtual void Draw(QPainter * painter) = 0;
    virtual void SetData(QPointF pt1,QPointF pt2) = 0;
    virtual void SetPoint(QPointF ptpt) = 0;
    virtual void Select(QPointF pt) = 0;
    bool mSelected = false;
    bool mDeleteed = false;

private:
    int mLineWidth = 0;
    QColor mLineColor = Qt::black;

signals:

};

#endif // DWGOBJECT_H
