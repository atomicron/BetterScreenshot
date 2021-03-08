#ifndef DRAWLABEL_H
#define DRAWLABEL_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QMouseEvent>
#include <QPen>

class DrawLabel : public QWidget
{

    QGridLayout* gl;
    QLabel *label;
    QPixmap pixmap ;

    QPixmap clean_pix;

    bool is_painting = false;
    bool start_painting = false;
    QPoint prev;
    QPoint next;


public:
    enum Tool { Pen, Rectangle, Circle };

    explicit DrawLabel(QPixmap pm, QWidget *parent = nullptr);

    static QPen pen;
    static Tool current_tool;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);

    QPixmap get_image();
    void set_tool(Tool t);

private:

};

#endif // DRAWLABEL_H
