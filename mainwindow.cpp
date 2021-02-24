#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "misc/msgbox.h"
#include "areaselector.h"

#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>

#include <QDebug>

#include "misc/log.h"
Log *Log::instance = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , lock(new Lock(QDir::homePath()+"/.BetterScreenshotLock"))
    , ui(new Ui::MainWindow)
    , tray(new Tray(this))
    , kh(&KeyHandler().Instance(this))
    , settings(new Settings(this))
    , sh(new ScreenHandler(this))
{
    ui->setupUi(this);
    kh->enable_hook();
    on_btn_reset_area_clicked();
    hide();

    setWindowTitle("Better Screenshot");
    setWindowIcon(QIcon(":/resources/icon/BS.png"));

    (log).truncate();
    (log).setEnable(true);
    log << "test me 123\r\n";


    ui->combo_box->addItem("Full screenshot");
    ui->combo_box->addItem("Snipe");

    settings->load();
}

MainWindow::~MainWindow()
{
    kh->disable_hook();
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

QString MainWindow::get_save_path()
{
    return ui->input_custom_path->text();
}

void MainWindow::set_save_path(QString path)
{
    save_path = path;
    ui->input_custom_path->setText(path);
}

void MainWindow::set_selected_area(QRect a)
{
    ui->lbl_start_point->setText("Start point: " + QString::number(a.topLeft().x()) +','+ QString::number(a.topLeft().y()));
    ui->lbl_end_point->setText("End point: " + QString::number(a.bottomRight().x()) +','+ QString::number(a.bottomRight().y()));
    selected_area = a;
}

bool MainWindow::is_custom_save()
{
    return ui->cb_custom_savepath->isChecked();
}

int MainWindow::get_psk_function()
{
    return ui->combo_box->currentIndex();
}

void MainWindow::set_enable_custom_save(bool b)
{
    ui->cb_custom_savepath->setChecked(b);
}

int MainWindow::get_quality()
{
    return ui->quality_slider->value();
}

bool MainWindow::is_tray_pop_up_enabled()
{
    return ui->cb_enable_tray_pop_up->isChecked();
}

void MainWindow::set_quality(int val)
{
    ui->quality_slider->setValue(val);
}

const QRect MainWindow::get_selected_area() const
{
    return selected_area;
}

void MainWindow::set_print_screen_key(bool b)
{
    is_print_screen_enabled = b;
    ui->cb_enable_print_screen_key->setChecked(b);
    ui->combo_box->setEnabled(b);
}

void MainWindow::set_psk_function(int selection)
{
    ui->combo_box->setCurrentIndex(selection);
}

void MainWindow::set_enable_copy(bool b)
{
    is_copy_enabled = b;
    ui->cb_enable_clipboard->setChecked(b);
}

void MainWindow::set_enable_tray_pop_up(bool b)
{
    tray->set_enable_pop_up(b);
    ui->cb_enable_tray_pop_up->setChecked(b);
}

void MainWindow::set_enable_auto_save(bool b)
{
    is_auto_save_enabled = b;
    ui->cb_enable_autosave->setChecked(b);
}

void MainWindow::tray_say(QString arg)
{
    tray->show_msg(arg);
}



// ----- public slots ----- //
void MainWindow::custom_quit()
{
    settings->save();
    QApplication::quit();
}

void MainWindow::do_print_screen()
// To help handle the PrintScreen key selection
{
    if (is_print_screen_enabled)
    {
        if (ui->combo_box->currentText() == "Snipe")
            do_snipe();
        if (ui->combo_box->currentText() == "Full screenshot")
            do_screenshot();
    }
}

void MainWindow::do_screenshot()
{
    bool current_visibility = isVisible();
    hide();
    if (!in_shot)
        sh->do_screenshot();
    setVisible(current_visibility);
}

void MainWindow::do_snipe()
{
    bool current_visibility = isVisible();
    hide();
    if (!in_shot)
        sh->do_snipe();
    setVisible(current_visibility);
}
// ----- end public slots ----- //



// ----- private slots ----- //
// Help button
void MainWindow::on_btn_help_clicked()
{
    MsgBox(
                "What is all this?\n"
"This is a software that helps in taking screenshots\n"
"of your entire screen or an area of the screen.\n\n"

"How to use:\n"
"- Left click on the tray icon for a fast snipe\n"
"- Right click the tray icon for a menu where you\n"
"can select to snipe or take a full screenshot\n"
"- You can make your Print Screen key on the keyboard\n"
"do either of the two by enabling it in the settings menu"
);
}

// First group - misc settings
void MainWindow::on_cb_enable_clipboard_toggled(bool checked)
{
    is_copy_enabled = checked;
}

void MainWindow::on_cb_enable_tray_pop_up_toggled(bool checked)
{
    tray->set_enable_pop_up(checked);
}

void MainWindow::on_cb_enable_print_screen_key_toggled(bool checked)
{
    is_print_screen_enabled = checked;
    if (checked)
        kh->enable_hook();
    else
        kh->disable_hook();

    ui->combo_box->setEnabled(checked);
}

// Second group - quality slider
void MainWindow::on_quality_slider_valueChanged(int value)
{
    ui->lbl_qs_val->setText(QString::number(value));
}

// Third group - save settings
void MainWindow::on_cb_enable_autosave_toggled(bool checked)
{
    is_auto_save_enabled = checked;
}

void MainWindow::on_cb_custom_savepath_toggled(bool checked)
{
    ui->input_custom_path->setEnabled(checked);
    ui->btn_browse_dir->setEnabled(checked);
    if (!checked)
        ui->input_custom_path->setText(settings->default_save_path);
}

void MainWindow::on_btn_browse_dir_clicked()
{
    QFileDialog fdlg(this);
    fdlg.setViewMode(QFileDialog::List);
    fdlg.setFileMode(QFileDialog::Directory);
    fdlg.setOption(QFileDialog::ShowDirsOnly);

    fdlg.exec();
    ui->input_custom_path->setText(fdlg.directory().path());
}

void MainWindow::on_input_custom_path_textChanged(const QString &arg1)
{
    set_save_path(arg1);
    QDir path(arg1);

    if (!path.exists() || !path.isAbsolute())
        ui->input_custom_path->setStyleSheet("QLineEdit {background-color: red;}");
    else
        ui->input_custom_path->setStyleSheet("QLineEdit {background-color: white;}");
}

// The random buttons
void MainWindow::on_btn_snipe_clicked()
{
    do_snipe();
}

void MainWindow::on_btn_print_screen_clicked()
{
    do_screenshot();
}

// Select custom area
void MainWindow::on_btn_select_area_clicked()
{
    AreaSelector select;
    select.exec();
    set_selected_area(select.get_area());
    is_area_selected = true;
}

void MainWindow::on_btn_reset_area_clicked()
{
    ui->lbl_start_point->clear();
    ui->lbl_end_point->clear();
    is_area_selected = false;
}
// ----- end private slots ----- //
