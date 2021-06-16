import QtQuick 2.3

Rectangle {
    width: 60
    height: 100
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
            ctx.rect(0, 100-controller.value, 60, controller.value);
            if (controller.value<25) {
            ctx.fillStyle="red";
            }
            else if (controller.value<50)
            {
             ctx.fillStyle="orange";
            }
            else if (controller.value>=50)
            {
             
            ctx.fillStyle="green";
            }
           
            ctx.fill();
          

          for (var i = 1; i < 10; i++)  {
                console.log(i)
                 ctx.beginPath();
            ctx.moveTo(0,i*10);
            ctx.lineTo(60,i*10);
            
            ctx.strokeStyle="black";
            ctx.stroke();
            }
           


            
            




            repaintTimer.start()
        }
    }
}