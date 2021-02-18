#ifndef AREASELECTOR_H
#define AREASELECTOR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QDialog>
#include <QRubberBand>

class AreaSelector : public QDialog
{
    Q_OBJECT

    QPoint start;
    QPoint end;

    int offset_x;
    int offset_y;

    QRect area;

    QRubberBand* rubber_band;

    bool accepted;

public:
    explicit AreaSelector(QWidget *parent = nullptr);
    explicit AreaSelector(QPoint, QPixmap, QWidget *parent = nullptr);
    ~AreaSelector();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

    const QRect get_area() const { return area; }

    bool is_accepted() const { return accepted; }
};

#endif // AREASELECTOR_H
