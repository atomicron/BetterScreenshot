#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QDir>

class MainWindow;

class Settings : public QSettings
{
    Q_OBJECT

    MainWindow* mw;
    QString save_path;

public:
    explicit Settings(MainWindow* parent = nullptr);

    const QString get_save_path() const { return save_path; }
    const QString default_save_path = QDir::homePath() + "/Documents/BetterScreenshot";

    void load();
    void save();
};

#endif // SETTINGS_H
