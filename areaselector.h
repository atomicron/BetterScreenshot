#ifndef AREASELECTOR_H
#define AREASELECTOR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QDialog>

class AreaSelector : public QDialog
{
    Q_OBJECT

    QPoint start;
    QPoint end;

    int offset_x;
    int offset_y;

    QRect area;

public:
    explicit AreaSelector(QWidget *parent = nullptr);
    ~AreaSelector();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

    const QRect get_area() const { return area; }

};

#endif // AREASELECTOR_H
