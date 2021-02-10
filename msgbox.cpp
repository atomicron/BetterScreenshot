#include "msgbox.h"

MsgBox::MsgBox(QString message)
{
    setText(message);
    exec();
}
