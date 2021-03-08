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

    gl->addWidget(label);
    gl->setMargin(0);
    setLayout(gl);

}

DrawLabel::Tool DrawLabel::current_tool = DrawLabel::Tool::Pen;
QPen DrawLabel::pen = QPen(Qt::black, 1);

void DrawLabel::mousePressEvent(QMouseEvent* event)
{
    start_painting = true;
    is_painting = true;
    prev = event->pos();
}

void DrawLabel::mouseMoveEvent(QMouseEvent* event)
{
    next = event->pos();
    update();
}

void DrawLabel::mouseReleaseEvent(QMouseEvent* event)
{
    is_painting = false;
    update();
}

void DrawLabel::paintEvent(QPaintEvent *event)
{

    if (start_painting)
    {
        clean_pix = label->pixmap()->copy();
        start_painting = false;
    }
    if (is_painting)
    {
        // IF PEN SELECTED
        if (current_tool == Pen)
        {
            QPainter painter(&clean_pix);
            painter.setPen(pen);
            painter.drawLine(prev, next);
            prev = next;
        }
        // ENDIF

        // If any of the other will be selected.
        // Constantly make a copy of your "clean" pixmap
        QPixmap copy = clean_pix.copy();
        // IF RECTANGLE
        if (current_tool == Rectangle)
        {
            QPainter painter(&copy);
            painter.setPen(pen);
            painter.drawRoundedRect(QRect(prev, next), 5, 5);
        }
        // ENDIF

        // IF CIRCLE SELECTED
        if (current_tool == Circle)
        {
            QPainter painter(&copy);
            painter.setPen(pen);
            painter.drawEllipse(QRect(prev, next));
        }
        // ENDIF
        label->setPixmap(copy);
    }
}

QPixmap DrawLabel::get_image()
{
    return label->pixmap()->copy();
}

void DrawLabel::set_tool(Tool t)
{
    current_tool = t;
}
