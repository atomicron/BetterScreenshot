#include "screenhandler.h"
#include "mainwindow.h"
#include "settings.h"
#include "misc/msgbox.h"

#include "areaselector.h"
#include <QClipboard>

#include <QDebug>
#include <QGuiApplication>
#include <QPixmap>
#include <QPainter>

#include "PaintWidget/paintwidget.h"

#include <cmath>

QString rand_alnum(int len)
{
    QString str;
    for (int i=0;i<len;++i)
    {
        int rand1 = (rand() % ('Z'-'A')) + 'A';
        int rand2 = (rand() % ('z'-'a')) + 'a';
        int rand3 = (rand() % ('9' - '0')) + '0';
        str += char(rand1);
        str += char(rand2);
        str += char(rand3);
    }
    return str;
}

const QString ScreenHandler::get_absolute_save_path()
{
    QString save_path = mw->get_save_path();
    QString count_string = QString::number(QDir(save_path).count());
    QString prefix = "screenshot";
    QString format = ".png";
    QString name = prefix + "_" + count_string;
    QString absolute_path = save_path + "/" + name + format;

    while (QFile::exists(absolute_path)) {
        QString random_suffix = rand_alnum(3);
        absolute_path = save_path + "/" + name + "_" + random_suffix + format;
    }
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
}

void ScreenHandler::do_screenshot()
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

    AreaSelector selector(canvas);
    selector.setGeometry(scr->virtualGeometry().topLeft().x(), scr->virtualGeometry().topLeft().y(),
                        full_size.width(), full_size.height());
    selector.exec();

    QRect area = selector.get_area();
    canvas = canvas.copy(area);

    if (selector.is_accepted() && mw->is_draw_enabled)
    // if draw mode is enabled open a drawing dialog with the canvas as a main image
    {
        PaintKEK paintKEK;
        paintKEK.setImage(canvas);
        paintKEK.exec();
        qDebug () << "Waiting";
        canvas = paintKEK.getImage();
        qDebug () << "New canvas";
    }

    if (selector.is_accepted() && mw->is_auto_save_enabled && !canvas.save(get_absolute_save_path(), "", mw->get_quality()))
        MsgBox("Failed to save\n"
               "Check save directory settings");

    if (selector.is_accepted() && mw->is_copy_enabled)
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setPixmap(canvas);
        mw->tray_say("Copied to clipboard :)");
    }

    mw->in_shot=false;
}
