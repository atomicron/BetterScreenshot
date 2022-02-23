#ifndef STYLEPICKER_H
#define STYLEPICKER_H

#include <QDialog>
#include <QDebug>
#include <QRadioButton>

#include <QScrollArea>
#include <QVBoxLayout>


#if QT_VERSION == 0x041000
// Works in Qt Creator 4.10.0
#include <QDesktopWidget>
#endif

#if QT_VERSION == 0x050003
// Works in Qt Creator 5.0.3
#include  <QDesktopServices>
#endif

namespace Ui {
class StylePicker;
}

class StylePicker : public QDialog
{
    Q_OBJECT

    int style_id;
    int cap_id;
    int join_id;

public:
    explicit StylePicker(QWidget *parent = nullptr);
    ~StylePicker();

    Qt::PenStyle style();
    Qt::PenCapStyle cap();
    Qt::PenJoinStyle join();

private:
    Ui::StylePicker *ui;

    QScrollArea* scrollArea;

private slots:
    void get_values();
};

#endif // STYLEPICKER_H
