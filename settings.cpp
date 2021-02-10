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
    mw->set_custom_save(value("CUSTOM_SAVE").toBool());
    mw->set_custom_save_path(save_path);
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

    setValue("CUSTOM_SAVE", mw->is_custom_save());
    setValue("SAVE_PATH", save_path);
    // get point
}
