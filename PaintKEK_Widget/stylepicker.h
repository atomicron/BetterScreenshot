#ifndef STYLEPICKER_H
#define STYLEPICKER_H

#include <QDialog>
#include <QDebug>
#include <QRadioButton>

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

private slots:
    void get_values();
};

#endif // STYLEPICKER_H
