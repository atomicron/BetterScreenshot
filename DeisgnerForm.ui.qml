import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 400
    height: 400

    RowLayout {
        id: rowLayout
        x: 45
        y: 58
        width: 230
        height: 192

        CheckBox {
            id: checkBox
            text: qsTr("Check Box")
        }

        CheckBox {
            id: checkBox1
            text: qsTr("Check Box")
        }
    }

}
