import QtQuick 2.3



Rectangle {
    width: 60
    height: 100
    color: Qt.rgba(0.2, 0.2, 0.2, 1)

    /* To control this widget :
     *      1- Create a GaugeController object
     *      2- Add this line to you *.cpp :
                    <Ui::QtAppClass*>
                        -><widget name in .ui file>
                        ->rootContext()
                        ->setContextProperty("controller", <GaugeController);
            3- Update the widget's value with the following line :
                    <GaugeController>->setValue(<value>);

        Example (with a widget named 'battery' in .ui file) :
            Ui::QtAppClass* _ui;
            GaugeController* controller = new GaugeController(this);
            ui->battery->rootContext()->setContextProperty("controller", controller);
            controller->setValue(50);
        
        Note that <value> must be in range [0, 100].
     */
    property int value: controller.value

    // timer used to update the widget periodically
    Timer {
        id: repaintTimer
        running: false
        interval: 0
        onTriggered: {
            canvas.requestPaint()
        }
    }

    // main canvas
    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            var centreX = width / 2;
            var centreY = height / 2;
            var offset = 4;

            ctx.lineWidth = offset;
            ctx.lineJoin = "round";

            // colored background
            ctx.beginPath();
            ctx.rect(offset, height - offset, width - 2*offset, -controller.value * ((height - 4*offset)/100));
            if (controller.value < 20)
                ctx.fillStyle = "red";
            else if (controller.value < 40)
                ctx.fillStyle = "orange";
            else
                ctx.fillStyle = "green";
            ctx.fill();
            ctx.closePath();

            // inner lines
            var count = 5;
            var fractionHeight = (height - 2*offset)/count;
            for (var i = 1; i < count; i++)  {
                ctx.beginPath();
                ctx.moveTo(offset, 2*offset + i*fractionHeight);
                ctx.lineTo(width-offset, 2*offset + i*fractionHeight);
                ctx.strokeStyle = "gray";
                ctx.stroke();
                ctx.closePath();
            }

            // outer contour
            ctx.beginPath();
            ctx.moveTo(offset, 3*offset);
            ctx.lineTo(width-offset, 3*offset);
            ctx.lineTo(width-offset, height-offset);
            ctx.lineTo(offset, height-offset);
            ctx.lineTo(offset, 3*offset);
            ctx.strokeStyle = "gray";
            ctx.stroke();
            ctx.closePath();

            // top battery plug
            ctx.lineWidth = 3*offset;
            ctx.beginPath();
            ctx.moveTo(width/3, 2*offset);
            ctx.lineTo(2*width/3, 2*offset);
            ctx.strokeStyle = "gray";
            ctx.lineCap = "round";
            ctx.stroke();
            ctx.closePath();

            // re-draw the widget
            repaintTimer.start()
        }
    }
}