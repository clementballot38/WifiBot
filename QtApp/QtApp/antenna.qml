import QtQuick 2.3


Rectangle {
    width: 400
    height: 400
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

        Example (with a widget named 'global_gauge' in .ui file) :
            Ui::QtAppClass* _ui;
            GaugeController* controller = new GaugeController(this);
            ui->global_gauge->rootContext()->setContextProperty("controller", controller);
            controller->setValue(50);
        
        Note that <value> must be in range [-127, 127].
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


            // outer bar
            ctx.beginPath();
            if(controller.value < 70)
                ctx.strokeStyle = "green";
            else
                ctx.strokeStyle = "gray";
            ctx.lineWidth = 3;
            ctx.arc(centreX, centreY, width / 3, -2*Math.PI /3, 0);
            ctx.stroke();

            // middle bar
            ctx.beginPath();
            if(controller.value < 30)
                ctx.strokeStyle = "orange";
            else
                ctx.strokeStyle = "gray";
            ctx.lineWidth = 3;
            ctx.arc(centreX, centreY, width / 4, -2*Math.PI /3, 0);
            ctx.stroke();

            // inner bar
            ctx.beginPath();
            if(controller.value < 0)
                ctx.strokeStyle = "red";
            else
                ctx.strokeStyle = "gray";
            ctx.lineWidth = 3;
            ctx.arc(centreX, centreY, width / 6, -2*Math.PI /3, 0);
            ctx.stroke();

            // center dot
            ctx.beginPath();
            if(controller.value < -50)
                ctx.fillStyle = "red";
            else
                ctx.fillStyle = "gray";
            ctx.arc(centreX, centreY, width/15, 0, 2*Math.PI);
            ctx.fill();
            
            // re-draw the widget
            repaintTimer.start()
        }
    }
}