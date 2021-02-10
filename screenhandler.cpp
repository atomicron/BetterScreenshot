#include "screenhandler.h"
#include "mainwindow.h"
#include "settings.h"

#include <QDebug>
#include <QGuiApplication>
#include <QPixmap>
#include <QPainter>
#include <QElapsedTimer>

ScreenHandler::ScreenHandler(MainWindow *parent)
    : QWidget(parent)
    , mw(parent)
{
    scr = QGuiApplication::primaryScreen();
}

void ScreenHandler::do_screenshot()
{
    QElapsedTimer timer;
    timer.start();

    QSize full_size = scr->virtualSize();

    QPixmap canvas(full_size);
    canvas.fill(Qt::black);

    QList<QScreen*> screens_list = QGuiApplication::screens();
    QList<QPixmap> pml;

    QPainter painter(&canvas);

    int offset_x = scr->virtualGeometry().topLeft().x();
    int offset_y = scr->virtualGeometry().topLeft().y();

    if (offset_x < 0) offset_x = -offset_x;
    else offset_x = 0;
    if (offset_y < 0) offset_y = -offset_y;
    else offset_y = 0;

    for (int i=0; i<screens_list.size(); ++i)
    {
        pml.push_back(screens_list[i]->grabWindow(0));
        painter.drawPixmap(screens_list[i]->geometry().topLeft().x()+offset_x,
                   screens_list[i]->geometry().topLeft().y()+offset_y,
                   pml[i]);
    }
    painter.end();

    QString save_path = mw->get_custom_save_path();
    int count = QDir(save_path).count();
    QString count_string = QString::number(count);
    QString absolute_path = save_path+"/screenshot_"+count_string+".png";
    QString format = ".png";
    int quality = mw->get_quality();

    qDebug() << "Abs path: " << absolute_path;
    if (!canvas.save(absolute_path, "", quality))
        qDebug() << "Failed to save";

   qDebug() << "Elapsed time: " << timer.elapsed();
}
