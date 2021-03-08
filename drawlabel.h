#ifndef DRAWLABEL_H
#define DRAWLABEL_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QMouseEvent>

class DrawLabel : public QWidget
{
    Q_OBJECT

    QGridLayout* gl;
//    QScrollArea *scroll_area;
    QLabel *label;
    QPixmap pixmap;

    bool is_painting = false;
    QPoint prev;
    QPoint next;

public:
    explicit DrawLabel(QPixmap pm, QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);

    QPixmap get_image();

signals:

};

#endif // DRAWLABEL_H
