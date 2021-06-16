import QtQuick 2.3

Rectangle {
    width: 400
    height: 400
    color: Qt.rgba(0.2, 0.2, 0.2, 1)
    property int value: controller.value

    Timer {
        id: repaintTimer
        running: false
        interval: 0
        onTriggered: {
            canvas.requestPaint()
        }
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            var centreX = width / 2;
            var centreY = height / 2;


            ctx.beginPath();
            if(controller.value<40)
            ctx.rect(10, 10, 100, 100);

            else 
            ctx.rect(10, 30,100,100);
            ctx.fillStyle="red";
            ctx.fill;



            repaintTimer.start()
        }
    }
}