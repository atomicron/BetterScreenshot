#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "msgbox.h"

#include "areaselector.h"

#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tray(new Tray(this))
//    , kh(new KeyHandler(this))
    , kh(&KeyHandler().Instance(this))
    , settings(new Settings(this))
    , sh(new ScreenHandler(this))
{
    ui->setupUi(this);
    kh->enable_hook();
    settings->load();
}

MainWindow::~MainWindow()
{
    kh->disable_hook();
    delete ui;
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::do_snapshot()
{
    sh->do_screenshot();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

QString MainWindow::get_custom_save_path()
{
    return ui->input_custom_path->text();
}

void MainWindow::set_custom_save_path(QString path)
{
   ui->input_custom_path->setText(path);
}

bool MainWindow::is_custom_save()
{
    return ui->cb_custom_savepath->isChecked();
}

void MainWindow::set_custom_save(bool b)
{
    ui->cb_custom_savepath->setChecked(b);
}

int MainWindow::get_quality()
{
    return ui->quality_slider->value();
}

void MainWindow::set_quality(int val)
{
   ui->quality_slider->setValue(val);
}

const QRect MainWindow::get_selected_area() const
{
    return selected_area;
}

void MainWindow::set_enable_crop(bool b)
{
    is_crop_enabled = b;
    ui->cb_enable_crop->setChecked(b);
}

void MainWindow::set_enable_copy(bool b)
{
    is_copy_enabled = b;
    ui->cb_enable_clipboard->setChecked(b);
}

void MainWindow::set_enable_auto_save(bool b)
{
   is_auto_save_enabled = b;
   ui->cb_enable_autosave->setChecked(b);
}
#include <QDebug>
void MainWindow::set_selected_area(QRect rect)
{
    ui->lbl_start_point->setText("Start point: " + QString::number(rect.topLeft().x()) +','+ QString::number(rect.topLeft().y()));
    ui->lbl_end_point->setText("End point: " + QString::number(rect.bottomRight().x()) +','+ QString::number(rect.bottomRight().y()));
    qDebug() << "Select area set to: " << rect.size();
    if (rect.size()==QSize(0,0))
    {
        ui->lbl_end_point->clear();
        ui->lbl_start_point->clear();
    }
    else
        selected_area = rect;
}

void MainWindow::tray_say(QString arg)
{
   tray->show_msg(arg);
}

void MainWindow::on_cb_custom_savepath_toggled(bool checked)
{
    ui->input_custom_path->setEnabled(checked);
    ui->btn_browse_dir->setEnabled(checked);
    if (checked)
        ui->input_custom_path->setText(settings->get_default_save_path());
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

void MainWindow::on_btn_save_clicked()
{
    const QString entered_path = ui->input_custom_path->text();
    QDir dir(entered_path);
    if (!dir.exists())
    {
        if (!QDir().mkdir(entered_path) || !dir.isAbsolute())
        {
            MsgBox("Cannot create custom save path\n" + entered_path);
        }
    }
    settings->save();
    MsgBox("Saved");
}

void MainWindow::on_btn_quit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_btn_select_area_clicked()
{
    AreaSelector select;
    select.exec();
    selected_area = select.get_area();
    set_selected_area(selected_area);
}

void MainWindow::on_btn_reset_area_clicked()
{
    selected_area = QRect(0,0,0,0);
    ui->lbl_start_point->clear();
    ui->lbl_end_point->clear();
}

void MainWindow::on_quality_slider_valueChanged(int value)
{
    ui->lbl_qs_val->setText(QString::number(value));
}


void MainWindow::on_cb_enable_crop_toggled(bool checked)
{
    is_crop_enabled = checked;
}

void MainWindow::on_cb_enable_autosave_toggled(bool checked)
{
    is_auto_save_enabled = checked;
}

void MainWindow::on_cb_enable_clipboard_toggled(bool checked)
{
    is_copy_enabled = checked;
}
