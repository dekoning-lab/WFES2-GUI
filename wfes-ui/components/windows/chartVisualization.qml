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
            id: axisX
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 1
            tickCount: 5
        }

        // Plot line
        LineSeries {
            id: lineSeries0Chart1
            axisX: axisX
            axisY: axisY
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart1
            axisX: axisX
            axisY: axisY
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
            id: axisX2
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY2
            min: 0
            max: 1
            tickCount: 5
        }


        // Plot line
        LineSeries {
            id: lineSeries0Chart2
            axisX: axisX2
            axisY: axisY2
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart2
            axisX: axisX2
            axisY: axisY2
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

    function updatePhaseTypeDistChart() {
        var minMaxDist = chartResults.updateChart("Phase Type Dist.", chart1.series(0));
        var minMaxAcum = chartResults.updateChart("Phase Type Acum.", chart2.series(0));

        bt1.enabled = false
        bt2.enabled = true

        chart1.visible = true
        chart2.visible = false

        chart1.series(1).visible = false
        chart2.series(1).visible = false

        chart1.title = "Phase Type Dist."
        chart2.title = "Phase Type Dist."

        chart1.series(0).name = "Probability of subs."
        chart2.series(0).name = "Cumulative prob. of subs."

        axisY.min = minMaxDist.x
        axisY.max = minMaxDist.y
        axisX.min = 1
        axisX.max = lineSeries0Chart1.count

        axisY2.min = minMaxAcum.x
        axisY2.max = minMaxAcum.y
        axisX2.min = 1
        axisX2.max = lineSeries0Chart2.count

    }

    function updateDistWfas() {
        var minMaxDist = chartResults.updateChart("Wfas Dist.", chart1.series(0));

        bt1.enabled = false
        bt2.enabled = false

        chart1.visible = true
        chart2.visible = false

        chart1.series(1).visible = false
        chart2.series(1).visible = false

        chart1.title = "Wfas Dist."

        chart1.series(0).name = "Allele frequency distribution"

        axisY.min = minMaxDist.x
        axisY.max = minMaxDist.y
        axisX.min = 1
        axisX.max = lineSeries0Chart1.count
    }

    function updateDistWfafle() {
        var minMaxDist = chartResults.updateChart("Wfafle Dist.", chart1.series(0));

        bt1.enabled = false
        bt2.enabled = false

        chart1.visible = true
        chart2.visible = false

        chart1.series(1).visible = false
        chart2.series(1).visible = false

        chart1.title = "Wfafle Dist."

        chart1.series(0).name = "Allele frequency distribution"

        axisY.min = minMaxDist.x
        axisY.max = minMaxDist.y
        axisX.min = 1
        axisX.max = lineSeries0Chart1.count
    }

    function updateProbTimeDist(name) {
        if(name === "Time Dist.") {
            var minMaxExt = chartResults.updateChart("Time Dist. Ext.", chart1.series(0));
            var minMaxFix = chartResults.updateChart("Time Dist. Fix.", chart1.series(1));
            var minMaxAbs = chartResults.updateChart("Time Dist. Abs.", chart2.series(0));
            var minMaxAcum = chartResults.updateChart("Time Dist. Acum.", chart2.series(1));

            bt1.enabled = false
            bt2.enabled = true

            chart1.visible = true
            chart2.visible = false

            chart1.series(0).visible = true
            chart1.series(1).visible = true
            chart2.series(0).visible = true
            chart2.series(1).visible = true

            chart1.title = "Time Dist."
            chart2.title = "Time Dist."

            chart1.series(0).name = "Probability of ext."
            chart1.series(1).name = "Probability of fix."
            chart2.series(0).name = "Probability of abs."
            chart2.series(1).name = "Cumulative prob. of abs."

            axisY.min = Math.min (minMaxExt.x, minMaxFix.x)
            axisY.max = Math.max(minMaxExt.y, minMaxFix.y)
            axisX.min = 1
            axisX.max = lineSeries0Chart1.count

            axisY2.min = Math.min (minMaxAbs.x, minMaxAcum.x)
            axisY2.max = Math.max(minMaxAbs.y, minMaxAcum.y)
            axisX2.min = 1
            axisX2.max = lineSeries0Chart2.count
        } else if(name === "Time Dist. SGV") {
            var minMaxSGVSubs = chartResults.updateChart("Time Dist. SGV Sub.", chart1.series(0));
            var minMaxSGVAcum = chartResults.updateChart("Time Dist. SGV Acum.", chart2.series(0));

            bt1.enabled = false
            bt2.enabled = true

            chart1.visible = true
            chart2.visible = false

            chart1.series(1).visible = false
            chart2.series(1).visible = false

            chart1.title = "Time Dist. SGV"
            chart2.title = "Time Dist. SGV"

            chart1.series(0).name = "Probability of subs."
            chart2.series(0).name = "Cumulative prob. of subs."

            axisY.min = minMaxSGVSubs.x
            axisY.max = minMaxSGVSubs.y
            axisX.min = 1
            axisX.max = lineSeries0Chart1.count

            axisY2.min = minMaxSGVAcum.x
            axisY2.max = minMaxSGVAcum.y
            axisX2.min = 1
            axisX2.max = lineSeries0Chart2.count
        } else if(name === "Time Dist. Skip") {
            var minMaxSkipSubs = chartResults.updateChart("Time Dist. Skip Sub.", chart1.series(0));
            var minMaxSkipAcum = chartResults.updateChart("Time Dist. Skip Acum.", chart2.series(0));

            bt1.enabled = false
            bt2.enabled = true

            chart1.visible = true
            chart2.visible = false

            chart1.series(1).visible = false
            chart2.series(1).visible = false

            chart1.title = "Time Dist. Skip"
            chart2.title = "Time Dist. Skip"

            chart1.series(0).name = "Probability of subs."
            chart2.series(0).name = "Cumulative prob. of subs."

            axisY.min = minMaxSkipSubs.x
            axisY.max = minMaxSkipSubs.y
            axisX.min = 1
            axisX.max = lineSeries0Chart1.count

            axisY2.min = minMaxSkipAcum.x
            axisY2.max = minMaxSkipAcum.y
            axisX2.min = 1
            axisX2.max = lineSeries0Chart2.count
        } else if(name === "Time Dist. Dual") {
            var minMaxDualExt = chartResults.updateChart("Time Dist. Dual Ext.", chart1.series(0));
            var minMaxDualFix = chartResults.updateChart("Time Dist. Dual Fix.", chart1.series(1));
            var minMaxDualAbs = chartResults.updateChart("Time Dist. Dual Abs.", chart2.series(0));
            var minMaxDualAcum = chartResults.updateChart("Time Dist. Dual Acum.", chart2.series(1));

            bt1.enabled = false
            bt2.enabled = true

            chart1.visible = true
            chart2.visible = false

            chart1.series(0).visible = true
            chart1.series(1).visible = true
            chart2.series(0).visible = true
            chart2.series(1).visible = true

            chart1.title = "Time Dist. Dual"
            chart2.title = "Time Dist. Dual"

            chart1.series(0).name = "Probability of ext."
            chart1.series(1).name = "Probability of fix."
            chart2.series(0).name = "Probability of abs."
            chart2.series(1).name = "Cumulative prob. of abs."

            axisY.min = Math.min (minMaxDualExt.x, minMaxDualFix.x)
            axisY.max = Math.max(minMaxDualExt.y, minMaxDualFix.y)
            axisX.min = 1
            axisX.max = lineSeries0Chart1.count

            axisY2.min = Math.min (minMaxDualAbs.x, minMaxDualAcum.x)
            axisY2.max = Math.max(minMaxDualAbs.y, minMaxDualAcum.y)
            axisX2.min = 1
            axisX2.max = lineSeries0Chart2.count
        }
    }
}
