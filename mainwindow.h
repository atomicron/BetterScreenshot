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

    QString get_save_path();
    bool is_custom_save();
    int get_quality();
    bool is_tray_pop_up_enabled();
    const QRect get_selected_area() const;

    void set_print_screen_key(bool b);
    void set_enable_auto_save(bool b);
    void set_enable_copy(bool b);
    void set_enable_tray_pop_up(bool b);
    void set_enable_custom_save(bool b);
    void set_save_path(QString);
    void set_selected_area(QRect);
    void set_quality(int);

    QRect selected_area;
    QString save_path;
    bool is_auto_save_enabled;
    bool is_copy_enabled;
    bool is_print_screen_enabled;

    bool in_shot = false;

    void tray_say(QString);

public slots:
    void custom_quit();
    void do_print_screen();
    void do_screenshot();
    void do_snipe();

private slots:
    void on_cb_custom_savepath_toggled(bool checked);
    void on_btn_browse_dir_clicked();
    void on_btn_select_area_clicked();
    void on_btn_reset_area_clicked();
    void on_quality_slider_valueChanged(int value);
    void on_cb_enable_print_screen_key_toggled(bool checked);
    void on_cb_enable_autosave_toggled(bool checked);
    void on_cb_enable_clipboard_toggled(bool checked);
    void on_btn_snipe_clicked();
    void on_input_custom_path_textChanged(const QString &arg1);
    void on_cb_enable_tray_pop_up_toggled(bool checked);
    void on_btn_print_screen_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Tray* tray;
    KeyHandler* kh;
    Settings* settings;
    ScreenHandler* sh;

};
#endif // MAINWINDOW_H
