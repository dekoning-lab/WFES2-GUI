import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

//TODO Implement value validators and return exceptions.
ApplicationWindow {
    id: rootPhaseType
    title: qsTr("WFES - Wright-Fisher Exact Solver (Phase Type)")

    color: Universal.chromeLowColor

    visible: true

    width: 945
    minimumWidth: 945
    height: 500
    minimumHeight: 500
    maximumWidth: 945
    maximumHeight: 500

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootPhaseType.destroy();
        root.visible = true;
    }

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
                            columns: 1
                            anchors {
                                top: labelModel.bottom
                                left: parent.left
                                margins: 10
                            }

                            RadioButton {
                                id: radioButtonPhaseTypeDist
                                checked: inputControllerWfesSingle.ui_modelType === "TODO"
                                text: qsTr("Phase Type Dist.")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("TODO.")

                                onCheckedChanged: {
                                    //TODO
                                }
                            }
                            RadioButton {
                                id: radioButtonFixation
                                checked: inputControllerWfesSingle.ui_modelType === "TODO"
                                text: qsTr("Phase Type Moment")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("TODO.")

                                onCheckedChanged: {
                                    //TODO.
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
                                textFieldText: inputControllerWfesSingle.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_a
                            }

                            LabeledTextField {
                                id: inputl
                                text: "l: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_l
                                //enabled: //TODO
                            }

                            LabeledTextField {
                                id: inputc
                                text: "c: "
                                toolTipText: "Starting number of copies integration cutoff."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_c
                            }

                            LabeledTextField {
                                id: inputM
                                text: "m: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_m
                                //enabled: //TODO
                            }

                            LabeledTextField {
                                id: inputK
                                text: "k: "
                                toolTipText: "Odds ratio (--establishment only)."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_k
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
                                textFieldText: inputControllerWfesSingle.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: "v: "
                                toolTipText: "Forward mutation rate."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_v
                            }

                            LabeledCheckBox {
                                id: inputR
                                text: "r: "
                                toolTipText: "No recurrent mutation."
                                checked: inputControllerWfesSingle.ui_r
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
                                textFieldText: inputControllerWfesSingle.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSingle.ui_h
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
                                    checked: inputControllerWfesSingle.ui_output_Q
                                    //enabled: //TODO

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: "R: "
                                    toolTipText: "Output R as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_R
                                    //enabled: //TODO
                                }

                                LabeledCheckBox {
                                    id: inputWriteP
                                    text: "P: "
                                    toolTipText: "Output P as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_P
                                    //enabled: //TODO
                                }

                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: "Res: "
                                    toolTipText: "Output Res (Generated results at right side) as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_Res
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

                                    LabeledCheckBox {
                                        id: inputForce
                                        toolTipText: "Do not perform parameter checks."
                                        text: "Force: "
                                        checked: inputControllerWfesSingle.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        toolTipText: "Number of threads for OpenMP."
                                        labelPreferredWidth: 10
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputControllerWfesSingle.ui_t
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

                                    LabeledTextField {
                                        id: inputI
                                        text: "I. Dist.: "
                                        toolTipText: "Path to initial probability distribution CSV file."
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputControllerWfesSingle.ui_initial_distribution
                                    }

                                    Button{
                                        text: "Search"
                                        onClicked: fileDialog.open()
                                    }


                                    FileDialog {
                                        id: fileDialog
                                        title: "Please choose a csv file"
                                        nameFilters: [ "csv files (*.csv)" ]
                                        onAccepted: {
                                            var path = fileDialog.fileUrl.toString()
                                            path = path.replace(/^(file:\/{2})/,"");
                                            inputI.textFieldText = path
                                        }
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
                                value: !outputControllerWfesSingle.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerWfesSingle.ui_stop
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
                                value: outputControllerWfesSingle.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                    /*// Set mode in backend.
                                    if(radioButtonAbsorption.checked)
                                        inputControllerWfesSingle.ui_modelType = "Absorption"
                                    else if (radioButtonFixation.checked)
                                        inputControllerWfesSingle.ui_modelType = "Fixation"
                                    else if (radioButtonEstablishment.checked)
                                        inputControllerWfesSingle.ui_modelType = "Establishment"
                                    else if (radioButtonFundamental.checked)
                                        inputControllerWfesSingle.ui_modelType = "Fundamental"
                                    else if (radioButtonNonAbsorbing.checked)
                                        inputControllerWfesSingle.ui_modelType = "Non Absorbing"
                                    else if (radioButtonEquilibrium.checked)
                                        inputControllerWfesSingle.ui_modelType = "Equilibrium"
                                    else if (radioButtonAlleleAge.checked)
                                        inputControllerWfesSingle.ui_modelType = "Allele Age"

                                    inputControllerWfesSingle.ui_n = inputN.textFieldText
                                    inputControllerWfesSingle.ui_a = inputA.textFieldText
                                    if(inputControllerWfesSingle.ui_modelType == "Fixation" || inputControllerWfesSingle.ui_modelType == "Absorption" || inputControllerWfesSingle.ui_modelType == "Establishment" || inputControllerWfesSingle.ui_modelType == "Allele Age")
                                        inputControllerWfesSingle.ui_p = inputp.textFieldText
                                    inputControllerWfesSingle.ui_c = inputc.textFieldText
                                    if(inputControllerWfesSingle.ui_modelType == "Allele Age")
                                        inputControllerWfesSingle.ui_x = inputX.textFieldText
                                    if(inputControllerWfesSingle.ui_modelType == "Establishment")
                                        inputControllerWfesSingle.ui_k = inputK.textFieldText
                                    inputControllerWfesSingle.ui_u = inputU.textFieldText
                                    inputControllerWfesSingle.ui_v = inputV.textFieldText
                                    inputControllerWfesSingle.ui_m = inputM.checked
                                    inputControllerWfesSingle.ui_s = inputS.textFieldText
                                    inputControllerWfesSingle.ui_h = inputH.textFieldText

                                    inputControllerWfesSingle.ui_output_Q = inputWriteQ.checked
                                    inputControllerWfesSingle.ui_output_R = inputWriteR.checked
                                    inputControllerWfesSingle.ui_output_B = inputWriteB.checked
                                    inputControllerWfesSingle.ui_output_N = inputWriteN.checked
                                    inputControllerWfesSingle.ui_output_NExt = inputWriteNExt.checked
                                    inputControllerWfesSingle.ui_output_NFix = inputWriteNFix.checked
                                    inputControllerWfesSingle.ui_output_I = inputWriteI.checked
                                    inputControllerWfesSingle.ui_output_E = inputWriteE.checked
                                    inputControllerWfesSingle.ui_output_V = inputWriteV.checked
                                    inputControllerWfesSingle.ui_output_Res = inputWriteRes.checked

                                    inputControllerWfesSingle.ui_force = inputForce.checked
                                    inputControllerWfesSingle.ui_t = inputT.textFieldText

                                    inputControllerWfesSingle.ui_initial_distribution = inputI.textFieldText

                                    inputControllerWfesSingle.ui_library = comboBoxLibrary.currentText;
                                    inputControllerWfesSingle.ui_solver = comboBoxSolver.currentText;

                                if(outputControllerWfesSingle.ui_get_error_message == "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    outputControllerWfesSingle.ui_execute
                                } else {
                                    messageDialog.text = outputControllerWfesSingle.ui_get_error_message
                                    messageDialog.open()
                                }
                                outputControllerWfesSingle.ui_reset_error*/
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

                Rectangle {
                    id: separator2
                    width: 1
                    Layout.fillHeight: true
                    color: Universal.baseHighColor
                    Layout.topMargin: 10
                    Layout.bottomMargin:10
                }

                ColumnLayout {
                    id: column3
                    Layout.margins: 10
                    Layout.alignment: Qt.AlignTop

                    Rectangle {
                        id: finalOutputSection
                        color: "transparent"
                        height: childrenRect.height
                        width: childrenRect.width

                        Label {
                            id: labelFinalOutput
                            text: "Output:"
                        }

                        ColumnLayout {

                            anchors {
                                top: labelFinalOutput.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: outputMean
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Mean: "
                                textFieldText: outputControllerWfesSingle.ui_get_mean
                                readOnly: true
                                // TODO visible: radioButtonAlleleAge.checked
                            }

                            LabeledTextField {
                                id: outputStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Std: "
                                textFieldText: outputControllerWfesSingle.ui_get_std
                                readOnly: true
                                // TODO visible: radioButtonAlleleAge.checked
                            }

                            Label {
                                id: labelMoments
                                text: "Moments:"
                            }

                            Rectangle {
                                width: prueba.width + 1
                                height: childrenRect.height + 1
                                color: "transparent"
                                border.width: 1

                                ScrollView {
                                    width: prueba.width
                                    height: 200
                                    clip: true
                                    topPadding: 1
                                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                                    contentHeight: 200
                                    contentWidth: prueba.width

                                    ListView {
                                        model: 20
                                        delegate: ItemDelegate {
                                            text: "Item " + (index + 1)
                                            width: prueba.width
                                        }
                                    }
                                }

                            }

                            LabeledTextField {
                                id: outputTime
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Time (s): "
                                toolTipText: "Execution time in seconds."
                                textFieldText: outputControllerWfesSingle.ui_get_time
                                readOnly: true
                            }

                            LabeledTextField {
                                id: prueba
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Status: "
                                toolTipText: "Status of the current execution."
                                readOnly: true
                                textFieldText: outputControllerWfesSingle.ui_progress
                            }

                        }
                    }
                }
            }
        }
    }

}
