#include "screenhandler.h"
#include "mainwindow.h"
#include "settings.h"

#include "areaselector.h"
#include <QClipboard>

#include <QDebug>
#include <QGuiApplication>
#include <QPixmap>
#include <QPainter>
//#include <QElapsedTimer>

const QString ScreenHandler::get_absolute_save_path()
{
    QString save_path = mw->get_save_path();
    QString count_string = QString::number(QDir(save_path).count());
    QString prefix = "screenshot";
    QString format = ".png";

    QString name = prefix + "_" + count_string + format;

    QString absolute_path = save_path + "/" + name;
    return absolute_path;
}

int ScreenHandler::get_offset(int arg)
{
    if (arg < 0) arg = -arg;
    else arg = 0;
    return arg;
}

ScreenHandler::ScreenHandler(MainWindow *parent)
    : QWidget(parent)
    , mw(parent)
{
    scr = QGuiApplication::primaryScreen();
    full_size = scr->virtualSize();
    int w = scr->virtualSize().width();
    int h = scr->virtualSize().height();
}

void ScreenHandler::do_screenshot()
{
    mw->in_shot=true;

    QPixmap canvas(full_size);
    canvas.fill(Qt::black);

    QList<QScreen*> screens_list = QGuiApplication::screens();
    QList<QPixmap> pml;

    QPainter painter(&canvas);

//    int leftmost_x=0;
//    int topmost_y=0;
//    for (int i=0; i<screens_list.size(); ++i)
//    {
//       if (leftmost_x < screens_list[i]->geometry().topLeft().x())
//           leftmost_x = screens_list[i]->geometry().topLeft().x();
//       if (topmost_y < screens_list[i]->geometry().topLeft().y())
//           topmost_y = screens_list[i]->geometry().topLeft().y();
//    }
//    qDebug()<<"topleftmost:"<<leftmost_x << ',' << topmost_y;

    int offset_x = get_offset(scr->virtualGeometry().topLeft().x());
    int offset_y = get_offset(scr->virtualGeometry().topLeft().y());

    for (int i=0; i<screens_list.size(); ++i)
    {
        pml.push_back(screens_list[i]->grabWindow(0));
    painter.drawPixmap(
                screens_list[i]->geometry().topLeft().x()+offset_x,
                screens_list[i]->geometry().topLeft().y()+offset_y,
                pml[i]);
    }
    painter.end();

//    if (mw->is_crop_enabled)
//    {
//        AreaSelector selector(canvas);
//        selector.move(-offset_x, -offset_y);
////        selector.move(leftmost_x, topmost_y);
//        selector.exec();
//        QRect area = selector.get_area();
//        canvas = canvas.copy(area);
//    }
    if (mw->is_auto_save_enabled && !canvas.save(get_absolute_save_path(), "", mw->get_quality()))
        qDebug() << "Failed to save";
    if (mw->is_copy_enabled)
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setPixmap(canvas);
        mw->tray_say("Copied to clipboard :)");
    }
    mw->in_shot=false;
}

void ScreenHandler::do_snipe()
{
    mw->in_shot=true;

    QPixmap canvas(full_size);
    canvas.fill(Qt::black);

    QList<QScreen*> screens_list = QGuiApplication::screens();
    QList<QPixmap> pml;

    QPainter painter(&canvas);

    int offset_x = get_offset(scr->virtualGeometry().topLeft().x());
    int offset_y = get_offset(scr->virtualGeometry().topLeft().y());

    for (int i=0; i<screens_list.size(); ++i)
    {
        pml.push_back(screens_list[i]->grabWindow(0));
        painter.drawPixmap(
                    screens_list[i]->geometry().topLeft().x()+offset_x,
                    screens_list[i]->geometry().topLeft().y()+offset_y,
                    pml[i]);
    }
    painter.end();

    AreaSelector selector(scr->availableGeometry().topLeft(), canvas);
    selector.setGeometry(scr->virtualGeometry().topLeft().x(), scr->virtualGeometry().topLeft().y(),
                        full_size.width(), full_size.height()
                         );
       selector.exec();
    QRect area = selector.get_area();
    canvas = canvas.copy(area);

    if (selector.is_accepted() && mw->is_auto_save_enabled && !canvas.save(get_absolute_save_path(), "", mw->get_quality()))
        qDebug() << "Failed to save";

//    qDebug()<<"Selector.is_accepted(): " << selector.is_accepted();
    if (selector.is_accepted() && mw->is_copy_enabled)
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setPixmap(canvas);
        mw->tray_say("Copied to clipboard :)");
    }
    mw->in_shot=false;
}
