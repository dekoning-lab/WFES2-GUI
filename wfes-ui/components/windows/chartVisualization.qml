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

    width: 800
    minimumWidth: 800
    maximumWidth: 800
    height: 500
    minimumHeight: 500
    maximumHeight: 500

    // Select theme for the application.
    Universal.theme: Universal.Light

    color: Universal.chromeLowColor

    Component.onCompleted: {
        // Center window in screen.
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    onClosing: {
        rootChart.hide()
    }

    ChartView {
        id: chart1
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12

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

    ChartView {
        id: chart2
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12
        visible: false

        ValueAxis {
            id: axisY2
            gridVisible: true
            tickCount: 5
            min: 0
            max: 1
        }

        ValueAxis {
            id: axisX2
            min: 0
            max: 1
            gridVisible: true
            tickCount: 5
        }
    }

    Button {
        id: bt1
        text: "Data 1"
        enabled: false
        anchors {
            right: parent.right
        }
        onClicked: {
            chart1.visible = true
            chart2.visible = false

            bt1.enabled = false
            bt2.enabled = true
        }
    }

    Button {
        id: bt2
        text: "Data 2"
        enabled: true
        anchors {
            right: parent.right
            top: bt1.bottom
        }
        onClicked: {
            chart1.visible = false
            chart2.visible = true

            bt1.enabled = true
            bt2.enabled = false
        }
    }

    function updatePhaseTypeMomentsChart() {
        bt1.visible = false
        bt2.visible = false
        chart1.visible = true
        chart2.visible = false
        bt1.enabled = false
        bt2.enabled = true

        chart1.removeAllSeries()
        chart1.title = "Phase Type Moments"
        var line = chart1.createSeries(ChartView.SeriesTypeLine, "Moments", axisX, axisY);

        var input = outputControllerPhaseType.ui_moments
        var numbers = []
        for(var i = 0; i < input.length; i++) {
            numbers[i] = parseInt(input[i])
            line.append(i, numbers[i])
        }
        axisX.min = 0;
        axisX.max = i-1;

        axisY.min = 0;
        axisY.max = Math.max(...numbers) + 1;
    }

    function updatePhaseTypeDistChart() {
        bt1.visible = true
        bt2.visible = true
        chart1.visible = true
        chart2.visible = false
        bt1.enabled = false
        bt2.enabled = true

        chart1.removeAllSeries()
        chart2.removeAllSeries()
        chart1.title = "Phase Type Dist."
        chart2.title = "Phase Type Dist."

        var names = []

        var input = outputControllerPhaseType.ui_probs
        var numbers = []
        var maxY1 = 0
        var minY1 = 0
        var maxY2 = 0
        var minY2 = 0
        if(typeof(input) != "undefined") {
            var splitted = input[0].split(", ")
            var splitLength = splitted.length

            if(splitLength === 3) {
                names[0] = "Prob. substitution"
                names[1] = "Cumulative prob. of subs."
            }
            if(splitLength === 5) {
                names[0] = "Prob. of extinction"
                names[1] = "Prob. of fixation"
                names[2] = "Prob. of absorption (either)"
                names[3] = "Cumulative prob. of abs."
            }

            for(var i = 1; i < splitLength; i++) {
                var line;
                if(splitLength === 5 && i > 2 || splitLength === 3 && i > 1) {
                    line = chart2.createSeries(ChartView.SeriesTypeLine, names[i-1], axisX2, axisY2);
                } else {
                    line = chart1.createSeries(ChartView.SeriesTypeLine, names[i-1], axisX, axisY);
                }
                splitted = []
                numbers = []
                for(var j = 0; j < input.length; j++) {
                    splitted = input[j].split(", ")
                    numbers[j] = parseFloat(splitted[i])
                    line.append(j, numbers[j])
                }

                if(splitLength === 5 && i > 2 || splitLength === 3 && i > 1) {
                    if(Math.max(...numbers) > maxY2) maxY2 = Math.max(...numbers);
                } else {
                    if(Math.max(...numbers) > maxY1) maxY1 = Math.max(...numbers);
                }
            }

            axisY.max = maxY1
            axisY2.max = maxY2
            axisX.max = input.length;
            axisX2.max = input.length;

            console.log(maxY2)
            console.log(maxY1)
        }
    }

    function updateDistWfas() {
        bt1.visible = false
        bt2.visible = false
        chart1.visible = true
        chart2.visible = false
        bt1.enabled = false
        bt2.enabled = true

        chart1.removeAllSeries()
        chart1.title = "WFAF-S"
        var line = chart1.createSeries(ChartView.SeriesTypeLine, "Dist.", axisX, axisY);

        var input = outputControllerWfas.ui_probs
        var numbers = []
        for(var i = 0; i < input.length; i++) {
            numbers[i] = parseInt(input[i])
            line.append(i, numbers[i])
        }
        axisX.min = 0;
        axisX.max = i-1;

        axisY.min = 0;
        axisY.max = Math.max(...numbers) + 1;
    }

    function updateDistWfafle() {
        bt1.visible = false
        bt2.visible = false
        chart1.visible = true
        chart2.visible = false
        bt1.enabled = false
        bt2.enabled = true

        chart1.removeAllSeries()
        chart1.title = "WFAF-D"
        var line = chart1.createSeries(ChartView.SeriesTypeLine, "Dist.", axisX, axisY);

        var input = outputControllerWfafle.ui_probs
        var numbers = []
        for(var i = 0; i < input.length; i++) {
            numbers[i] = parseInt(input[i])
            line.append(i, numbers[i])
        }
        axisX.min = 0;
        axisX.max = i-1;

        axisY.min = 0;
        axisY.max = Math.max(...numbers) + 1;
    }

    function updateProbTimeDist(name) {
        bt1.visible = true
        bt2.visible = true
        chart1.visible = true
        chart2.visible = false
        bt1.enabled = false
        bt2.enabled = true

        chart1.removeAllSeries()
        chart2.removeAllSeries()
        chart1.title = name
        chart2.title = name

        var names = []

        var input = outputControllerTimeDist.ui_probs
        var numbers = []
        var maxY1 = 0
        var minY1 = 0
        var maxY2 = 0
        var minY2 = 0
        if(typeof(input) != "undefined") {
            var splitted = input[0].split(", ")
            var splitLength = splitted.length

            if(splitLength === 3) {
                names[0] = "Prob. substitution"
                names[1] = "Cumulative prob. of subs."
            }
            if(splitLength === 5) {
                names[0] = "Prob. of extinction"
                names[1] = "Prob. of fixation"
                names[2] = "Prob. of absorption (either)"
                names[3] = "Cumulative prob. of abs."
            }

            for(var i = 1; i < splitLength; i++) {
                var line;
                if(splitLength === 5 && i > 2 || splitLength === 3 && i > 1) {
                    line = chart2.createSeries(ChartView.SeriesTypeLine, names[i-1], axisX2, axisY2);
                } else {
                    line = chart1.createSeries(ChartView.SeriesTypeLine, names[i-1], axisX, axisY);
                }
                splitted = []
                numbers = []
                for(var j = 0; j < input.length; j++) {
                    splitted = input[j].split(", ")
                    numbers[j] = parseFloat(splitted[i])
                    line.append(j, numbers[j])
                }

                if(splitLength === 5 && i > 2 || splitLength === 3 && i > 1) {
                    if(Math.max(...numbers) > maxY2) maxY2 = Math.max(...numbers);
                } else {
                    if(Math.max(...numbers) > maxY1) maxY1 = Math.max(...numbers);
                }
            }

            axisY.max = maxY1
            axisY2.max = maxY2
            axisX.max = input.length;
            axisX2.max = input.length;

            console.log(maxY2)
            console.log(maxY1)
        }
    }
}
