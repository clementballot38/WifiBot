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
            if(controller.value < 70)
                ctx.strokeStyle = "green";
            else
                ctx.strokeStyle = "gray";
            ctx.lineWidth = 3;
            ctx.arc(centreX, centreY, width / 3, -2*Math.PI /3, 0);
            ctx.stroke();

            ctx.beginPath();
            if(controller.value < 30)
                ctx.strokeStyle = "orange";
            else
                ctx.strokeStyle = "gray";
            ctx.lineWidth = 3;
            ctx.arc(centreX, centreY, width / 4, -2*Math.PI /3, 0);
            ctx.stroke();

            ctx.beginPath();
            if(controller.value < 0)
                ctx.strokeStyle = "red";
            else
                ctx.strokeStyle = "gray";
            ctx.lineWidth = 3;
            ctx.arc(centreX, centreY, width / 6, -2*Math.PI /3, 0);
            ctx.stroke();

            ctx.beginPath();
            if(controller.value < -50)
                ctx.fillStyle = "red";
            else
                ctx.fillStyle = "gray";
            ctx.arc(centreX, centreY, width/15, 0, 2*Math.PI);
            ctx.fill();
            
            repaintTimer.start()
        }
    }
}