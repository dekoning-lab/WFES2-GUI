import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

//TODO Implement value validators and return exceptions.
ApplicationWindow {
    id: rootTimeDist
    title: qsTr("WFES - Wright-Fisher Exact Solver (Time Dist.)")

    color: Universal.chromeLowColor

    visible: true

    width: 640
    minimumWidth: 640
    maximumWidth: 640
    height: 525
    minimumHeight: 525
    maximumHeight: 525

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootTimeDist.destroy();
        root.visible = true;
        rootTimeDist.updateBackend()
        outputControllerTimeDist.ui_save_config
    }

    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
        // Activate time dist sgv, so it is loaded and it loads the configuration.
        radioButtonTimeDistSGV.checked = true

    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"

        UpperMenu {
            id: upperMenu
        }

        Rectangle {
            id: content
            height: childrenRect.height
            width: parent.width
            color: "transparent"

            anchors {
                top: upperMenu.bottom
                left: parent.left
            }

            RowLayout {
                id: mainGrid

                ColumnLayout {
                    id: column1
                    width: childrenRect.width

                    Layout.margins: 10
                    Layout.alignment: Qt.AlignTop

                    Rectangle {
                        id: modeSection
                        color: "transparent"
                        height: childrenRect.height
                        width: childrenRect.width

                        Label {
                            id: labelModel
                            text: "Mode:"
                            font.bold: true
                        }

                        GridLayout {
                            id: modeSectionGrid
                            columns: 2
                            anchors {
                                top: labelModel.bottom
                                left: parent.left
                                margins: 10
                            }

                            RadioButton {
                                id: radioButtonTimeDist
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist."
                                text: qsTr("Time Dist.")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Distribution of time to fixation / extinction.")

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = !checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = !checked

                                    labelComponents.visible = !checked
                                    timeDistSGVSection.visible = !checked
                                    timeDistSGVCommonSection.visible = !checked
                                    populationSection.visible = checked
                                    mutationSection.visible = checked
                                    selectionSection.visible = checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = checked
                                }
                            }
                            RadioButton {
                                id: radioButtonTimeDistSGV
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. SGV"
                                text: qsTr("Time Dist. SGV")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Time distribution of fixation with standing genetics variation.")

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = checked

                                    labelComponents.visible = checked
                                    timeDistSGVSection.visible = checked
                                    timeDistSGVCommonSection.visible = checked
                                    populationSection.visible = !checked
                                    mutationSection.visible = !checked
                                    selectionSection.visible = !checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = !checked
                                }
                            }

                            RadioButton {
                                id: radioButtonTimeDistSkip
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. Skip"
                                text: qsTr("Time Dist. Skip")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Distribution of time to absorption, excluding mutation time.")

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = !checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = !checked

                                    labelComponents.visible = !checked
                                    timeDistSGVSection.visible = !checked
                                    timeDistSGVCommonSection.visible = !checked
                                    populationSection.visible = checked
                                    mutationSection.visible = checked
                                    selectionSection.visible = checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = checked
                                }
                            }
                            RadioButton {
                                id: radioButtonTimeDistDual
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. Dual"
                                text: qsTr("Time Dist. Dual")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("TODO.")

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = !checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = !checked

                                    labelComponents.visible = !checked
                                    timeDistSGVSection.visible = !checked
                                    timeDistSGVCommonSection.visible = !checked
                                    populationSection.visible = checked
                                    mutationSection.visible = checked
                                    selectionSection.visible = checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = checked
                                }
                            }

                        }

                    }

                    Rectangle {
                        id: separator1column1
                        height: 1
                        width: modeSectionGrid.width + 10
                        color: Universal.baseHighColor
                    }

                    Label {
                        id: labelComponents
                        text: "Components:"
                        visible: (inputControllerTimeDist.ui_modelType === "Time Dist. SGV")
                        font.bold: true
                    }
                    Rectangle {
                        id: timeDistSGVSection
                        width: modeSection.width
                        height: childrenRect.height
                        visible: (inputControllerTimeDist.ui_modelType === "Time Dist. SGV")
                        color: "transparent"

                        Layout.alignment: Qt.AlignTop

                        TabView {
                            id: timeDistSGVSectionTabView
                            width: parent.width
                            height: 170
                            Tab {
                                id: comp1
                                title: "Comp. 1"
                                height: parent.height
                                GridLayout {
                                    id: tabGrid1
                                    columns: 1
                                    anchors {
                                        top: parent.top
                                        left: parent.left
                                    }

                                    Rectangle {
                                        id: mutationSection1
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"

                                        Label {
                                            id: labelMutation1
                                            text: "Mutation:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: mutationSectionGrid1
                                            columns: 2
                                            anchors {
                                                top: labelMutation1.bottom
                                                left: parent.left
                                                margins: 10
                                            }


                                            LabeledTextField {
                                                id: inputU1
                                                text: "u1: "
                                                toolTipText: "Backward mutation rate."
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var u_vec = inputControllerTimeDist.ui_u_vec
                                                    return u_vec[0]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputV1
                                                text: "v1: "
                                                toolTipText: "Forward mutation rate."
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var v_vec = inputControllerTimeDist.ui_v_vec
                                                    return v_vec[0]
                                                }
                                            }

                                        }
                                    }

                                    Rectangle {
                                        id: selectionSection1
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"


                                        Label {
                                            id: labelSelection1
                                            text: "Selection:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: selectionSectionGrid1
                                            columns: 4
                                            anchors {
                                                top: labelSelection1.bottom
                                                left: parent.left
                                                margins: 10
                                            }

                                            LabeledTextField {
                                                id: inputS1
                                                text: "s1: "
                                                toolTipText: "Selection coefficient."
                                                validator: DoubleValidator {bottom: -1; top: 1;}
                                                textFieldText: {
                                                    var s_vec = inputControllerTimeDist.ui_s_vec
                                                    return s_vec[0]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH1
                                                text: "h1: "
                                                toolTipText: "Dominance coefficient."
                                                validator: DoubleValidator {bottom: 0; top: 1;}
                                                textFieldText: {
                                                    var h_vec = inputControllerTimeDist.ui_h_vec
                                                    return h_vec[0]
                                                }
                                            }

                                        }
                                    }

                                }
                                onLoaded: function() {
                                    var dummyString = outputControllerTimeDist.ui_load_config
                                    rootTimeDist.updateGUI()
                                }
                            }
                            Tab {
                                id: comp2
                                title: "Comp. 2"
                                height: parent.height
                                GridLayout {
                                    id: tabGrid2
                                    columns: 1
                                    anchors {
                                        top: parent.top
                                        left: parent.left
                                    }

                                    Rectangle {
                                        id: mutationSection2
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"

                                        Label {
                                            id: labelMutation2
                                            text: "Mutation:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: mutationSectionGrid2
                                            columns: 2
                                            anchors {
                                                top: labelMutation2.bottom
                                                left: parent.left
                                                margins: 10
                                            }


                                            LabeledTextField {
                                                id: inputU2
                                                text: "u2: "
                                                toolTipText: "Backward mutation rate."
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var u_vec = inputControllerTimeDist.ui_u_vec
                                                    return u_vec[1]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputV2
                                                text: "v2: "
                                                toolTipText: "Forward mutation rate."
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var v_vec = inputControllerTimeDist.ui_v_vec
                                                    return v_vec[1]
                                                }
                                            }

                                        }
                                    }

                                    Rectangle {
                                        id: selectionSection2
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"


                                        Label {
                                            id: labelSelection2
                                            text: "Selection:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: selectionSectionGrid2
                                            columns: 4
                                            anchors {
                                                top: labelSelection2.bottom
                                                left: parent.left
                                                margins: 10
                                            }

                                            LabeledTextField {
                                                id: inputS2
                                                text: "s2: "
                                                toolTipText: "Selection coefficient."
                                                validator: DoubleValidator {bottom: -1; top: 1;}
                                                textFieldText: {
                                                    var s_vec = inputControllerTimeDist.ui_s_vec
                                                    return s_vec[1]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH2
                                                text: "h2: "
                                                toolTipText: "Dominance coefficient."
                                                validator: DoubleValidator {bottom: 0; top: 1;}
                                                textFieldText: {
                                                    var h_vec = inputControllerTimeDist.ui_h_vec
                                                    return h_vec[1]
                                                }
                                            }

                                        }
                                    }

                                }

                            }
                        }

                    }

                    Rectangle {
                        id: populationSection
                        width: modeSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType != "Time Dist. SGV")
                        color: "transparent"

                        Label {
                            id: labelPopulation
                            text: "Population:"
                            font.bold: true
                        }

                        GridLayout {
                            id: populationSectionGrid
                            columns: 2
                            anchors {
                                top: labelPopulation.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: inputN
                                text: "N: "
                                toolTipText: "Size of the population in the Wright Fisher Model."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerTimeDist.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 10e-10;}
                                textFieldText: inputControllerTimeDist.ui_a
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "Stop once this probability mass is reached."
                                validator: DoubleValidator {bottom: 0; top: 10e-3;}
                                textFieldText: inputControllerTimeDist.ui_c
                            }

                            LabeledTextField {
                                id: inputM
                                text: "m: "
                                toolTipText: "Maximum number of generations."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerTimeDist.ui_m
                            }

                        }

                    }

                    Rectangle {
                        id: separator2column1
                        height: 1
                        width: modeSectionGrid.width + 10
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: timeDistSGVCommonSection
                        width: timeDistSGVSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType == "Time Dist. SGV")
                        color: "transparent"

                        Label {
                            id: labelCommonParameters
                            text: "Common Parameters"
                            font.bold: true
                        }

                        GridLayout {
                            id: timeDistSGVCommonSectionGrid
                            columns: 2
                            anchors {
                                top: labelCommonParameters.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: inputN1
                                text: "N: "
                                toolTipText: "Size of the population in the Wright Fisher Model."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerTimeDist.ui_n_sgv
                            }

                            LabeledTextField {
                                id: inputA1
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 10e-10;}
                                textFieldText: inputControllerTimeDist.ui_a_sgv
                            }

                            LabeledTextField {
                                id: inputL
                                text: "l: "
                                toolTipText: "Transition probability."
                                validator: DoubleValidator {bottom: 1e-20; top: 1;}
                                textFieldText: inputControllerTimeDist.ui_l
                                enabled: (inputControllerTimeDist.ui_modelType == "Time Dist. SGV")
                            }

                            LabeledTextField {
                                id: inputC1
                                text: "c: "
                                toolTipText: "Stop once this probability mass is reached."
                                validator: DoubleValidator {bottom: 0; top: 10e-3;}
                                textFieldText: inputControllerTimeDist.ui_c_sgv
                            }

                            LabeledTextField {
                                id: inputM1
                                text: "m: "
                                toolTipText: "Maximum number of generations."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerTimeDist.ui_m_sgv
                            }

                            LabeledCheckBox {
                                id: inputR1
                                text: "r: "
                                toolTipText: "Exclude recurrent mutation."
                                checked: inputControllerTimeDist.ui_r_sgv
                            }
                        }
                    }

                    Rectangle {
                        id: mutationSection
                        width: populationSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType != "Time Dist. SGV")
                        color: "transparent"

                        Label {
                            id: labelMutation
                            text: "Mutation:"
                            font.bold: true
                        }

                        GridLayout {
                            id: mutationSectionGrid
                            columns: 2
                            anchors {
                                top: labelMutation.bottom
                                left: parent.left
                                margins: 10
                            }


                            LabeledTextField {
                                id: inputU
                                text: "u: "
                                toolTipText: "Backward mutation rate."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerTimeDist.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: "v: "
                                toolTipText: "Forward mutation rate."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerTimeDist.ui_v
                            }

                            LabeledCheckBox {
                                id: inputR
                                text: "r: "
                                toolTipText: "Exclude recurrent mutation."
                                checked: inputControllerTimeDist.ui_r
                            }
                        }
                    }

                    Rectangle {
                        id: separator3column1
                        height: 1
                        width: modeSectionGrid.width + 10
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: selectionSection
                        width: mutationSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType != "Time Dist. SGV")
                        color: "transparent"

                        Label {
                            id: labelSelection
                            text: "Selection:"
                            font.bold: true
                        }

                        GridLayout {
                            id: selectionSectionGrid
                            columns: 4
                            anchors {
                                top: labelSelection.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: inputS
                                text: "s: "
                                toolTipText: "Selection coefficient."
                                validator: DoubleValidator {bottom: -1; top: 1;}
                                textFieldText: inputControllerTimeDist.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                validator: DoubleValidator {bottom: 0; top: 1;}
                                textFieldText: inputControllerTimeDist.ui_h
                            }

                        }
                    }
                }

                Rectangle {
                    id: separator1
                    width: 1
                    Layout.fillHeight: true
                    color: Universal.baseHighColor
                    Layout.topMargin: 10
                    Layout.bottomMargin:10
                }

                ColumnLayout {
                    id: column2
                    Layout.preferredHeight: column1.height

                    ColumnLayout {
                        Layout.alignment: Qt.AlignTop
                        Layout.margins: 10

                        Rectangle {
                            id: outputSection
                            color: "transparent"
                            height: childrenRect.height
                            width: childrenRect.width

                            Label {
                                id: labelOutput
                                text: "Output Options:"
                                font.bold: true
                            }

                            GridLayout {
                                id: outputSectionGrid
                                width: childrenRect.width
                                columns: 2
                                anchors {
                                    top: labelOutput.bottom
                                    left: parent.left
                                    margins: 10
                                }

                                LabeledCheckBox {
                                    id: inputWriteQ
                                    text: "Q: "
                                    toolTipText: "Output Q as CSV file."
                                    checked: inputControllerTimeDist.ui_output_Q
                                    //enabled: //TODO

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: "R: "
                                    toolTipText: "Output R as CSV file."
                                    checked: inputControllerTimeDist.ui_output_R
                                    //enabled: //TODO
                                }

                                LabeledCheckBox {
                                    id: inputWriteP
                                    text: "P: "
                                    toolTipText: "TODO. (Always enabled)."
                                    checked: true
                                    enabledCheckBox: false
                                }

                            }

                        }

                        Rectangle {
                            height: 1
                            width: Math.max(executionSection.width, outputSection.width)
                            color: Universal.baseHighColor
                        }

                        Rectangle {
                            id: executionSection
                            color: "transparent"
                            height: childrenRect.height
                            width: childrenRect.width

                            Label {
                                id: labelExecution
                                text: "Execution:"
                                font.bold: true
                            }


                            ColumnLayout {

                                width: childrenRect.width
                                anchors {
                                    top: labelExecution.bottom
                                    left: parent.left
                                    margins: 10
                                }
                                RowLayout {
                                    width: childrenRect.width

                                    LabeledCheckBox {
                                        id: inputForce
                                        toolTipText: "Do not perform parameter checks."
                                        text: "Force: "
                                        checked: inputControllerTimeDist.ui_force
                                        enabled: (inputControllerTimeDist.ui_modelType == "Time Dist. SGV")
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        textFieldPreferredWidth: 100
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 1;}
                                        textFieldText: inputControllerTimeDist.ui_t
                                    }
                                }

                                ColumnLayout {
                                    width: childrenRect.width

                                    LabeledComboBox {
                                        id: comboBoxLibrary
                                        text: "Library:"
                                        model: ["Pardiso", "ViennaCL"]
                                        toolTipText: "Library used for solving matrix systems."
                                    }

                                }

                            }
                        }

                    }

                    RowLayout {
                        id: row2
                        Layout.preferredHeight: childrenRect.height
                        Layout.preferredWidth: parent.width

                        Button {
                            id: stopButton
                            Layout.margins: 10
                            Layout.alignment: Qt.AlignRight
                            text: "Stop"

                            Binding {
                                target: stopButton
                                property: "enabled"
                                value: !outputControllerTimeDist.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerTimeDist.ui_stop
                                stopButton.enabled = false
                                executeButton.enabled = true
                            }
                        }

                        Button {
                            id: executeButton
                            Layout.margins: 10
                            Layout.alignment: Qt.AlignRight
                            text: "Execute"

                            onEnabledChanged: {
                                if(outputControllerTimeDist.ui_get_not_exec)
                                    imageOutputController.image_changed()
                                console.log(outputControllerTimeDist.ui_get_error_message)
                                if(outputControllerTimeDist.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerTimeDist.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerTimeDist.ui_reset_error
                                }
                                upperMenu.updateProbTimeDist(inputControllerTimeDist.ui_modelType)
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerTimeDist.ui_get_not_exec
                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()

                                updateBackend()

                                if(error === "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerTimeDist.ui_execute
                                } else {
                                    messageDialog.text = error
                                    messageDialog.open()
                                }
                            }

                        }

                    }
                }

                MessageDialog {
                    id: messageDialog
                    title: "Warning"
                    text: ""
                    icon: StandardIcon.Warning
                }

            }

        }


        Rectangle {
            height: 1
            width: parent.width
            color: Universal.baseHighColor
            anchors {
                top: bottomMenu.top
                left: parent.left
            }
        }

        Binding {
            target: bottomMenu
            property: "visibleProgressBar"
            value: !outputControllerTimeDist.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            height: childrenRect.height
            executionProgress: outputControllerTimeDist.ui_progress

            anchors {
                bottom: parent.bottom
                left: parent.left
            }

            executionTime: {
                outputControllerTimeDist.ui_get_time == "" ? "" : outputControllerTimeDist.ui_get_time + "s"
            }
        }
    }

    function updateGUI() {
        //First, let's fill the SGV parameters.
        radioButtonTimeDistSGV.checked = true
        radioButtonTimeDist.checked = false
        radioButtonTimeDistDual.checked = false
        radioButtonTimeDistSkip.checked = false

        inputN1.textFieldText = inputControllerTimeDist.ui_n_sgv
        inputA1.textFieldText = inputControllerTimeDist.ui_a_sgv
        inputL.textFieldText = inputControllerTimeDist.ui_l
        inputC1.textFieldText = inputControllerTimeDist.ui_c_sgv
        inputM1.textFieldText = inputControllerTimeDist.ui_m_sgv
        inputR1.checked = inputControllerTimeDist.ui_r_sgv
        var u_vec = inputControllerTimeDist.ui_u_vec
        var v_vec = inputControllerTimeDist.ui_v_vec
        var s_vec = inputControllerTimeDist.ui_s_vec
        var h_vec = inputControllerTimeDist.ui_h_vec
        for(var i = 0; i < 2; i++) {
            timeDistSGVSectionTabView.getTab(i).active = true
            timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
            timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
            timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
            timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText = h_vec[i]
        }

        //And second, the rest of parameters.
        radioButtonTimeDist.checked = true
        radioButtonTimeDistDual.checked = false
        radioButtonTimeDistSkip.checked = false
        radioButtonTimeDistSGV.checked = false
        inputN.textFieldText = inputControllerTimeDist.ui_n
        inputA.textFieldText = inputControllerTimeDist.ui_a
        inputC.textFieldText = inputControllerTimeDist.ui_c
        inputM.textFieldText = inputControllerTimeDist.ui_m
        inputU.textFieldText = inputControllerTimeDist.ui_u
        inputV.textFieldText = inputControllerTimeDist.ui_v
        inputR.checked = inputControllerTimeDist.ui_r
        inputS.textFieldText = inputControllerTimeDist.ui_s
        inputH.textFieldText = inputControllerTimeDist.ui_h

        inputWriteQ.checked = inputControllerTimeDist.ui_output_Q
        inputWriteR.checked = inputControllerTimeDist.ui_output_R
        inputWriteP.checked = inputControllerTimeDist.ui_output_P

        inputForce.checked = inputControllerTimeDist.ui_force

        inputT.textFieldText = inputControllerTimeDist.ui_t
        var library = inputControllerTimeDist.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        radioButtonTimeDist.checked = inputControllerTimeDist.ui_modelType == "Time Dist."
        radioButtonTimeDistDual.checked = inputControllerTimeDist.ui_modelType == "Time Dist. Dual"
        radioButtonTimeDistSGV.checked = inputControllerTimeDist.ui_modelType == "Time Dist. SGV"
        radioButtonTimeDistSkip.checked = inputControllerTimeDist.ui_modelType == "Time Dist. Skip"


    }

    function updateBackend() {

        if(radioButtonTimeDist.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist."
        if(radioButtonTimeDistSGV.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist. SGV"
        if(radioButtonTimeDistSkip.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist. Skip"
        if(radioButtonTimeDistDual.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist. Dual"

        inputControllerTimeDist.ui_n = inputN.textFieldText
        inputControllerTimeDist.ui_a = inputA.textFieldText
        inputControllerTimeDist.ui_c = inputC.textFieldText
        inputControllerTimeDist.ui_m = inputM.textFieldText
        inputControllerTimeDist.ui_u = inputU.textFieldText
        inputControllerTimeDist.ui_v = inputV.textFieldText
        inputControllerTimeDist.ui_r = inputR.checked
        inputControllerTimeDist.ui_s = inputS.textFieldText
        inputControllerTimeDist.ui_h = inputH.textFieldText

        inputControllerTimeDist.ui_n_sgv = inputN1.textFieldText
        inputControllerTimeDist.ui_a_sgv = inputA1.textFieldText
        inputControllerTimeDist.ui_l = inputL.textFieldText
        inputControllerTimeDist.ui_c_sgv = inputC1.textFieldText
        inputControllerTimeDist.ui_m_sgv = inputM1.textFieldText
        inputControllerTimeDist.ui_r_sgv = inputR1.checked
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < 2; i++) {
            timeDistSGVSectionTabView.getTab(i).active = true
            var u = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
            var v = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
            var s = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
            var h = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerTimeDist.ui_u_vec = u_vec
        inputControllerTimeDist.ui_v_vec = v_vec
        inputControllerTimeDist.ui_s_vec = s_vec
        inputControllerTimeDist.ui_h_vec = h_vec


        inputControllerTimeDist.ui_output_P = inputWriteP.checked
        inputControllerTimeDist.ui_output_Q = inputWriteQ.checked
        inputControllerTimeDist.ui_output_R = inputWriteR.checked

        inputControllerTimeDist.ui_t = inputT.textFieldText

        inputControllerTimeDist.ui_library = comboBoxLibrary.currentText;

        inputControllerTimeDist.ui_force = inputForce.checked

    }

    function checkIntegrity() {
        var error = ""


        if(!radioButtonTimeDistSGV.checked) {
            if(parseInt(inputN.textFieldText) < 2)
                error += " - Population Size (N) is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(inputN.textFieldText) > 50000)
                error += " - Population Size (N) is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputA.textFieldText) < 0)
                error += " - Tail Truncation Cutoff (a) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && parseFloat(inputA.textFieldText) > 1e-5)
                error += " - Tail Truncation Cutoff (a) value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputC.textFieldText) < 0)
                error += " - Integration Cutoff (c) is quite small. It must be at least 0. \n \n"
            if(parseFloat(inputC.textFieldText) > 1)
                error += " - Integration Cutoff (c) is quite large. The maximum value allowed is 1. \n \n"

            if(parseInt(inputM.textFieldText) < 2)
                error += " - Maximum Number of Generations (m) is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(inputM.textFieldText) > 50000)
                error += " - Maximum Number of Generations (m) is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputU.textFieldText) < 0)
                error += " - Backward Mutation (u) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && (4 * parseInt(inputN.textFieldText) * parseFloat(inputU.textFieldText)) > 1)
                error += " - Backward Mutation (u) is quite large and might violate the Wright-Fisher assumptions. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputV.textFieldText) < 0)
                error += " - Forward Mutation (v) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && (4 * parseInt(inputN.textFieldText) * parseFloat(inputV.textFieldText)) > 1)
                error += " - Forward Mutation (v) is quite large and might violate the Wright-Fisher assumptions. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputS.textFieldText) < -1)
                error += " - Selection Coefficient (s) is quite small. It must be at least -1. \n \n"
            if(parseFloat(inputS.textFieldText) > 1)
                error += " - Selection Coefficient (s) is quite large. The maximum value allowed is 1. \n \n"
            if(!inputForce.checked && parseFloat(inputS.textFieldText) * (2 * parseInt(inputN.textFieldText)) <= -100)
                error += " - Selection Coefficient (s) is quite negative. Fixations might be impossible. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputH.textFieldText) < 0)
                error += " - Dominance Coefficient (h) is quite small. It must be at least 0. \n \n"
            if(parseFloat(inputH.textFieldText) > 1)
                error += " - Dominance Coefficient (h) is quite large. The maximum value allowed is 1. \n \n"
        } else {
            if(parseInt(inputN1.textFieldText) < 2)
                error += " - Population Size (N) of SGV is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(inputN1.textFieldText) > 50000)
                error += " - Population Size (N) of SGV is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputL.textFieldText) < 1e-20)
                error += " - Rate of switching to pre-adaptive phase (l) of SGV is quite small. It must be at least 0. \n \n"
            if(parseFloat(inputL.textFieldText) > 1)
                error += " - Rate of switching to pre-adaptive phase (l) of SGV is quite large. The maximum value allowed is 10e-3. \n \n"

            if(parseFloat(inputA1.textFieldText) < 0)
                error += " - Tail Truncation Cutoff (a) of SGV is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && parseFloat(inputA1.textFieldText) > 1e-5)
                error += " - Tail Truncation Cutoff (a) of SGV value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore. \n \n"

            if(parseFloat(inputC1.textFieldText) < 0)
                error += " - Integration Cutoff (c) of SGV is quite small. It must be at least 0. \n \n"
            if(parseFloat(inputC1.textFieldText) > 10e-3)
                error += " - Integration Cutoff (c) of SGV is quite large. The maximum value allowed is 10e-3. \n \n"

            if(parseInt(inputM1.textFieldText) < 2)
                error += " - Maximum Number of Generations (m) of SGV is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(inputM1.textFieldText) > 50000)
                error += " - Maximum Number of Generations (m) of SGV is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"

            var u_vec = []
            var v_vec = []
            var s_vec = []
            var h_vec = []
            for(var i = 0; i < 2; i++) {
                timeDistSGVSectionTabView.getTab(i).active = true
                var u = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                var v = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                var s = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                var h = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
                u_vec.push(u)
                v_vec.push(v)
                s_vec.push(s)
                h_vec.push(h)
            }

            for(i = 0; i < 2; i++) {
                if(parseFloat(u_vec[i].textFieldText) < 0)
                    error += " - Backward Mutation (u" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && (4 * parseInt(inputN.textFieldText) * parseFloat(u_vec[i])) > 1)
                    error += " - Backward Mutation (u" + (i + 1) + ") of SGV is quite large and might violate the Wright-Fisher assumptions. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < 2; i++) {
                if(parseFloat(v_vec[i]) < 0)
                    error += " - Forward Mutation (v" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && (4 * parseInt(inputN.textFieldText) * parseFloat(v_vec[i])) > 1)
                    error += " - Forward Mutation (v" + (i + 1) + ") of SGV is quite large and might violate the Wright-Fisher assumptions. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < 2; i++) {
                if(parseFloat(s_vec[i]) < -1)
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite negative. Fixations might be impossible. It must be at least -1. \n \n"
                if(parseFloat(s_vec[i]) > 1)
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite large. The maximum value allowed is 1. \n \n"
                if(parseFloat(s_vec[i]) * 2 * parseInt(inputN.textFieldText) <= -100) {
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite negative. Fixations might be impossible. It must be at least -1. \n \n"
                }
            }

            for(i = 0; i < 2; i++) {
                if(parseFloat(h_vec[i]) < 0)
                    error += " - Dominance Coefficient (h" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(parseFloat(h_vec[i]) > 1)
                    error += " - Dominance Coefficient (h" + (i + 1) + ") of SGV is quite large. The maximum value allowed is 1. \n \n"
            }


        }
        // Number of threads (t) does not have upper limites, since it depends on the hardware available.
        if(parseInt(inputT.textFieldText) < 1)
            error += " - Number of Threads (t) is quite small, it must be at least 1. \n \n"

        //TODO Check if Initial Distribution (I) file exists.

        return error.split("\n \n")[0];
    }
}
