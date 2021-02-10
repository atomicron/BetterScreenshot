#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "msgbox.h"

#include <QDebug> // remove later
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

//    kh = &KeyHandler().Instance(this);

    kh->enable_hook();
    settings->load();

}

MainWindow::~MainWindow()
{
    qDebug() << "Disabling hook and destroying kh, tray";
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

void MainWindow::on_quality_slider_valueChanged(int value)
{
   ui->lbl_qs_val->setText(QString::number(value));
}
