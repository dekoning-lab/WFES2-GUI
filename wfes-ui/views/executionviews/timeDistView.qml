import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

//TODO Implement value validators and return exceptions.
ApplicationWindow {
    id: root
    title: qsTr("WFES - Wright-Fisher Exact Solver (time_dist)")

    color: Universal.chromeLowColor

    visible: true

    width: 640
    minimumWidth: 640
    height: 465
    minimumHeight: 465
    maximumWidth: 640
    maximumHeight: 465

    // Select theme for the application.
    Universal.theme: Universal.Light

    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        UpperMenu {
            id: upperMenu
        }

        Rectangle {
            height: parent.height
            width: parent.width
            color: "transparent"

            anchors {
                top: upperMenu.bottom
                left: parent.left
            }

            RowLayout {
                id: mainGrid
                Layout.fillHeight: true

                ColumnLayout {
                    id: column1
                    width: childrenRect.width
                    height: childrenRect.height

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
                                }
                            }
                            RadioButton {
                                id: radioButtonTimeDistSGV
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. SGV"
                                text: qsTr("Time Dist. SGV")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("TODO.")

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
                                }
                            }

                            RadioButton {
                                id: radioButtonTimeDistSkip
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. Skip"
                                text: qsTr("Time Dist. Skip")

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
                                }
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: modeSectionGrid.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: populationSection
                        width: modeSection.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelPopulation
                            text: "Population:"
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
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputControllerTimeDist.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerTimeDist.ui_a
                            }

                            LabeledTextField {
                                id: inputL
                                text: "l: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerTimeDist.ui_l
                                enabled: (inputControllerTimeDist.ui_modelType == "Time Dist. SGV")
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerTimeDist.ui_c
                            }

                            LabeledTextField {
                                id: inputM
                                text: "m: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerTimeDist.ui_m
                                //enabled: //TODO
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: populationSectionGrid.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: mutationSection
                        width: populationSection.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelMutation
                            text: "Mutation:"
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
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputControllerTimeDist.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: "v: "
                                toolTipText: "Forward mutation rate."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerTimeDist.ui_v
                            }

                            LabeledCheckBox {
                                id: inputR
                                text: "r: "
                                toolTipText: "TODO."
                                checked: inputControllerTimeDist.ui_r
                                //enabled: //TODO
                            }
                        }
                    }

                    Rectangle {
                        height: 1
                        width: mutationSectionGrid.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: selectionSection
                        width: mutationSection.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelSelection
                            text: "Selection:"
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
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputControllerTimeDist.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
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
                    Layout.preferredHeight: parent.height

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
                                    toolTipText: "TODO."
                                    checked: inputControllerTimeDist.ui_output_P
                                    //enabled: //TODO
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

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        textFieldPreferredWidth: 100
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
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
                                        onTextChanged: {
                                            if(comboBoxLibrary.currentText === "Pardiso") {
                                                comboBoxBackend.enabled = false
                                                comboBoxSolver.enabled = false
                                            }else if (comboBoxLibrary.currentText === "ViennaCL"){
                                                comboBoxBackend.enabled = true
                                                comboBoxSolver.enabled = true
                                            }
                                        }
                                    }

                                    LabeledComboBox {
                                        id: comboBoxSolver
                                        text: "Solver:"
                                        toolTipText: "Solver used by viennacl."
                                        model: ["GMRes", "BicGStab"]
                                        enabled: (comboBoxLibrary.currentText === "ViennaCL")
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

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerTimeDist.ui_get_not_exec
                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                if(radioButtonTimeDist.checked)
                                    inputControllerTimeDist.ui_modelType == "Time Dist."
                                if(radioButtonTimeDistSGV.checked)
                                    inputControllerTimeDist.ui_modelType == "Time Dist. SGV"
                                if(radioButtonTimeDistSkip.checked)
                                    inputControllerTimeDist.ui_modelType == "Time Dist. Skip"
                                if(radioButtonTimeDistDual.checked)
                                    inputControllerTimeDist.ui_modelType == "Time Dist. Dual"

                                inputControllerTimeDist.ui_n = inputN.textFieldText
                                inputControllerTimeDist.ui_a = inputA.textFieldText
                                inputControllerTimeDist.ui_l = inputL.textFieldText
                                inputControllerTimeDist.ui_c = inputC.textFieldText
                                inputControllerTimeDist.ui_m = inputM.textFieldText
                                inputControllerTimeDist.ui_u = inputU.textFieldText
                                inputControllerTimeDist.ui_v = inputV.textFieldText
                                inputControllerTimeDist.ui_r = inputR.checked
                                inputControllerTimeDist.ui_s = inputS.textFieldText
                                inputControllerTimeDist.ui_h = inputH.textFieldText

                                inputControllerTimeDist.ui_output_P = inputWriteP.checked
                                inputControllerTimeDist.ui_output_Q = inputWriteQ.checked
                                inputControllerTimeDist.ui_output_R = inputWriteR.checked

                                inputControllerTimeDist.ui_t = inputT.textFieldText

                                inputControllerTimeDist.ui_library = comboBoxLibrary.currentText;
                                inputControllerTimeDist.ui_solver = comboBoxSolver.currentText;

                                if(outputControllerTimeDist.ui_get_error_message === "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    outputControllerTimeDist.ui_execute
                                } else {
                                    messageDialog.text = outputControllerTimeDist.ui_get_error_message
                                    messageDialog.open()
                                }
                                outputControllerWfesSingle.ui_reset_error
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
    }

}
