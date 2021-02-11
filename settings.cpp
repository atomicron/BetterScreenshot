#include "settings.h"
#include "mainwindow.h"
#include "msgbox.h"

#include<QDebug>

Settings::Settings(MainWindow *parent)
    : QSettings(QSettings::UserScope, QString("BetterScreenshot"), QString("BetterScreenshot"), parent)
    , mw(parent)
{
}

const QString ENABLE_CROP = "ENABLE_CROP";
const QString AUTO_SAVE = "AUTO_SAVE";
const QString CLIPBOARD = "CLIPBOARD";
const QString CUSTOM_SAVE = "CUSTOM_SAVE";
const QString SAVE_PATH = "SAVE_PATH";
const QString START_POINT = "START_POINT";
const QString END_POINT = "END_POINT";
const QString QUALITY = "QUALITY";

void Settings::load()
{
    if (status() != QSettings::NoError)
        MsgBox("Error, could not load settings");

    mw->set_enable_crop(value(ENABLE_CROP).toBool());
    mw->set_enable_auto_save(value(AUTO_SAVE).toBool());
    mw->set_enable_copy(value(CLIPBOARD).toBool());
    mw->set_enable_custom_save(value(CUSTOM_SAVE).toBool());
    mw->set_save_path(value(SAVE_PATH).toString());
    mw->set_selected_area(QRect(value(START_POINT).toPoint(), value(END_POINT).toPoint()));
    mw->set_quality(value(QUALITY).toInt());
}

void Settings::save()
{
    setValue(ENABLE_CROP, mw->is_crop_enabled);
    setValue(AUTO_SAVE, mw->is_auto_save_enabled);
    setValue(CLIPBOARD, mw->is_copy_enabled);
    setValue(CUSTOM_SAVE, mw->is_custom_save());
    setValue(SAVE_PATH, mw->get_save_path());
    setValue(START_POINT, mw->selected_area.topLeft());
    setValue(END_POINT, mw->selected_area.bottomRight());
    setValue(QUALITY, mw->get_quality());
}
