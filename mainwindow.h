#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dwgobject.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum DrawType
{
    DNone,
    DPoint,
    DLine,
    DCircle,
    DRectangle,
    DPolyLine,
    DSDLine
};
enum ModifyType
{
    MNone,
    MSelect,
    MDelete
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<DwgObject *> m_mainlist ;
    QPainter * mpainter = nullptr;
    DrawType mCurDrawType = DNone;
    ModifyType mCurModifyType = MNone;
    qreal m_winScale = 1.0;
    QTransform m_trans;

private slots:
    void on_actionPoint_triggered();
    void on_actionLine_triggered();
    void on_actionCircle_triggered();
    void on_actionExit_triggered();
    void on_actionSelect_triggered();
    void on_actionDelete_triggered();
    void on_actionRectangle_triggered();

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    virtual void wheelEvent(QWheelEvent *event);

    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
