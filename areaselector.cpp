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
    setWindowOpacity(0.2);

    QScreen* scr  = QGuiApplication::primaryScreen();
    setFixedSize(scr->virtualSize());

    offset_x = scr->virtualGeometry().topLeft().x();
    offset_y = scr->virtualGeometry().topLeft().y();
    move(offset_x, offset_y);

    setCursor(Qt::CrossCursor);

}

AreaSelector::AreaSelector(QPixmap pm, QWidget *parent) : QDialog(parent)
{
    installEventFilter(this);
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowState(windowState() | Qt::WindowFullScreen);
    setWindowOpacity(1);

    setFixedSize(pm.size());

//    offset_x = scr->virtualGeometry().topLeft().x();
//    offset_y = scr->virtualGeometry().topLeft().y();
//    move(offset_x, offset_y);

    QPalette palette;
    palette.setBrush(QPalette::Background, pm);
    this->setPalette(palette);

    setCursor(Qt::CrossCursor);

}

AreaSelector::~AreaSelector()
{
}

void AreaSelector::mousePressEvent(QMouseEvent *event)
{
//    start = QCursor::pos();
    start = event->pos();
    rubber_band = new QRubberBand(QRubberBand::Rectangle, this);
//    rubber_band->setGeometry(QRect(start, QSize()));
    rubber_band->show();
}

void AreaSelector::mouseMoveEvent(QMouseEvent *event)
{
    rubber_band->setGeometry(QRect(start, event->pos()).normalized());
}

void AreaSelector::mouseReleaseEvent(QMouseEvent *event)
{
    rubber_band->hide();
    delete rubber_band;
    // determine selection, for example using QRect::intersects()
    // and QRect::contains().

//    end = QCursor::pos();
    end = event->pos();

    int leftmost = min(start.x(), end.x());
    int rightmost = max(start.x(), end.x());
    int topmost = min(start.y(), end.y());
    int botmost = max(start.y(), end.y());

    area = QRect(QPoint(leftmost, topmost), QPoint(rightmost, botmost));

    hide();
}
