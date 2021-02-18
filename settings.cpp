#include "settings.h"
#include "mainwindow.h"
#include "misc/msgbox.h"

Settings::Settings(MainWindow *parent)
    : QSettings(QSettings::UserScope, QString("BetterScreenshot"), QString("BetterScreenshot"), parent)
    , mw(parent)
{
}

const QString PRINT_SCREEN_KEY = "PRINT_SCREEN_KEY";
const QString AUTO_SAVE = "AUTO_SAVE";
const QString CLIPBOARD = "CLIPBOARD";
const QString TRAY_POP_UP = "TRAY_POP_UP";
const QString CUSTOM_SAVE = "CUSTOM_SAVE";
const QString SAVE_PATH = "SAVE_PATH";
const QString START_POINT = "START_POINT";
const QString END_POINT = "END_POINT";
const QString QUALITY = "QUALITY";

void Settings::load()
{
    if (status() != QSettings::NoError)
        MsgBox("Error, could not load settings");

    mw->set_print_screen_key(value(PRINT_SCREEN_KEY).toBool());
    mw->set_enable_auto_save(value(AUTO_SAVE).toBool());
    mw->set_enable_copy(value(CLIPBOARD).toBool());
    mw->set_enable_tray_pop_up(value(TRAY_POP_UP).toBool());
    mw->set_enable_custom_save(value(CUSTOM_SAVE).toBool());
    mw->set_save_path(value(SAVE_PATH).toString());
    mw->set_selected_area(QRect(value(START_POINT).toPoint(), value(END_POINT).toPoint()));
    mw->set_quality(value(QUALITY).toInt());
}

void Settings::save()
{
    setValue(PRINT_SCREEN_KEY, mw->is_print_screen_enabled);
    setValue(AUTO_SAVE, mw->is_auto_save_enabled);
    setValue(CLIPBOARD, mw->is_copy_enabled);
    setValue(TRAY_POP_UP, mw->is_tray_pop_up_enabled());
    setValue(CUSTOM_SAVE, mw->is_custom_save());
    setValue(SAVE_PATH, mw->get_save_path());
    setValue(START_POINT, mw->selected_area.topLeft());
    setValue(END_POINT, mw->selected_area.bottomRight());
    setValue(QUALITY, mw->get_quality());
}
