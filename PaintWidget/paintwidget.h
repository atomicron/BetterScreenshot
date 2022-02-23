#ifndef PAINTKEK_H
#define PAINTKEK_H

#include <QMainWindow>
#include <QPen>
#include <QMouseEvent>
#include <QGraphicsScene>
#include "graphicsscene.h"
#include "stylepicker.h"
#include <QDebug>
#include <QColorDialog>
#include <QInputDialog>
#include <QToolBar>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class PaintKEK; }
QT_END_NAMESPACE

class PaintKEK : public QDialog
{
    Q_OBJECT

public:
    PaintKEK(QWidget *parent = nullptr);
    ~PaintKEK();

    void setImage(QPixmap p);
    QPixmap getImage();

private:
    Ui::PaintKEK *ui;
    GraphicsScene *scene;

    QPoint start_point;
    QPoint next_point;

    void init_actions();

    QToolBar* toolBar;

private slots:
    void action_undo_triggered();
    void action_pen_triggered();
    void action_box_triggered();
    void action_circle_triggered();
    void action_color_triggered();
    void action_width_triggered();
    void action_style_triggered();

};
#endif // PAINTKEK_H
