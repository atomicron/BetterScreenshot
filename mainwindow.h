#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// User defined classes
#include "tray.h"
#include "keyhandler.h"
#include "settings.h"
#include "screenhandler.h"

#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void closeEvent(QCloseEvent*);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString get_custom_save_path();
    void set_custom_save_path(QString);
    bool is_custom_save();
    void set_custom_save(bool b);
    int get_quality();
    void set_quality(int);
    const QRect get_selected_area() const;
    void set_enable_crop(bool b);
    void set_enable_copy(bool b);
    void set_enable_auto_save(bool b);

    void set_selected_area(QRect);
    QRect selected_area;

    bool is_crop_enabled;
    bool is_auto_save_enabled;
    bool is_copy_enabled;

    void tray_say(QString);

public slots:
    void quit();
    void do_snapshot();

private slots:
    void on_cb_custom_savepath_toggled(bool checked);
    void on_btn_browse_dir_clicked();
    void on_btn_save_clicked();
    void on_btn_quit_clicked();
    void on_btn_select_area_clicked();
    void on_btn_reset_area_clicked();
    void on_quality_slider_valueChanged(int value);
    void on_cb_enable_crop_toggled(bool checked);

    void on_cb_enable_autosave_toggled(bool checked);

    void on_cb_enable_clipboard_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    Tray* tray;
    KeyHandler* kh;
    Settings* settings;
    ScreenHandler* sh;

};
#endif // MAINWINDOW_H
