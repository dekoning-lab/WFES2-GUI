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
    property alias visibleWindow: rootChartVisualization.visible

    id: rootChartVisualization
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.charts + ")"

    visible: visibleWindow

    width: 800
    minimumWidth: 800
    maximumWidth: 800
    height: 500
    minimumHeight: 500
    maximumHeight: 500

    // Select theme for the application.
    Universal.theme: Universal.Light

    color: "white"

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootChartVisualization.close()
    }

    Component.onCompleted: {
        // Center window in screen.
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    onClosing: {
        rootChartVisualization.hide()
    }

    ChartView {
        id: chart1Linear
        title: Strings.nonGeneratedChart
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: 10;}
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
            useOpenGL: true
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart1
            axisX: axisXLinear
            axisY: axisYLinear
            useOpenGL: true
        }

    }

    ChartView {
        id: chart2Linear
        title: Strings.nonGeneratedChart
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: 10;}
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
            useOpenGL: true
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart2
            axisX: axisX2Linear
            axisY: axisY2Linear
            useOpenGL: true
        }

    }

    ChartView {
        id: chart3Linear
        title: Strings.nonGeneratedChart
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: 10;}
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
            useOpenGL: true
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart3
            axisX: axisX3Linear
            axisY: axisY3Linear
            useOpenGL: true
        }

    }

    ChartView {
        id: chart1Log
        title: Strings.nonGeneratedChart
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: 10;}
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
            useOpenGL: true
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart1Log
            axisX: axisX1Log
            axisY: axisY1Log
            useOpenGL: true
        }

    }

    ChartView {
        id: chart2Log
        title: Strings.nonGeneratedChart
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: 10;}
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
            useOpenGL: true
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart2Log
            axisX: axisX2Log
            axisY: axisY2Log
            useOpenGL: true
        }

    }

    ChartView {
        id: chart3Log
        title: Strings.nonGeneratedChart
        anchors.fill: parent
        antialiasing: true
        anchors { fill: parent; margins: 10;}
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
            useOpenGL: true
        }

        // Plot line
        LineSeries {
            id: lineSeries1Chart3Log
            axisX: axisX3Log
            axisY: axisY3Log
            useOpenGL: true
        }

    }

    ColumnLayout {

        anchors {
            top: parent.top
            right: parent.right
        }

        Button {
            id: bt1
            text: Strings.dataText + "1"

            Layout.preferredWidth: 100

            enabled: false

            onClicked: {
                if(scaleButton.checked) {
                    chart1Linear.visible = false
                    chart2Linear.visible = false
                    chart3Linear.visible = false
                    chart1Log.visible = true
                    chart2Log.visible = false
                    chart3Log.visible = false
                } else {
                    chart1Linear.visible = true
                    chart2Linear.visible = false
                    chart3Linear.visible = false
                    chart1Log.visible = false
                    chart2Log.visible = false
                    chart3Log.visible = false
                }
                bt1.enabled = false
                bt2.enabled = true
                bt3.enabled = true

                maxYValue.textFieldText = axisYLinear.max.toExponential(4);
                minYValue.textFieldText = axisYLinear.min.toExponential(4);
            }
        }

        Button {
            id: bt2
            text: Strings.dataText + "2"

            Layout.preferredWidth: 100

            enabled: true

            onClicked: {
                if(scaleButton.checked) {
                    chart1Linear.visible = false
                    chart2Linear.visible = false
                    chart3Linear.visible = false
                    chart1Log.visible = false
                    chart2Log.visible = true
                    chart3Log.visible = false
                } else {
                    chart1Linear.visible = false
                    chart2Linear.visible = true
                    chart3Linear.visible = false
                    chart1Log.visible = false
                    chart2Log.visible = false
                    chart3Log.visible = false
                }
                bt1.enabled = true
                bt2.enabled = false
                bt3.enabled = true

                maxYValue.textFieldText = axisY2Linear.max.toExponential(4);
                minYValue.textFieldText = axisY2Linear.min.toExponential(4);
            }
        }

        Button {
            id: bt3
            text: Strings.dataText + "3"

            Layout.preferredWidth: 100

            enabled: true

            onClicked: {
                if(scaleButton.checked) {
                    chart1Linear.visible = false
                    chart2Linear.visible = false
                    chart3Linear.visible = false
                    chart1Log.visible = false
                    chart2Log.visible = false
                    chart3Log.visible = true
                } else {
                    chart1Linear.visible = false
                    chart2Linear.visible = false
                    chart3Linear.visible = true
                    chart1Log.visible = false
                    chart2Log.visible = false
                    chart3Log.visible = false
                }
                bt1.enabled = true
                bt2.enabled = true
                bt3.enabled = false

                maxYValue.textFieldText = axisY3Linear.max.toExponential(4);
                minYValue.textFieldText = axisY3Linear.min.toExponential(4);
            }
        }
    }

    Switch {
        id: scaleButton
        text: Strings.logScale
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        onCheckedChanged: {
            if(scaleButton.checked) {
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
            } else{
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

    Button {
        id: downloadButton
        text: Strings.download
        width: 100
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: {
            var url = globalConfiguration.ui_save_path + "/Wfes/"
            var name = ""

            //If svg do this.
            if(chart1Linear.title == "WFES Single - Equilibrium") {
                if(chart1Linear.visible || chart1Log.visible) {
                    name = "wfes-single-equilibrium";
                    chartResults.saveChartSVG("Wfes Single Equilibrium Dist.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
                }
            }
            if(chart1Linear.title == "Phase Type Dist.") {
                if(chart1Linear.visible || chart1Log.visible) {
                    name = "phase-type-dist";
                    chartResults.saveChartSVG("Phase Type Dist.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
                } else if (chart2Linear.visible || chart2Log.visible) {
                    name = "phase-type-acum";
                    chartResults.saveChartSVG("Phase Type Acum.", scaleButton.checked, axisY2Linear.min, axisY2Linear.max, url, "chart-" + name)
                }
            }
            if(chart1Linear.title == "WFAF-S") {
                name = "wfafs-dist";
                chartResults.saveChartSVG("Wfafs Dist.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
            }
            if(chart1Linear.title == "WFAF-D") {
                name = "wfafd-dist";
                chartResults.saveChartSVG("Wfafd Dist.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
            }
            if(chart1Linear.title == "Time Dist.") {
                if(chart1Linear.visible || chart1Log.visible) {
                    name = "time-dist-ext";
                    chartResults.saveChartSVG("Time Dist. Ext.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
                } else if (chart2Linear.visible || chart2Log.visible) {
                    name = "time-dist-fix";
                    chartResults.saveChartSVG("Time Dist. Fix.", scaleButton.checked, url, axisY2Linear.min, axisY2Linear.max, "chart-" + name)
                } else if (chart3Linear.visible || chart3Log.visible) {
                    name = "time-dist-abs";
                    chartResults.saveChartSVG("Time Dist. Abs.", scaleButton.checked, url, axisY3Linear.min, axisY3Linear.max, "chart-" + name)
                }
            }
            if(chart1Linear.title == "Time Dist. SGV (scaled x10e20)") {
                if(chart1Linear.visible || chart1Log.visible) {
                    name = "time-dist-sgv-sub";
                    chartResults.saveChartSVG("Time Dist. SGV Sub.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
                } else if (chart2Linear.visible || chart2Log.visible) {
                    name = "time-dist-sgv-acum";
                    chartResults.saveChartSVG("Time Dist. SGV Acum.", scaleButton.checked, url, axisY2Linear.min, axisY2Linear.max, "chart-" + name)
                }
            }
            if(chart1Linear.title == "Time Dist. Skip") {
                if(chart1Linear.visible || chart1Log.visible) {
                    name = "time-dist-skip-sub";
                    chartResults.saveChartSVG("Time Dist. Skip Sub.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
                } else if (chart2Linear.visible || chart2Log.visible) {
                    name = "time-dist-skip-acum";
                    chartResults.saveChartSVG("Time Dist. Skip Acum.", scaleButton.checked, url, axisY2Linear.min, axisY2Linear.max, "chart-" + name)
                }
            }
            if(chart1Linear.title == "Time Dist. Dual") {
                if(chart1Linear.visible || chart1Log.visible) {
                    name = "time-dist-dual-ext";
                    chartResults.saveChartSVG("Time Dist. Dual Ext.", scaleButton.checked, url, axisYLinear.min, axisYLinear.max, "chart-" + name)
                } else if (chart2Linear.visible || chart2Log.visible) {
                    name = "time-dist-dual-fix";
                    chartResults.saveChartSVG("Time Dist. Dual Fix.", scaleButton.checked, url, axisY2Linear.min, axisY2Linear.max, "chart-" + name)
                } else if (chart3Linear.visible || chart3Log.visible) {
                    name = "time-dist-dual-abs";
                    chartResults.saveChartSVG("Time Dist. Dual Abs.", scaleButton.checked, url, axisY3Linear.min, axisY3Linear.max, "chart-" + name)
                }
            }


            // If png do this.
            /*if(chart1Linear.visible) {
                chart1Linear.grabToImage(function(result) {
                    result.saveToFile(url + "chart-" + bt1.text + ".png");
                });
            } else if(chart1Log.visible) {
                chart1Log.grabToImage(function(result) {
                    result.saveToFile(url + "chart-" + bt1.text + ".png");
                });
            } else if(chart2Linear.visible) {
                chart2Linear.grabToImage(function(result) {
                    result.saveToFile(url + "chart-" + bt2.text + ".png");
                });
            } else if(chart2Log.visible) {
                chart2Log.grabToImage(function(result) {
                    result.saveToFile(url + "chart-" + bt2.text + ".png");
                });
            } else if(chart3Linear.visible) {
                chart3Linear.grabToImage(function(result) {
                    result.saveToFile(url + "chart-" + bt3.text + ".png");
                });
            } else if(chart3Log.visible) {
                chart3Log.grabToImage(function(result) {
                    result.saveToFile(url + "chart-" + bt3.text + ".png");
                });
            }*/
            systemOperations.openUrlInFileExplorer(url)

        }
    }

    ColumnLayout {

        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        Button {
            id: resetAxis
            text: Strings.resetYAxis
            onClicked: {
                if(chart1Linear.visible || chart1Log.visible) {
                    axisYLinear.max = maxYValue.defaultMax1
                    axisYLinear.min = minYValue.defaultMin1
                    axisY1Log.max = maxYValue.defaultMax1
                    axisY1Log.min = minYValue.defaultMin1
                    maxYValue.textFieldText = maxYValue.defaultMax1.toExponential(4);
                    minYValue.textFieldText = minYValue.defaultMin1.toExponential(4);
                } else if(chart2Linear.visible || chart2Log.visible) {
                    axisY2Linear.max = maxYValue.defaultMax2
                    axisY2Linear.min = minYValue.defaultMin2
                    axisY2Log.max = maxYValue.defaultMax2
                    axisY2Log.min = minYValue.defaultMin2
                    maxYValue.textFieldText = maxYValue.defaultMax2.toExponential(4);
                    minYValue.textFieldText = minYValue.defaultMin2.toExponential(4);
                } else if(chart3Linear.visible || chart3Log.visible) {
                    axisY3Linear.max = maxYValue.defaultMax3
                    axisY3Linear.min = minYValue.defaultMin3
                    axisY3Log.max = maxYValue.defaultMax3
                    axisY3Log.min = minYValue.defaultMin3
                    maxYValue.textFieldText = maxYValue.defaultMax3.toExponential(4);
                    minYValue.textFieldText = minYValue.defaultMin3.toExponential(4);
                }
            }
        }

        LabeledTextField {
            property var defaultMax1: 0
            property var defaultMax2: 0
            property var defaultMax3: 0
            id: maxYValue
            textFieldText: "0"
            text: Strings.maxY + Strings.colon
            labelPreferredWidth: 50
            textFieldTextEdited: function() {
                if(!Number.isNaN(Number(maxYValue.textFieldText)) && parseFloat(maxYValue.textFieldText) >= parseFloat(maxYValue.textFieldText)) {
                    borderColor = "#555555"
                    if(chart1Linear.visible || chart1Log.visible) {
                        axisYLinear.max = parseFloat(maxYValue.textFieldText)
                        axisY1Log.max = parseFloat(maxYValue.textFieldText)
                    } else if(chart2Linear.visible || chart2Log.visible) {
                        axisY2Linear.max = parseFloat(maxYValue.textFieldText)
                        axisY2Log.max = parseFloat(maxYValue.textFieldText)
                    } else if(chart3Linear.visible || chart3Log.visible) {
                        axisY3Linear.max = parseFloat(maxYValue.textFieldText)
                        axisY3Log.max = parseFloat(maxYValue.textFieldText)
                    }
                } else {
                    borderColor = "#ff0000"
                }
            }
        }

        LabeledTextField {
            property var defaultMin1: 0
            property var defaultMin2: 0
            property var defaultMin3: 0
            id: minYValue
            text: Strings.minY + Strings.colon
            labelPreferredWidth: 50
            textFieldText: "0"

            textFieldTextEdited: function() {
                if(!Number.isNaN(Number(minYValue.textFieldText)) && parseFloat(minYValue.textFieldText) >= parseFloat(minYValue.textFieldText)) {
                    borderColor = "#555555"
                    if(chart1Linear.visible || chart1Log.visible) {
                        axisYLinear.min = parseFloat(minYValue.textFieldText)
                        axisY1Log.min = parseFloat(minYValue.textFieldText)
                    } else if(chart2Linear.visible || chart2Log.visible) {
                        axisY2Linear.min = parseFloat(minYValue.textFieldText)
                        axisY2Log.min = parseFloat(minYValue.textFieldText)
                    } else if(chart3Linear.visible || chart3Log.visible) {
                        axisY3Linear.min = parseFloat(minYValue.textFieldText)
                        axisY3Log.min = parseFloat(minYValue.textFieldText)
                    }
                } else {
                    borderColor = "#ff0000"
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
        if(scaleButton.checked) {
            chart1Linear.visible = false
            chart1Linear.visible = false
            chart1Linear.visible = false
            chart1Log.visible = chart1_visible
            chart2Log.visible = chart2_visible
            chart3Log.visible = chart3_visible
        } else {
            chart1Linear.visible = chart1_visible
            chart2Linear.visible = chart2_visible
            chart3Linear.visible = chart3_visible
            chart1Log.visible = false
            chart2Log.visible = false
            chart3Log.visible = false
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
        chart1Linear.title = title
        chart2Linear.title = title
        chart3Linear.title = title
        chart1Log.title = title
        chart2Log.title = title
        chart3Log.title = title
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

    function changeButtonsName(name_bt_1, name_bt_2, name_bt_3) {
        bt1.text = name_bt_1
        bt2.text = name_bt_2
        bt3.text = name_bt_3
    }

    function updateWfesSingleEquilibrium() {
        var minMaxDist = chartResults.updateChart("Wfes Single Equilibrium Dist.", chart1Linear.series(0));
        minMaxDist = chartResults.updateChart("Wfes Single Equilibrium Dist.", chart1Log.series(0));

        visibleButtons(false, false, false)
        enableButtons(false, true, true)
        changeButtonsName("Freq.", "", "")

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("WFES Single - Equilibrium")

        setSeriesName("Equilibrium frequency distribution", "", "", "", "", "")

        var axisPadding = ((minMaxDist.y - minMaxDist.x) - minMaxDist.x) * 0.01
        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)

        minYValue.defaultMin1 = minMaxDist.x - axisPadding;
        maxYValue.defaultMax1 = minMaxDist.y + axisPadding;
        minYValue.textFieldText = (minMaxDist.x - axisPadding).toExponential(4);
        maxYValue.textFieldText = (minMaxDist.y + axisPadding).toExponential(4);
    }

    function updatePhaseTypeDistChart() {
        var minMaxDist = chartResults.updateChart("Phase Type Dist.", chart1Linear.series(0));
        var minMaxAcum = chartResults.updateChart("Phase Type Acum.", chart2Linear.series(0));
        minMaxDist = chartResults.updateChart("Phase Type Dist.", chart1Log.series(0));
        minMaxAcum = chartResults.updateChart("Phase Type Acum.", chart2Log.series(0));

        visibleButtons(true, true, false)
        enableButtons(false, true, true)
        changeButtonsName("Subs.", "Acum.", "")

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("Phase Type Dist.")

        setSeriesName("Probability of subs.", "", "Cumulative prob. of subs.", "", "", "")

        var axisPadding = ((minMaxDist.y - minMaxDist.x) - minMaxDist.x) * 0.01
        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.at(lineSeries0Chart1.count-1).x, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.at(lineSeries0Chart1Log.count-1).x, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)

        axisPadding = ((minMaxAcum.y - minMaxAcum.x) - minMaxAcum.x) * 0.01
        setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.at(lineSeries0Chart2.count-1).x, minMaxAcum.x - axisPadding, minMaxAcum.y + axisPadding)
        setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.at(lineSeries0Chart2Log.count-1).x, minMaxAcum.x - axisPadding, minMaxAcum.y + axisPadding)

        axisPadding = ((minMaxDist.y - minMaxDist.x) - minMaxDist.x) * 0.01
        minYValue.defaultMin1 = minMaxDist.x - axisPadding;
        maxYValue.defaultMax1 = minMaxDist.y + axisPadding;
        axisPadding = ((minMaxAcum.y - minMaxAcum.x) - minMaxAcum.x) * 0.01
        minYValue.defaultMin2 = minMaxAcum.x - axisPadding;
        maxYValue.defaultMax2 = minMaxAcum.y + axisPadding;

        axisPadding = ((minMaxDist.y - minMaxDist.x) - minMaxDist.x) * 0.01
        minYValue.textFieldText = (minMaxDist.x - axisPadding).toExponential(4);
        maxYValue.textFieldText = (minMaxDist.y + axisPadding).toExponential(4);
    }

    function updateDistWfafs() {
        var minMaxDist = chartResults.updateChart("Wfafs Dist.", chart1Linear.series(0));
        minMaxDist = chartResults.updateChart("Wfafs Dist.", chart1Log.series(0));

        visibleButtons(false, false, false)
        enableButtons(false, true, true)
        changeButtonsName("Dist.", "", "")

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("WFAF-S")

        setSeriesName("Allele frequency distribution", "", "", "", "", "")

        var axisPadding = ((minMaxDist.y - minMaxDist.x) - minMaxDist.x) * 0.01
        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)

        minYValue.defaultMin1 = minMaxDist.x - axisPadding;
        maxYValue.defaultMax1 = minMaxDist.y + axisPadding;

        minYValue.textFieldText = (minMaxDist.x - axisPadding).toExponential(4);
        maxYValue.textFieldText = (minMaxDist.y + axisPadding).toExponential(4);
    }

    function updateDistWfafd() {
        var minMaxDist = chartResults.updateChart("Wfafd Dist.", chart1Linear.series(0));
        minMaxDist = chartResults.updateChart("Wfafd Dist.", chart1Log.series(0));

        visibleButtons(false, false, false)
        enableButtons(false, true, true)
        changeButtonsName("Dist.", "", "")

        visibleChart(true, false, false)

        visibleSeries(true, false, true, false, true, false)

        setTitle("WFAF-D")

        setSeriesName("Allele frequency distribution", "", "", "", "", "")

        var axisPadding = ((minMaxDist.y - minMaxDist.x) - minMaxDist.x) * 0.01
        setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)
        setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDist.x - axisPadding, minMaxDist.y + axisPadding)

        minYValue.defaultMin1 = minMaxDist.x - axisPadding;
        maxYValue.defaultMax1 = minMaxDist.y + axisPadding;

        minYValue.textFieldText = (minMaxDist.x - axisPadding).toExponential(4);
        maxYValue.textFieldText = (minMaxDist.y + axisPadding).toExponential(4);
    }

    function updateProbTimeDist(name) {
        var minChart3;
        var maxChart3;
        var axisPadding;
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
            changeButtonsName("Ext.", "Fix.", "Abs.")

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, true, true)

            setTitle("Time Dist.")

            setSeriesName("Probability of ext.", "", "Probability of fix.", "", "Probability of abs.", "Cumulative prob. of abs.")

            axisPadding = ((minMaxExt.y - minMaxExt.x) - minMaxExt.x) * 0.01
            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxExt.x - axisPadding, minMaxExt.y + axisPadding)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxExt.x - axisPadding, minMaxExt.y + axisPadding)

            axisPadding = ((minMaxFix.y - minMaxFix.x) - minMaxFix.x) * 0.01
            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxFix.x - axisPadding, minMaxFix.y + axisPadding)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxFix.x - axisPadding, minMaxFix.y + axisPadding)

            minChart3 = Math.min(minMaxAbs.x, minMaxAcum.x)
            maxChart3 = Math.max(minMaxAbs.y, minMaxAcum.y)

            axisPadding = ((maxChart3 - maxChart3) - minChart3) * 0.01
            setValuesAxis(axisX3Linear, axisY3Linear, 1, lineSeries0Chart3.count, minChart3 - axisPadding, maxChart3 + axisPadding)
            setValuesAxis(axisX3Log, axisY3Log, 1, lineSeries0Chart3Log.count, minChart3 - axisPadding, maxChart3 + axisPadding)

            axisPadding = ((minMaxExt.y - minMaxExt.x) - minMaxExt.x) * 0.01
            minYValue.defaultMin1 = minMaxExt.x - axisPadding;
            maxYValue.defaultMax1 = minMaxExt.y + axisPadding;
            axisPadding = ((minMaxFix.y - minMaxFix.x) - minMaxFix.x) * 0.01
            minYValue.defaultMin2 = minMaxFix.x - axisPadding;
            maxYValue.defaultMax2 = minMaxFix.y + axisPadding;
            axisPadding = ((maxChart3 - maxChart3) - minChart3) * 0.01
            minYValue.defaultMin3 = minChart3 - axisPadding;
            maxYValue.defaultMax3 = maxChart3 + axisPadding;

            axisPadding = ((minMaxExt.y - minMaxExt.x) - minMaxExt.x) * 0.01
            minYValue.textFieldText = (minMaxExt.x - axisPadding).toExponential(4);
            maxYValue.textFieldText = (minMaxExt.y + axisPadding).toExponential(4);
        } else if(name === "Time Dist. SGV") {
            var minMaxSGVSubs = chartResults.updateChart("Time Dist. SGV Sub.", chart1Linear.series(0));
            var minMaxSGVAcum = chartResults.updateChart("Time Dist. SGV Acum.", chart2Linear.series(0));
            minMaxSGVSubs = chartResults.updateChart("Time Dist. SGV Sub.", chart1Log.series(0));
            minMaxSGVAcum = chartResults.updateChart("Time Dist. SGV Acum.", chart2Log.series(0));

            visibleButtons(true, true, false)
            enableButtons(false, true, true)
            changeButtonsName("Subs.", "Acum.", "")

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, false, false)

            setTitle("Time Dist. SGV (scaled x10e20)")

            setSeriesName("Probability of subs.", "", "Cumulative prob. of subs.", "", "", "")

            axisPadding = ((minMaxSGVSubs.y - minMaxSGVSubs.x) - minMaxSGVSubs.x) * 0.01
            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxSGVSubs.x - axisPadding, minMaxSGVSubs.y + axisPadding)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxSGVSubs.x - axisPadding, minMaxSGVSubs.y + axisPadding)

            axisPadding = ((minMaxSGVAcum.y - minMaxSGVAcum.x) - minMaxSGVAcum.x) * 0.01
            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxSGVAcum.x - axisPadding, minMaxSGVAcum.y + axisPadding)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxSGVAcum.x - axisPadding, minMaxSGVAcum.y + axisPadding)

            axisPadding = ((minMaxSGVSubs.y - minMaxSGVSubs.x) - minMaxSGVSubs.x) * 0.01
            minYValue.defaultMin1 = minMaxSGVSubs.x - axisPadding;
            maxYValue.defaultMax1 = minMaxSGVSubs.y + axisPadding;
            axisPadding = ((minMaxSGVAcum.y - minMaxSGVAcum.x) - minMaxSGVAcum.x) * 0.01
            minYValue.defaultMin2 = minMaxSGVAcum.x - axisPadding;
            maxYValue.defaultMax2 = minMaxSGVAcum.y + axisPadding;

            axisPadding = ((minMaxSGVSubs.y - minMaxSGVSubs.x) - minMaxSGVSubs.x) * 0.01
            minYValue.textFieldText = (minMaxSGVSubs.x - axisPadding).toExponential(4);
            maxYValue.textFieldText = (minMaxSGVSubs.y + axisPadding).toExponential(4);
        } else if(name === "Time Dist. Skip") {
            var minMaxSkipSubs = chartResults.updateChart("Time Dist. Skip Sub.", chart1Linear.series(0));
            var minMaxSkipAcum = chartResults.updateChart("Time Dist. Skip Acum.", chart2Linear.series(0));
            minMaxSkipSubs = chartResults.updateChart("Time Dist. Skip Sub.", chart1Log.series(0));
            minMaxSkipAcum = chartResults.updateChart("Time Dist. Skip Acum.", chart2Log.series(0));

            visibleButtons(true, true, false)
            enableButtons(false, true, true)
            changeButtonsName("Subs.", "Acum.", "")

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, false, false)

            setTitle("Time Dist. Skip")

            setSeriesName("Probability of subs.", "", "Cumulative prob. of subs.", "", "", "")

            axisPadding = ((minMaxSkipSubs.y - minMaxSkipSubs.x) - minMaxSkipSubs.x) * 0.01
            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxSkipSubs.x - axisPadding, minMaxSkipSubs.y + axisPadding)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxSkipSubs.x - axisPadding, minMaxSkipSubs.y + axisPadding)

            axisPadding = ((minMaxSkipAcum.y - minMaxSkipAcum.x) - minMaxSkipAcum.x) * 0.01
            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxSkipAcum.x - axisPadding, minMaxSkipAcum.y + axisPadding)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxSkipAcum.x - axisPadding, minMaxSkipAcum.y + axisPadding)

            axisPadding = ((minMaxSkipSubs.y - minMaxSkipSubs.x) - minMaxSkipSubs.x) * 0.01
            minYValue.defaultMin1 = minMaxSkipSubs.x - axisPadding;
            maxYValue.defaultMax1 = minMaxSkipSubs.y + axisPadding;
            axisPadding = ((minMaxSkipAcum.y - minMaxSkipAcum.x) - minMaxSkipAcum.x) * 0.01
            minYValue.defaultMin2 = minMaxSkipAcum.x - axisPadding;
            maxYValue.defaultMax2 = minMaxSkipAcum.y + axisPadding;

            axisPadding = ((minMaxSkipSubs.y - minMaxSkipSubs.x) - minMaxSkipSubs.x) * 0.01
            minYValue.textFieldText = (minMaxSkipSubs.x - axisPadding).toExponential(4);
            maxYValue.textFieldText = (minMaxSkipSubs.y + axisPadding).toExponential(4);
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
            changeButtonsName("Ext.", "Fix.", "Abs.")

            visibleChart(true, false, false)

            visibleSeries(true, false, true, false, true, true)

            setTitle("Time Dist. Dual")

            setSeriesName("Probability of ext.", "", "Probability of fix.", "", "Probability of abs.", "Cumulative prob. of abs.")

            axisPadding = ((minMaxDualExt.y - minMaxDualExt.x) - minMaxDualExt.x) * 0.01
            setValuesAxis(axisXLinear, axisYLinear, 1, lineSeries0Chart1.count, minMaxDualExt.x - axisPadding, minMaxDualExt.y + axisPadding)
            setValuesAxis(axisX1Log, axisY1Log, 1, lineSeries0Chart1Log.count, minMaxDualExt.x - axisPadding, minMaxDualExt.y + axisPadding)

            axisPadding = ((minMaxDualFix.y - minMaxDualFix.x) - minMaxDualFix.x) * 0.01
            setValuesAxis(axisX2Linear, axisY2Linear, 1, lineSeries0Chart2.count, minMaxDualFix.x - axisPadding, minMaxDualFix.y + axisPadding)
            setValuesAxis(axisX2Log, axisY2Log, 1, lineSeries0Chart2Log.count, minMaxDualFix.x - axisPadding, minMaxDualFix.y + axisPadding)

            minChart3 = Math.min(minMaxDualAbs.x, minMaxDualAcum.x)
            maxChart3 = Math.max(minMaxDualAbs.y, minMaxDualAcum.y)

            axisPadding = ((maxChart3 - maxChart3) - minChart3) * 0.01
            setValuesAxis(axisX3Linear, axisY3Linear, 1, lineSeries0Chart3.count, minChart3 - axisPadding, maxChart3 + axisPadding)
            setValuesAxis(axisX3Log, axisY3Log, 1, lineSeries0Chart3Log.count, minChart3 - axisPadding, maxChart3 + axisPadding)

            axisPadding = ((minMaxDualExt.y - minMaxDualExt.x) - minMaxDualExt.x) * 0.01
            minYValue.defaultMin1 = minMaxDualExt.x - axisPadding;
            maxYValue.defaultMax1 = minMaxDualExt.y + axisPadding;
            axisPadding = ((minMaxDualFix.y - minMaxDualFix.x) - minMaxDualFix.x) * 0.01
            minYValue.defaultMin2 = minMaxDualFix.x - axisPadding;
            maxYValue.defaultMax2 = minMaxDualFix.y + axisPadding;
            axisPadding = ((maxChart3 - maxChart3) - minChart3) * 0.01
            minYValue.defaultMin3 = minChart3 - axisPadding;
            maxYValue.defaultMax3 = maxChart3 + axisPadding;

            axisPadding = ((minMaxDualExt.y - minMaxDualExt.x) - minMaxDualExt.x) * 0.01
            minYValue.textFieldText = (minMaxDualExt.x - axisPadding).toExponential(4);
            maxYValue.textFieldText = (minMaxDualExt.y + axisPadding).toExponential(4);
        }
    }
}
