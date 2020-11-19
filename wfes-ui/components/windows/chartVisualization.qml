import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtCharts 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import assets 1.0
import components 1.0

ApplicationWindow {
    property alias visibleWindow: rootChart.visible

    id: rootChart
    title: qsTr("WFES - Wright-Fisher Exact Solver")

    visible: visibleWindow

    width: 500
    minimumWidth: 500
    maximumWidth: 500
    height: 500
    minimumHeight: 500
    maximumHeight: 500

    // Select theme for the application.
    Universal.theme: Universal.Light

    color: Universal.chromeLowColor

    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    onClosing: {
        rootChart.hide()
    }

    ChartView {
            id: myChart
            title: ""
            anchors.fill: parent
            antialiasing: true
            anchors { fill: parent; margins: -10 }

            ValueAxis {
                id: axisY
                gridVisible: true
                tickCount: 5
                min: 0
                max: 1
            }

            ValueAxis {
                id: axisX
                min: 0
                max: 1
                gridVisible: true
                tickCount: 5
            }

        }

    function updatePhaseTypeMomentsChart() {
        myChart.removeAllSeries()
        var line = myChart.createSeries(ChartView.SeriesTypeLine, "Phase Type Moments", axisX, axisY);

        var input = outputControllerPhaseType.ui_moments
        var numbers = []
        for(var i = 0; i < input.length; i++) {
            numbers[i] = parseInt(input[i])
            line.append(i, numbers[i])
        }
        axisX.min = 0;
        axisX.max = i-1;

        axisY.min = 0;
        axisY.max = Math.max(...numbers);;

    }

    function updateProbsChart() {
        myChart.removeAllSeries()
        var line = myChart.createSeries(ChartView.SeriesTypeLine, "Phase Type Moments", axisX, axisY);

        var input = outputControllerTimeDist.ui_
        var numbers = []
        for(var i = 0; i < input.length; i++) {
            numbers[i] = parseInt(input[i])
            line.append(i, numbers[i])
        }
        axisX.min = 0;
        axisX.max = i-1;

        axisY.min = 0;
        axisY.max = Math.max(...numbers);;

    }
}
