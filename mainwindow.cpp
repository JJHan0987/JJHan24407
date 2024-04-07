#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "QRibbon.h"
#include <QDebug>
#include <QPainter>
//#include <QMouseEvent>
#include <QtMath>

#include "dwgpoint.h"
#include "dwgline.h"
#include "dwgcircle.h"
#include "dwgractangle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    QRibbon::install(this);
    //    this->show();
    m_trans.reset();
    m_trans.translate(0,this->height());
    m_trans.scale(1,-1);

    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete mpainter;
}

void MainWindow::on_actionPoint_triggered()
{
    mCurDrawType = DPoint;
    mCurModifyType = MNone;
    this->setCursor(Qt::CrossCursor);
}


void MainWindow::on_actionLine_triggered()
{
    mCurDrawType = DLine;
    mCurModifyType = MNone;
    this->setCursor(Qt::CrossCursor);

}
void MainWindow::on_actionCircle_triggered()
{
    mCurDrawType = DCircle;
    mCurModifyType = MNone;
    this->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionRectangle_triggered()
{
    mCurDrawType = DRectangle;
    mCurModifyType = MNone;
    this->setCursor(Qt::CrossCursor);
}

bool isFirst = true;
QPoint temppt;
QPoint movept;
QPointF firstpt, lastpt;

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    movept = event->pos();
    if(event->buttons() & Qt::LeftButton)
    {
        if(mCurDrawType == DPoint)
        {
            DwgPoint *point = new DwgPoint;            // 创建并初始化一个直线对象
            QPointF pt = m_trans.inverted().map(event->pos());
            point->SetPoint(pt);		// 使用SetData函数设置私有成员变量
            m_mainlist.append(point);				// append函数用于把对象添加到数组mLines中
            update();						// 该函数用于刷新窗口
        }
        if(mCurDrawType == DLine)
        {
            if(isFirst)
            {
                temppt = event->pos();
                firstpt = temppt;
                isFirst = false;
            }
            else
            {
                DwgLine *line = new DwgLine;            // 创建并初始化一个直线对象
                QPointF pt1 = m_trans.inverted().map(temppt);
                QPointF pt2 = m_trans.inverted().map(event->pos());
                line->SetData(pt1,pt2);		// 使用SetData函数设置私有成员变量
                m_mainlist.append(line);				// append函数用于把对象添加到数组mLines中
                update();						// 该函数用于刷新窗口
                isFirst = true;
            }
        }
        if(mCurDrawType == DCircle)
        {
            if(isFirst)
            {
                temppt = event->pos();
                firstpt = temppt;
                isFirst = false;
            }
            else
            {
                DwgCircle *circle = new DwgCircle;            // 创建并初始化一个直线对象

                QPointF pt1 = m_trans.inverted().map(temppt);
                QPointF pt2 = m_trans.inverted().map(event->pos());
                circle->SetData(pt1,pt2);		// 使用SetData函数设置私有成员变量
                m_mainlist.append(circle);                     // append函数用于把对象添加到数组mLines中
                update();                                   // 该函数用于刷新窗口
                isFirst = true;
            }
        }
        if(mCurDrawType == DRectangle)
        {
            if(isFirst)
            {
                temppt = event->pos();
                firstpt = temppt;
                isFirst = false;
            }
            else
            {
                DwgRactangle *rectangle = new DwgRactangle;            // 创建并初始化一个直线对象

                QPointF pt1 = m_trans.inverted().map(temppt);
                QPointF pt2 = m_trans.inverted().map(event->pos());
                rectangle->SetData(pt1,pt2);		// 使用SetData函数设置私有成员变量
                m_mainlist.append(rectangle);                     // append函数用于把对象添加到数组mLines中
                update();                                   // 该函数用于刷新窗口
                isFirst = true;
            }
        }
        if(mCurModifyType == MSelect)
        {
            QPointF spt = m_trans.inverted().map(event->pos());
            foreach (auto i, m_mainlist) {
                i->Select(spt);
            }
            update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    mpainter = new QPainter(this);
    mpainter->save();

    if(!(firstpt.isNull() || lastpt.isNull()) && !isFirst)
    {
        QPen pen1;
        pen1.setColor(QColor(125,0,0));
        pen1.setWidth(2);
        pen1.setStyle(Qt::DashLine);
        mpainter->setPen(pen1);

        if(mCurDrawType == DLine)
            mpainter->drawLine(firstpt,lastpt);
        if(mCurDrawType == DCircle)
        {
            qreal rad = sqrt((firstpt.x()-lastpt.x())*(firstpt.x()-lastpt.x())
                             +(firstpt.y()-lastpt.y())*(firstpt.y()-lastpt.y()));

            mpainter->drawEllipse(firstpt.x()-rad,firstpt.y()-rad,rad*2,rad*2);
        }
        if(mCurDrawType == DRectangle)
        {
            mpainter->drawRect(firstpt.x(),firstpt.y(),lastpt.x()-firstpt.x(),lastpt.y()-firstpt.y());
        }
        pen1.setColor(Qt::black);
        pen1.setStyle(Qt::SolidLine);
    }

    QPen pen;
    pen.setCosmetic(true);      // 该函数用于保持缩放时的线宽为1个像素，而不会随着缩放而变化
    mpainter->setPen(pen);

    mpainter->setWorldTransform(m_trans,true);        // 设置painter的绘制矩阵为系统的变换矩阵mtrans

    foreach (auto i, m_mainlist) {
        i->Draw(mpainter);
    }

    pen.setCosmetic(false);
    mpainter->setPen(pen);
    mpainter->restore();

    delete mpainter;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionSelect_triggered()
{
    mCurModifyType = MSelect;
    mCurDrawType = DNone;
    this->setCursor(Qt::SizeAllCursor);
}


void MainWindow::on_actionDelete_triggered()
{
    this->setCursor(Qt::ArrowCursor);
    foreach(auto i , m_mainlist)
    {
        if(i->mSelected)
            i->mDeleteed = true;
    }
    update();
}



void MainWindow::wheelEvent(QWheelEvent *event)
{
    m_winScale = m_winScale +(event->angleDelta().y()/120.0/10);

    qreal winScale = 1+event->angleDelta().y()/120.0/10;
    QTransform trans1,trans2,trans3;
    trans1.translate(-event->position().x(),-event->position().y());
    trans2.scale(winScale,winScale);
    trans3.translate(event->position().x(),event->position().y());
    m_trans = m_trans*trans1*trans2*trans3;

    qDebug() <<  m_trans;
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!movept.isNull())
        if(event->buttons() & Qt::MiddleButton)
            m_trans.translate(event->pos().x()-movept.x(),
                              movept.y()-event->pos().y());

    movept = event->pos();

    if(!isFirst)
    {
        lastpt = event->pos();
    }
    update();
    QMainWindow::mouseMoveEvent(event);
}




