#include "stylepicker.h"
#include "ui_stylepicker.h"

StylePicker::StylePicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StylePicker)
{
    ui->setupUi(this);

    setModal(true);

    scrollArea = new QScrollArea(this);

    // label test
    QLabel *imageLabel = new QLabel;
    QImage image("/home/localuser/Documents/nature.jpg");
    imageLabel->setPixmap(QPixmap::fromImage(image));
//    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    // label test

    // put the widget containing all the goodies into the scrollarea
    scrollArea->setWidget(ui->widget);

    // use a layout with only the scroll are in it, to fill the whole area
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    setLayout(layout);

    // resize the window to 0.7(70%) of the screen
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    ui->buttonGroup1->addButton(ui->radioButton_1);
    ui->buttonGroup1->addButton(ui->radioButton_2);
    ui->buttonGroup1->addButton(ui->radioButton_3);
    ui->buttonGroup1->addButton(ui->radioButton_4);
    ui->buttonGroup1->addButton(ui->radioButton_5);
    ui->buttonGroup1->addButton(ui->radioButton_6);
    ui->buttonGroup2->addButton(ui->radioButton_7);
    ui->buttonGroup2->addButton(ui->radioButton_8);
    ui->buttonGroup2->addButton(ui->radioButton_9);
    ui->buttonGroup3->addButton(ui->radioButton_10);
    ui->buttonGroup3->addButton(ui->radioButton_11);
    ui->buttonGroup3->addButton(ui->radioButton_12);

    connect (this, SIGNAL(finished(int)), this, SLOT(get_values()));
}

void StylePicker::get_values()
{
    style_id = ui->buttonGroup1->checkedId();
    cap_id = ui->buttonGroup2->checkedId();
    join_id = ui->buttonGroup3->checkedId();

    if (ui->radioButton_1->isChecked())
        style_id = 1;
    if (ui->radioButton_2->isChecked())
        style_id = 2;
    if (ui->radioButton_3->isChecked())
        style_id = 3;
    if (ui->radioButton_4->isChecked())
        style_id = 4;
    if (ui->radioButton_5->isChecked())
        style_id = 5;
    if (ui->radioButton_6->isChecked())
        style_id = 7;
    if (ui->radioButton_7->isChecked())
        cap_id = 1;
    if (ui->radioButton_8->isChecked())
        cap_id = 2;
    if (ui->radioButton_9->isChecked())
        cap_id = 3;
     if (ui->radioButton_10->isChecked())
        join_id = 1;
    if (ui->radioButton_11->isChecked())
        join_id = 2;
    if (ui->radioButton_12->isChecked())
        join_id = 3;

    qDebug () << style_id << cap_id << join_id;
}

StylePicker::~StylePicker()
{
    delete ui;
}

Qt::PenStyle StylePicker::style()
{
    switch (style_id)
    {
    case 1:
        return Qt::SolidLine;
    case 2:
        return Qt::DashLine;
    case 3:
        return Qt::DotLine;
    case 4:
        return Qt::DashDotLine;
    case 5:
        return Qt::DashDotDotLine;
    case 6:
        return Qt::CustomDashLine;
    default:
        return Qt::SolidLine;
    };
}

Qt::PenCapStyle StylePicker::cap()
{
    switch (cap_id)
    {
    case 1:
        return Qt::SquareCap;
    case 2:
        return Qt::FlatCap;
    case 3:
        return Qt::RoundCap;
    default:
        return Qt::SquareCap;
    };
}

Qt::PenJoinStyle StylePicker::join()
{
    switch (join_id)
    {
    case 1:
        return Qt::BevelJoin;
    case 2:
        return Qt::MiterJoin;
    case 3:
        return Qt::RoundJoin;
    default:
        return Qt::BevelJoin;
    };
}

