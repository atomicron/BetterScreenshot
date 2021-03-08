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

#include "drawlabel.h"

class DrawDialog : public QDialog
{
    Q_OBJECT

    QPixmap *pm;

    QGridLayout *gl;
//    QLabel *label;
    QScrollArea* scroll_area;
    QToolBar* toolbar;

    QAction* action_pen;
    DrawLabel* label;

//    QPainter* painter;
//    QPen pen;
//    QPoint prev;
//    QPoint xy;
//    bool is_painting = false;

//    QPixmap *tmp_pix;

public:
    explicit DrawDialog(QPixmap pixmap, QWidget *parent = nullptr);

    QPixmap get_image();

private slots:
    void pen_clicked();

};

#endif // DRAWDIALOG_H
