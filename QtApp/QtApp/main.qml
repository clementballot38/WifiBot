import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    color: "#1e1e1e"
    width: 820
    height: 570

    GroupBox {
        id: groupBox
        x: 58
        y: 43
        width: 339
        height: 275
        title: qsTr("Group Box")
    }
}
