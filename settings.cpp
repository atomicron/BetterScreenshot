#include "settings.h"
#include "mainwindow.h"
#include "msgbox.h"

Settings::Settings(MainWindow *parent)
    : QSettings(QSettings::UserScope, QString("BetterScreenshot"), QString("BetterScreenshot"), parent)
    , mw(parent)
{
}

void Settings::load()
{
    if (status() != QSettings::NoError)
        MsgBox("Error, could not load settings");

    save_path =	value("SAVE_PATH").toString();
    mw->set_enable_crop(value("ENABLE_CROP").toBool());
    mw->set_enable_auto_save(value("AUTO_SAVE").toBool());
    mw->set_enable_copy(value("CLIPBOARD").toBool());
    mw->set_custom_save(value("CUSTOM_SAVE").toBool());
    mw->set_custom_save_path(save_path);
    mw->set_selected_area(QRect(value("START_POINT").toPoint(), value("END_POINT").toPoint()));
    mw->set_quality(value("QUALITY").toInt());
    if (!QDir(save_path).exists())
    {
        MsgBox("The screenshots path does not exist anymore\nLikely it has been deleted."
               " The program will try to recreate the path in the input box upon clicking 'Save'");
    }
}

void Settings::save()
{
    save_path = default_save_path;
    if (mw->is_custom_save())
    {
        save_path = mw->get_custom_save_path();
    }
    else
    {
        mw->set_custom_save_path(default_save_path);
    }

    setValue("ENABLE_CROP", mw->is_crop_enabled);
    setValue("AUTO_SAVE", mw->is_auto_save_enabled);
    setValue("CLIPBOARD", mw->is_copy_enabled);
    setValue("CUSTOM_SAVE", mw->is_custom_save());
    setValue("SAVE_PATH", save_path);
    setValue("START_POINT", mw->selected_area.topLeft());
    setValue("END_POINT", mw->selected_area.bottomRight());
    setValue("QUALITY", mw->get_quality());
}
