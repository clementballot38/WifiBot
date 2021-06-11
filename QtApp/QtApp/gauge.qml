import QtQuick 2.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4


CircularGauge {
    id: gauge
    objectName: "gauge"

    /* To control this widget :
     *      1- Create a GaugeController object
     *      2- Add this line to you *.cpp :
                    <Ui::QtAppClass*>
                        -><widget name in .ui file>
                        ->rootContext()
                        ->setContextProperty("controller", <GaugeController);
            3- Update the widget's value with the following line :
                    <GaugeController>->setValue(<value>);
            4- (optionnal) Set the min/max values of the gauge :
                    <GaugeController>->setMinValue(<value>);
                    <GaugeController>->setMaxValue(<value);

        Example (with a widget named 'global_gauge' in .ui file) :
            Ui::QtAppClass* _ui;
            GaugeController* controller = new GaugeController(this);
            ui->global_gauge->rootContext()->setContextProperty("controller", controller);
            controller->setMinValue(0);
            controller->setMaxValue(100);
            controller->setValue(50);
     */
    value: controller.value
    minimumValue: controller.minValue
    maximumValue: controller.maxValue

    style: CircularGaugeStyle {

        needle: Rectangle {
            y: outerRadius * 0.15
            implicitWidth: outerRadius * 0.03
            implicitHeight: outerRadius * 0.9
            antialiasing: true
            color: Qt.rgba(0.66, 0.3, 0, 1)
        }

        background: Rectangle {
            implicitWidth: gauge.width
            implicitHeight: gauge.height
            color: Qt.rgba(0.2, 0.2, 0.2, 1)
        }
    }
}