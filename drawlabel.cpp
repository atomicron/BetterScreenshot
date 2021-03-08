#include "drawlabel.h"

#include <QPainter>
#include <QDebug>

DrawLabel::DrawLabel(QPixmap pm, QWidget *parent)
: QWidget(parent)
, pixmap(pm)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    gl = new QGridLayout(this);

    label = new QLabel(this);
    label->setPixmap(pixmap);

//    scroll_area = new QScrollArea(this);
//    scroll_area->setBackgroundRole(QPalette::Dark);
//    scroll_area->setWidget(label);

//    gl->addWidget(scroll_area);
    gl->addWidget(label);
    gl->setMargin(0);
    setLayout(gl);
}

void DrawLabel::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "Press event";
    is_painting = true;
    prev = event->pos();
}

void DrawLabel::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "Position: " << event->pos();
    next = event->pos();
    update();
}

void DrawLabel::mouseReleaseEvent(QMouseEvent* event)
{
    is_painting = false;
}

void DrawLabel::paintEvent(QPaintEvent *event)
{
    if (!is_painting) return;
    //    qDebug()<<"Paint event";
    QPixmap pix = *label->pixmap();
    QPainter painter(&pix);
    QPen pen(Qt::blue);
    painter.setPen(pen);
    qDebug() << "Drawing line from " << prev << " to " << next;
    painter.drawLine(prev, next);
    prev = next;
    label->setPixmap(pix);
}

QPixmap DrawLabel::get_image()
{
    return label->pixmap()->copy();
}
