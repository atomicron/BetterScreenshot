#include "drawdialog.h"
#include <QGuiApplication>
#include <QScreen>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>

DrawDialog::DrawDialog(QPixmap pixmap, QWidget *parent)
: QDialog(parent)
//, pm(&pixmap)

{
    setWindowFlag(Qt::WindowMinMaxButtonsHint);
    setModal(true);

    // label that holds the image
    image_label = new DrawLabel(pixmap, this);
    image_label->setBackgroundRole(QPalette::Base);
    image_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // layout for the inner widget
    inner_gl = new QGridLayout(this);
//    inner_gl->setRowMinimumHeight(0, 20);
//    inner_gl->setRowMinimumHeight(2, 20);
//    inner_gl->setColumnMinimumWidth(0, 20);
//    inner_gl->setColumnMinimumWidth(2, 20);
    inner_gl->addWidget(image_label, 1, 1, Qt::AlignCenter);

    // inner_widget will be inside the scroll area
    inner_widget = new QWidget(this);
    inner_widget->setLayout(inner_gl);

    // scroll area that takes the inner widget
    scroll_area = new QScrollArea(this);
    scroll_area->setBackgroundRole(QPalette::Dark);
    scroll_area->setWidget(inner_widget);

    // add the scroll area to the outer layout
    gl = new QGridLayout(this);
    gl->addWidget(scroll_area);
    gl->setMargin(0);
    setLayout(gl);

    QSize max = QGuiApplication::primaryScreen()->size();
    QSize preferred_size = pixmap.size();
    // adjust for the offset
    preferred_size.setHeight(preferred_size.height() + 70);
    preferred_size.setWidth(preferred_size.width() + 30);

    // adjust for taskbar or whatever
    int offset=200;
    if (preferred_size.width() > max.width() - offset)
        preferred_size.setWidth(max.width() - offset);
    if (preferred_size.height() > max.height() - offset)
        preferred_size.setHeight(max.height() - offset);

    resize(preferred_size);

    // toolbar stuff
    toolbar = new QToolBar(this);
    toolbar->setBackgroundRole(QPalette::Base);
    toolbar->setOrientation(Qt::Horizontal);
    action_pen = new QAction("Pen");
    action_pen->setIcon(QIcon(":/resources/icon/pen.png"));
    action_rectangle = new QAction("Rectangle");
    action_rectangle->setIcon(QIcon(":/resources/icon/rectangle.png"));
    action_circle = new QAction("Circle");
    action_circle->setIcon(QIcon(":/resources/icon/circle.png"));
    toolbar->addAction(action_pen);
    toolbar->addAction(action_rectangle);
    toolbar->addAction(action_circle);
    QLabel *label = new QLabel(this);
    label->setText("Width:");
    toolbar->addWidget(label);
    width_input = new QLineEdit(this);
    width_input->setFixedSize(20, 20);
    toolbar->addWidget(width_input);
    QPushButton *color_pick_button = new QPushButton(this);
//    color_pick_button->setStyleSheet("QPushButton { border:none; }");
    color_pick_button->setIcon(QIcon(":/resources/icon/palette.png"));
    color_pick_button->setFixedSize(25, 25);
    toolbar->addWidget(color_pick_button);
//    toolbar->setStyleSheet("QToolButton { padding-left: 5px; padding-right: 5px; }");
    toolbar->setStyleSheet("QToolButton { margin: 5px; }");
    gl->addWidget(toolbar);

    connect (action_pen, SIGNAL(triggered()), this, SLOT(pen_clicked()));
    connect (action_rectangle, SIGNAL(triggered()), this, SLOT(rectangle_clicked()));
    connect (action_circle, SIGNAL(triggered()), this, SLOT(circle_clicked()));
    connect (width_input, SIGNAL(textChanged(QString)), this, SLOT(width_input_changed()));
    connect (color_pick_button, SIGNAL(clicked()), this, SLOT(pick_color()));
}

QPixmap DrawDialog::get_image()
{
    return image_label->get_image();
}

void DrawDialog::pen_clicked()
{
    image_label->set_tool(DrawLabel::Tool::Pen);
}

void DrawDialog::rectangle_clicked()
{
    image_label->set_tool(DrawLabel::Tool::Rectangle);
}

void DrawDialog::circle_clicked()
{
    image_label->set_tool(DrawLabel::Tool::Circle);
}

void DrawDialog::width_input_changed()
{
    QString str = width_input->text();
    qDebug() << str;
    image_label->pen.setWidth(str.toInt());
}

void DrawDialog::pick_color()
{
    image_label->pen.setColor(QColorDialog::getColor());
}

