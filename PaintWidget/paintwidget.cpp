#include "paintwidget.h"
#include "ui_paintwidget.h"

PaintKEK::PaintKEK(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaintKEK)
{
    ui->setupUi(this);

    scene = new GraphicsScene(this);
    toolBar = new QToolBar("Title", this);

    init_actions();
    layout()->addWidget(toolBar);

//    QPixmap cat_pixmap(":/resources/cat.jpg");
//    scene->push_back(cat_pixmap);

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

PaintKEK::~PaintKEK()
{
    delete ui;
}

void PaintKEK::setImage(QPixmap p)
{
//    scene->clear();
    scene->push_back(p);
}

QPixmap PaintKEK::getImage()
{
    scene->clearSelection();                                                  // Selections would also render to the file
    scene->setSceneRect(scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);                                              // Start all pixels transparent


    QPainter painter(&image);
    scene->render(&painter);
//	image.save("file_name.png");

    return QPixmap::fromImage(image);

//    return ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
}

void PaintKEK::init_actions()
{
    QAction* action_undo = new QAction("Undo");
    toolBar->addAction(action_undo);
    QAction* action_pen = new QAction("Pen");
    toolBar->addAction(action_pen);
    QAction* action_box = new QAction("Box");
    toolBar->addAction(action_box);
    QAction* action_circle = new QAction("O");
    toolBar->addAction(action_circle);
    QAction* action_color_picker = new QAction("Color");
    toolBar->addAction(action_color_picker);
    QAction* action_width = new QAction("Width");
    toolBar->addAction(action_width);
    QAction* action_style = new QAction("Style");
    toolBar->addAction(action_style);

    connect (action_undo, SIGNAL(triggered()), this, SLOT(action_undo_triggered()));
    connect (action_pen, SIGNAL(triggered()), this, SLOT(action_pen_triggered()));
    connect (action_box, SIGNAL(triggered()), this, SLOT(action_box_triggered()));
    connect (action_circle, SIGNAL(triggered()), this, SLOT(action_circle_triggered()));
    connect (action_color_picker, SIGNAL(triggered()), this, SLOT(action_color_triggered()));
    connect (action_width, SIGNAL(triggered()), this, SLOT(action_width_triggered()));
    connect (action_style, SIGNAL(triggered()), this, SLOT(action_style_triggered()));
}

void PaintKEK::action_undo_triggered()
{
    scene->pop_back();
}

void PaintKEK::action_pen_triggered()
{
    scene->current_tool = GraphicsScene::PEN;
}

void PaintKEK::action_box_triggered()
{
    scene->current_tool = GraphicsScene::BOX;
}

void PaintKEK::action_circle_triggered()
{
    scene->current_tool = GraphicsScene::CIRCLE;
}

void PaintKEK::action_color_triggered()
{
    QColor color = QColorDialog::getColor();
    scene->pen.setColor(color);
}

void PaintKEK::action_width_triggered()
{
    int width = QInputDialog::getInt(this, tr("PO-TA-TOES:"),
                     tr("Width:"), QLineEdit::Normal);
    scene->pen.setWidth(width);
}

void PaintKEK::action_style_triggered()
{
    StylePicker picker;
    picker.exec();

    scene->pen.setStyle(picker.style());
    scene->pen.setCapStyle(picker.cap());
    scene->pen.setJoinStyle(picker.join());

    qDebug () << "scene->pen: " << scene->pen;
}
