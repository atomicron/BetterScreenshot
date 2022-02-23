#include "settings.h"
#include "mainwindow.h"
#include "misc/msgbox.h"

#include "misc/os.h"

Settings::Settings(MainWindow *parent)
    : QSettings(QSettings::UserScope, QString("BetterScreenshot"), QString("BetterScreenshot"), parent)
    , mw(parent)
{
}

QString Settings::get_default_save_path()
{
    QString default_save_path; // = QDir::homePath() + "/Documents/BetterScreenshot";

    // The name of the final destination folder/directory;
    QString destination_folder = "BetterScreenshot";

    // If Windows, use default save path C:/Users/USER/Pictures/BetterScreenshot
#if WINDOWS_OS
//    QString windows_home_dir = "C:/Users/" + QDir::home();
    QString windows_home_dir = QDir::homePath();
    QString windows_default_save_path = windows_home_dir + "/Pictures/" + destination_folder;
    default_save_path = windows_default_save_path;
#endif

    // If Linux, use /home/USER/Pictures/BetterScreenshot
#if LINUX_OS
    QString linux_home_dir = QDir::homePath();
    QString linux_default_save_path = linux_home_dir + "/Pictures/" + destination_folder;
    default_save_path = linux_default_save_path;
#endif

    return default_save_path;
}

const QString PRINT_SCREEN_KEY = "PRINT_SCREEN_KEY";
const QString PSK_FUNCTION = "PSK_FUNCTION";
const QString DRAW = "DRAW";
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
    mw->set_psk_function(value(PSK_FUNCTION).toInt());
    mw->set_enable_draw(value(DRAW).toBool());
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
    setValue(PSK_FUNCTION, mw->get_psk_function());
    setValue(DRAW, mw->is_draw_enabled);
    setValue(AUTO_SAVE, mw->is_auto_save_enabled);
    setValue(CLIPBOARD, mw->is_copy_enabled);
    setValue(TRAY_POP_UP, mw->is_tray_pop_up_enabled());
    setValue(CUSTOM_SAVE, mw->is_custom_save());
    setValue(SAVE_PATH, mw->get_save_path());
    setValue(START_POINT, mw->selected_area.topLeft());
    setValue(END_POINT, mw->selected_area.bottomRight());
    setValue(QUALITY, mw->get_quality());
}
