import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    color: "#1e1e1e"
    width: 820
    height: 570

    Text {
        id: text1
        x: 284
        y: 222
        color: "#ffffff"
        text: "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Invisible things</p></body></html>"
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        textFormat: Text.RichText
    }
}
