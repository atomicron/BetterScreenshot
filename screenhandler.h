#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include <QWidget>
#include <QScreen>

class MainWindow;

class ScreenHandler : public QWidget
{
    Q_OBJECT

    MainWindow* mw;
    QScreen* scr;
    QSize full_size;

    const QString get_absolute_save_path();
    int get_offset(int);

public:
    explicit ScreenHandler(MainWindow *parent = nullptr);

    void do_screenshot();

};

#endif // SCREENHANDLER_H
