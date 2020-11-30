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
        id: chart1Linear
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12

        ValueAxis {
            id: axisXLinear
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisYLinear
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%.2e"
        }

        // Plot line
        LineSeries {
            id: lineSeries0Chart1
            axisX: axisXLinear
            axisY: axisYLinear
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart1
            axisX: axisXLinear
            axisY: axisYLinear
        }

    }

    ChartView {
        id: chart2Linear
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12
        visible: false

        ValueAxis {
            id: axisX2Linear
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY2Linear
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%.2e"
        }


        // Plot line
        LineSeries {
            id: lineSeries0Chart2
            axisX: axisX2Linear
            axisY: axisY2Linear
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart2
            axisX: axisX2Linear
            axisY: axisY2Linear
        }

    }

    ChartView {
        id: chart3Linear
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12
        visible: false

        ValueAxis {
            id: axisX3Linear
            objectName: "Linear"
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY3Linear
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%.2e"
        }

        // Plot line
        LineSeries {
            id: lineSeries0Chart3
            axisX: axisX3Linear
            axisY: axisY3Linear
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart3
            axisX: axisX3Linear
            axisY: axisY3Linear
        }

    }

    ChartView {
        id: chart1Log
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12
        visible: false

        LogValueAxis {
            id:axisX1Log
            objectName: "Log"
            min: 0
            max: 1
            base: 10
            minorTickCount: 0
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY1Log
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%.2e"
        }

        // Plot line
        LineSeries {
            id: lineSeries0Chart1Log
            axisX: axisX1Log
            axisY: axisY1Log
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart1Log
            axisX: axisX1Log
            axisY: axisY1Log
        }

    }

    ChartView {
        id: chart2Log
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12
        visible: false

        LogValueAxis {
            id:axisX2Log
            objectName: "Log"
            min: 0
            max: 1
            base: 10
            minorTickCount: 0
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY2Log
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%.2e"
        }

        // Plot line
        LineSeries {
            id: lineSeries0Chart2Log
            axisX: axisX2Log
            axisY: axisY2Log
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart2Log
            axisX: axisX2Log
            axisY: axisY2Log
        }

    }

    ChartView {
        id: chart3Log
        title: "A chart will appear here when you execute an executable with Dist, Moments or Probs (P)."
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: -10 }
        legend.alignment: Qt.AlignRight
        legend.font.pointSize: 12
        visible: false

        LogValueAxis {
            id:axisX3Log
            objectName: "Log"
            min: 0
            max: 1
            base: 10
            minorTickCount: 0
            labelFormat: "%i"
        }

        ValueAxis {
            id: axisY3Log
            min: 0
            max: 1
            tickCount: 5
            labelFormat: "%.2e"
        }

        // Plot line
        LineSeries {
            id: lineSeries0Chart3Log
            axisX: axisX3Log
            axisY: axisY3Log
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart3Log
            axisX: axisX3Log
            axisY: axisY3Log
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
            if(scaleButton.text != "Linear Scale") {
                chart1Linear.visible = true
                chart2Linear.visible = false
                chart3Linear.visible = false
                chart1Log.visible = false
                chart2Log.visible = false
                chart3Log.visible = false
            } else {
                chart1Linear.visible = false
                chart2Linear.visible = false
                chart3Linear.visible = false
                chart1Log.visible = true
                chart2Log.visible = false
                chart3Log.visible = false
            }
                bt1.enabled = false
                bt2.enabled = true
                bt3.enabled = true
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
            if(scaleButton.text != "Linear Scale") {
                chart1Linear.visible = false
                chart2Linear.visible = true
                chart3Linear.visible = false
                chart1Log.visible = false
                chart2Log.visible = false
                chart3Log.visible = false
            } else {
                chart1Linear.visible = false
                chart2Linear.visible = false
                chart3Linear.visible = false
                chart1Log.visible = false
                chart2Log.visible = true
                chart3Log.visible = false
            }
            bt1.enabled = true
            bt2.enabled = false
            bt3.enabled = true
        }
    }

    Button {
        id: bt3
        text: "Data 3"
        enabled: true
        anchors {
            right: parent.right
            top: bt2.bottom
        }
        onClicked: {
            if(scaleButton.text != "Linear Scale") {
                chart1Linear.visible = false
                chart2Linear.visible = false
                chart3Linear.visible = true
                chart1Log.visible = false
                chart2Log.visible = false
                chart3Log.visible = false
            } else {
                chart1Linear.visible = false
                chart2Linear.visible = false
                chart3Linear.visible = false
                chart1Log.visible = false
                chart2Log.visible = false
                chart3Log.visible = true
            }
            bt1.enabled = true
            bt2.enabled = true
            bt3.enabled = false
        }
    }

    Button {
        id: scaleButton
        text: "Log10 Scale"
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        onClicked: {
            if(scaleButton.text == "Log10 Scale") {
                scaleButton.text = "Linear Scale"
                if(chart1Linear.visible) {
                    chart1Linear.visible = false
                    chart1Log.visible = true
                }
                if(chart2Linear.visible) {
                    chart2Linear.visible = false
                    chart2Log.visible = true
                }
                if(chart3Linear.visible) {
                    chart3Linear.visible = false
                    chart3Log.visible = true
                }
            } else if(scaleButton.text == "Linear Scale") {
                scaleButton.text = "Log10 Scale"
                if(chart1Log.visible) {
                    chart1Log.visible = false
                    chart1Linear.visible = true
                }
                if(chart2Log.visible) {
                    chart2Log.visible = false
                    chart2Linear.visible = true
                }
                if(chart3Log.visible) {
                    chart3Log.visible = false
                    chart3Linear.visible = true
                }
            }
        }
    }

    function enableButtons(bt1_enabled, bt2_enabled, bt3_enabled) {
        bt1.enabled = bt1_enabled
        bt2.enabled = bt2_enabled
        bt3.enabled = bt3_enabled
    }

    function visibleButtons(bt1_visible, bt2_visible, bt3_visible) {
        bt1.visible = bt1_visible
        bt2.visible = bt2_visible
        bt3.visible = bt3_visible
    }

    function visibleChart(chart1_visible, chart2_visible, chart3_visible) {
        if(scaleButton.text != "Linear Scale") {
            chart1Linear.visible = chart1_visible
            chart2Linear.visible = chart2_visible
            chart3Linear.visible = chart3_visible
            chart1Log.visible = false
            chart2Log.visible = false
            chart3Log.visible = false
        } else if (scaleButton.text != "Log10 Scale"){
            chart1Linear.visible = false
            chart1Linear.visible = false
            chart1Linear.visible = false
            chart1Log.visible = chart1_visible
            chart2Log.visible = chart2_visible
            chart3Log.visible = chart3_visible
        }
    }

    function visibleSeries(char1_serie1, chart1_serie2, chart2_serie1, chart2_serie2, chart3_serie1, chart3_serie2) {
        chart1Linear.series(0).visible = char1_serie1
        chart1Linear.series(1).visible = chart1_serie2
        chart2Linear.series(0).visible = chart2_serie1
        chart2Linear.series(1).visible = chart2_serie2
        chart3Linear.series(0).visible = chart3_serie1
        chart3Linear.series(1).visible = chart3_serie2
        chart1Log.series(0).visible = char1_serie1
        chart1Log.series(1).visible = chart1_serie2
        chart2Log.series(0).visible = chart2_serie1
        chart2Log.series(1).visible = chart2_serie2
        chart3Log.series(0).visible = chart3_serie1
        chart3Log.series(1).visible = chart3_serie2
    }

    function setTitle(title) {
        chart1Linear.title = "Phase Type Dist."
        chart2Linear.title = "Phase Type Dist."
        chart3Linear.title = "Phase Type Dist."
        chart1Log.title = "Phase Type Dist."
        chart2Log.title = "Phase Type Dist."
        chart3Log.title = "Phase Type Dist."
    }

    function setSeriesName(char1_serie1, chart1_serie2, chart2_serie1, chart2_serie2, chart3_serie1, chart3_serie2) {
        chart1Linear.series(0).name = char1_serie1
        chart1Linear.series(1).name = chart1_serie2
        chart2Linear.series(0).name = chart2_serie1
        chart2Linear.series(1).name = chart2_serie2
        chart3Linear.series(0).name = chart3_serie1
        chart3Linear.series(1).name = chart3_serie2
        chart1Log.series(0).name = char1_serie1
        chart1Log.series(1).name = chart1_serie2
        chart2Log.series(0).name = chart2_serie1
        chart2Log.series(1).name = chart2_serie2
        chart3Log.series(0).name = chart3_serie1
        chart3Log.series(1).name = chart3_serie2
    }

    function setValuesAxis(axisX, axisY, minX, maxX, minY, maxY) {
        axisY.min = minY
        axisY.max = maxY
        axisX.min = minX
        axisX.max = maxX
    }

    function updatePhaseTypeDistChart() {
        var minMaxDist = chartResults.updateChart("Phase Type Dist.", chart1Linear.series(0));
        var minMaxAcum = chartResults.updateChart("Phase Type Acum.", chart2Linear.series(0));
        minMaxDist = chartResults.updateChart("Phase Type Dist.", chart1Log.series(0));
        minMaxAcum = chartResults.updateChart("Phase Type Acum.", chart2Log.series(0));

        visibleButtons(true, true, false)
        enableButtons(false, true, true)

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("Phase Type Dist.")

        setSeriesName("Probability of subs.", "", "Cumulative prob. of subs.", "", "", "")

        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDist.x, minMaxDist.y)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDist.x, minMaxDist.y)

        setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxAcum.x, minMaxAcum.y)
        setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxAcum.x, minMaxAcum.y)
    }

    function updateDistWfas() {
        var minMaxDist = chartResults.updateChart("Wfas Dist.", chart1Linear.series(0));
        minMaxDist = chartResults.updateChart("Wfas Dist.", chart1Log.series(0));

        visibleButtons(true, false, false)
        enableButtons(false, true, true)

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("Wfas Dist.")

        setSeriesName("Allele frequency distribution", "", "", "", "", "")

        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDist.x, minMaxDist.y)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDist.x, minMaxDist.y)
    }

    function updateDistWfafle() {
        var minMaxDist = chartResults.updateChart("Wfafle Dist.", chart1Linear.series(0));
        minMaxDist = chartResults.updateChart("Wfafle Dist.", chart1Log.series(0));

        visibleButtons(true, false, false)
        enableButtons(false, true, true)

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("Wfas Dist.")

        setSeriesName("Allele frequency distribution", "", "", "", "", "")

        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDist.x, minMaxDist.y)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDist.x, minMaxDist.y)
    }

    function updateProbTimeDist(name) {
        var minChart3;
        var maxChart3;
        if(name === "Time Dist.") {
            var minMaxExt = chartResults.updateChart("Time Dist. Ext.", chart1Linear.series(0));
            var minMaxFix = chartResults.updateChart("Time Dist. Fix.", chart2Linear.series(0));
            var minMaxAbs = chartResults.updateChart("Time Dist. Abs.", chart3Linear.series(0));
            var minMaxAcum = chartResults.updateChart("Time Dist. Acum.", chart3Linear.series(1));
            minMaxExt = chartResults.updateChart("Time Dist. Ext.", chart1Log.series(0));
            minMaxFix = chartResults.updateChart("Time Dist. Fix.", chart2Log.series(0));
            minMaxAbs = chartResults.updateChart("Time Dist. Abs.", chart3Log.series(0));
            minMaxAcum = chartResults.updateChart("Time Dist. Acum.", chart3Log.series(1));

            visibleButtons(true, true, true)
            enableButtons(false, true, true)

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, true, true)

            setTitle("Time Dist.")

            setSeriesName("Probability of ext.", "", "Probability of fix.", "", "Probability of abs.", "Cumulative prob. of abs.")

            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxExt.x, minMaxExt.y)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxExt.x, minMaxExt.y)

            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxFix.x, minMaxFix.y)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxFix.x, minMaxFix.y)

            minChart3 = Math.min(minMaxAbs.x, minMaxAcum.x)
            maxChart3 = Math.max(minMaxAbs.y, minMaxAcum.y)

            setValuesAxis(axisX3Linear, axisY3Linear, 1, lineSeries0Chart3.count, minChart3, maxChart3)
            setValuesAxis(axisX3Log, axisY3Log, 1, lineSeries0Chart3Log.count, minChart3, maxChart3)

            setValuesAxis(axisX3Linear, axisY3Linear, 1, lineSeries1Chart3.count, minChart3, maxChart3)
            setValuesAxis(axisX3Log, axisY3Log, 1, lineSeries1Chart3Log.count, minChart3, maxChart3)
        } else if(name === "Time Dist. SGV") {
            var minMaxSGVSubs = chartResults.updateChart("Time Dist. SGV Sub.", chart1Linear.series(0));
            var minMaxSGVAcum = chartResults.updateChart("Time Dist. SGV Acum.", chart2Linear.series(0));
            minMaxSGVSubs = chartResults.updateChart("Time Dist. SGV Sub.", chart1Log.series(0));
            minMaxSGVAcum = chartResults.updateChart("Time Dist. SGV Acum.", chart2Log.series(0));

            visibleButtons(true, true, false)
            enableButtons(false, true, true)

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, false, false)

            setTitle("Time Dist. SGV")

            setSeriesName("Probability of subs.", "", "Cumulative prob. of subs.", "", "", "")

            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxSGVSubs.x, minMaxSGVSubs.y)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxSGVSubs.x, minMaxSGVSubs.y)

            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxSGVAcum.x, minMaxSGVAcum.y)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxSGVAcum.x, minMaxSGVAcum.y)
        } else if(name === "Time Dist. Skip") {
            var minMaxSkipSubs = chartResults.updateChart("Time Dist. Skip Sub.", chart1Linear.series(0));
            var minMaxSkipAcum = chartResults.updateChart("Time Dist. Skip Acum.", chart2Linear.series(0));
            minMaxSkipSubs = chartResults.updateChart("Time Dist. Skip Sub.", chart1Log.series(0));
            minMaxSkipAcum = chartResults.updateChart("Time Dist. Skip Acum.", chart2Log.series(0));

            visibleButtons(true, true, false)
            enableButtons(false, true, true)

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, false, false)

            setTitle("Time Dist. Skip")

            setSeriesName("Probability of subs.", "", "Cumulative prob. of subs.", "", "", "")

            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxSkipSubs.x, minMaxSkipSubs.y)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxSkipSubs.x, minMaxSkipSubs.y)

            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxSkipAcum.x, minMaxSkipAcum.y)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxSkipAcum.x, minMaxSkipAcum.y)

        } else if(name === "Time Dist. Dual") {
            var minMaxDualExt = chartResults.updateChart("Time Dist. Dual Ext.", chart1Linear.series(0));
            var minMaxDualFix = chartResults.updateChart("Time Dist. Dual Fix.", chart2Linear.series(0));
            var minMaxDualAbs = chartResults.updateChart("Time Dist. Dual Abs.", chart3Linear.series(0));
            var minMaxDualAcum = chartResults.updateChart("Time Dist. Dual Acum.", chart3Linear.series(1));
            minMaxDualExt = chartResults.updateChart("Time Dist. Dual Ext.", chart1Log.series(0));
            minMaxDualFix = chartResults.updateChart("Time Dist. Dual Fix.", chart2Log.series(0));
            minMaxDualAbs = chartResults.updateChart("Time Dist. Dual Abs.", chart3Log.series(0));
            minMaxDualAcum = chartResults.updateChart("Time Dist. Dual Acum.", chart3Log.series(1));

            visibleButtons(true, true, true)
            enableButtons(false, true, true)

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, true, true)

            setTitle("Time Dist. Dual")

            setSeriesName("Probability of ext.", "", "Probability of fix.", "", "Probability of abs.", "Cumulative prob. of abs.")

            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDualExt.x, minMaxDualExt.y)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDualExt.x, minMaxDualExt.y)

            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxDualFix.x, minMaxDualFix.y)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxDualFix.x, minMaxDualFix.y)

            minChart3 = Math.min(minMaxDualAbs.x, minMaxDualAcum.x)
            maxChart3 = Math.max(minMaxDualAbs.y, minMaxDualAcum.y)

            setValuesAxis(axisX3Linear, axisY3Linear, 1, lineSeries0Chart3.count, minChart3, maxChart3)
            setValuesAxis(axisX3Log, axisY3Log, 1, lineSeries0Chart3Log.count, minChart3, maxChart3)

            setValuesAxis(axisX3Linear, axisY3Linear, 1, lineSeries1Chart3.count, minChart3, maxChart3)
            setValuesAxis(axisX3Log, axisY3Log, 1, lineSeries1Chart3Log.count, minChart3, maxChart3)
        }
    }
}
