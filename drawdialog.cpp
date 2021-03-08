#include "drawdialog.h"
#include <QGuiApplication>
#include <QScreen>
#include <QSizePolicy>
#include <QVBoxLayout>

DrawDialog::DrawDialog(QPixmap pixmap, QWidget *parent)
: QDialog(parent)
, pm(&pixmap)

{
    setWindowFlag(Qt::WindowMinMaxButtonsHint);
    setModal(true);
//    setMaximumSize(QGuiApplication::primaryScreen()->size());

    gl = new QGridLayout(this);
//    label = new QLabel(this);
//    label->setPixmap(*pm);
    label = new DrawLabel(*pm, this);

    QGridLayout *inner_layout = new QGridLayout(this);
    QLabel spacer1;
    spacer1.setFixedHeight(50);
    QLabel spacer2;
    spacer2.setFixedWidth(50);
    inner_layout->addWidget(&spacer1, 0, 1, -1, -1);
    inner_layout->addWidget(&spacer2, 1, 0, -1, -1);
    inner_layout->addWidget(label, 1, 1, Qt::AlignCenter);
    inner_layout->setMargin(0);

    scroll_area = new QScrollArea(this);
    scroll_area->setBackgroundRole(QPalette::Dark);
    scroll_area->setLayout(inner_layout);

    toolbar = new QToolBar(this);
    toolbar->setOrientation(Qt::Horizontal);
    action_pen = new QAction("Pen");
    toolbar->addAction(action_pen);

    gl->addWidget(toolbar);
    gl->addWidget(scroll_area);

    setLayout(gl);

//    QPixmap pix = *label->pixmap();

//    label->installEventFilter(this);

    connect (action_pen, SIGNAL(triggered()), this, SLOT(pen_clicked()));

//    pen.setStyle(Qt::SolidLine);
////    pen.setWidth(12);
////    pen.setWidth(15);
//    pen.setBrush(Qt::green);
//    pen.setCapStyle(Qt::RoundCap);
//    pen.setJoinStyle(Qt::RoundJoin);
}

QPixmap DrawDialog::get_image()
{
   return label->get_image();
}

void DrawDialog::pen_clicked()
{
}
