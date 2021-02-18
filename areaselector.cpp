#include "areaselector.h"
#include <QCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>

int min(int a, int b) { return a<b ? a : b; }
int max(int a, int b) { return a>b ? a : b; }

AreaSelector::AreaSelector(QWidget *parent) : QDialog(parent)
{
    installEventFilter(this);
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowState(windowState() | Qt::WindowFullScreen);
    setWindowOpacity(0.2);

    QScreen* scr  = QGuiApplication::primaryScreen();
    setGeometry(scr->virtualGeometry().topLeft().x(), scr->virtualGeometry().topLeft().y(),
                scr->virtualSize().width(), scr->virtualSize().height());

    setCursor(Qt::CrossCursor);
    rubber_band = nullptr;
    accepted = false;
}

AreaSelector::AreaSelector(QPixmap pm, QWidget *parent) : QDialog(parent)
{
    installEventFilter(this);
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowState(windowState() | Qt::WindowFullScreen);
    setWindowOpacity(1);

    setFixedSize(pm.size());

//    QScreen* scr  = QGuiApplication::primaryScreen();
//    setGeometry(scr->virtualGeometry().topLeft().x(), scr->virtualGeometry().topLeft().y(),
//                scr->virtualSize().width(), scr->virtualSize().height());

    QPainter painter(&pm);
    painter.setOpacity(0.33);
    painter.fillRect(QRect(0, 0, pm.size().width(), pm.size().height()), QColor("gray"));

    QPalette palette;
    palette.setBrush(QPalette::Background, pm);

    setPalette(palette);

    setCursor(Qt::CrossCursor);
    rubber_band = nullptr;
    accepted = false;
}

AreaSelector::~AreaSelector()
{
}

void AreaSelector::mousePressEvent(QMouseEvent *event)
{
    start = event->pos();
    // this should be moved to the constructor
    if (rubber_band) delete rubber_band;
    rubber_band = new QRubberBand(QRubberBand::Rectangle, this);
    rubber_band->show();
//    if (event->button() == Qt::RightButton)
//    {
//        if (rubber_band)
//            delete rubber_band;
//        hide();
//        accepted = false;
//        event->ignore();
//    }
}

void AreaSelector::mouseMoveEvent(QMouseEvent *event)
{
    rubber_band->setGeometry(QRect(start, event->pos()).normalized());
}

void AreaSelector::mouseReleaseEvent(QMouseEvent *event)
{
    rubber_band->hide();
    delete rubber_band;

    if (event->button() == Qt::RightButton)
    {
        accepted = false;
    }
    else
    {
        accepted = true;

        end = event->pos();

        int leftmost = min(start.x(), end.x());
        int rightmost = max(start.x(), end.x());
        int topmost = min(start.y(), end.y());
        int botmost = max(start.y(), end.y());

        area = QRect(QPoint(leftmost, topmost), QPoint(rightmost, botmost));
    }

    hide();
}
