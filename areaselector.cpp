#include "areaselector.h"
#include <QCursor>
#include <QDebug>
#include<QGuiApplication>
#include <QScreen>

int min(int a, int b) { return a<b ? a : b; }
int max(int a, int b) { return a>b ? a : b; }

AreaSelector::AreaSelector(QWidget *parent) : QDialog(parent)
{
    installEventFilter(this);
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowState(windowState() | Qt::WindowFullScreen);
    setWindowOpacity(30);

    QScreen* scr  = QGuiApplication::primaryScreen();
    setFixedSize(scr->virtualSize());

    offset_x = scr->virtualGeometry().topLeft().x();
    offset_y = scr->virtualGeometry().topLeft().y();
    move(offset_x, offset_y);

    setCursor(Qt::CrossCursor);

    exec();
}

AreaSelector::~AreaSelector()
{
}

void AreaSelector::mousePressEvent(QMouseEvent *event)
{
    start = QCursor::pos();
}

void AreaSelector::mouseMoveEvent(QMouseEvent *event)
{

}

void AreaSelector::mouseReleaseEvent(QMouseEvent *event)
{
    end = QCursor::pos();

    int leftmost = min(start.x(), end.x());
    int rightmost = max(start.x(), end.x());
    int topmost = min(start.x(), end.x());
    int botmost = max(start.x(), end.x());

    area = QRect(QPoint(leftmost, topmost), QPoint(rightmost, botmost));

    close();
}
