#ifndef DRAWDIALOG_H
#define DRAWDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QToolBox>
#include <QToolBar>
#include <QAction>
#include <QDebug>

#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QColorDialog>

#include "drawlabel.h"

class DrawDialog : public QDialog
{
    Q_OBJECT

    QPixmap *pm;

    QGridLayout *gl;
    QGridLayout *inner_gl;
    QWidget *inner_widget;
    DrawLabel *image_label;
    QScrollArea* scroll_area;
    QToolBar* toolbar;
    QLineEdit *width_input;

    QAction* action_pen;
    QAction* action_rectangle;
    QAction* action_circle;

public:
    explicit DrawDialog(QPixmap pixmap, QWidget *parent = nullptr);

    QPixmap get_image();

private slots:
    void pen_clicked();
    void rectangle_clicked();
    void circle_clicked();
    void width_input_changed();
    void pick_color();

};

#endif // DRAWDIALOG_H
