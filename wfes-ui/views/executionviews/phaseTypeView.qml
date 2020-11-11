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
    maximumWidth: 945
    height: 485
    minimumHeight: 485
    maximumHeight: 485

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
                                checked: inputControllerPhaseType.ui_modelType === "Phase Type Dist."
                                text: qsTr("Phase Type Dist.")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Calculate distribution of absorption times for a fixation-only model.")

                                onCheckedChanged: {
                                    inputN.enabled = checked
                                    inputS.enabled = checked
                                    inputH.enabled = checked
                                    inputU.enabled = checked
                                    inputV.enabled = checked
                                    inputA.enabled = checked
                                    inputT.enabled = checked
                                    inputK.enabled = !checked
                                    inputC.enabled = checked
                                    inputM.enabled = checked
                                    inputR.enabled = checked

                                    inputWriteQ.enabled = checked
                                    inputWriteP.enabled = checked
                                    inputWriteR.enabled = checked
                                    inputWriteMoments.enabled = !checked
                                    inputWriteRes.enabled = !checked
                                }
                            }
                            RadioButton {
                                id: radioButtonPhaseTypeMoments
                                checked: inputControllerPhaseType.ui_modelType === "Phase Type Moments"
                                text: qsTr("Phase Type Moments")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Calculate moments of absorption times for a fixation-only model.")

                                onCheckedChanged: {
                                    inputN.enabled = checked
                                    inputS.enabled = checked
                                    inputH.enabled = checked
                                    inputU.enabled = checked
                                    inputV.enabled = checked
                                    inputA.enabled = checked
                                    inputT.enabled = checked
                                    inputK.enabled = checked
                                    inputC.enabled = !checked
                                    inputM.enabled = !checked
                                    inputR.enabled = !checked

                                    inputWriteQ.enabled = checked
                                    inputWriteP.enabled = !checked
                                    inputWriteR.enabled = checked
                                    inputWriteMoments.enabled = checked
                                    inputWriteRes.enabled = checked
                                }
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: populationSectionGrid.width
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
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerPhaseType.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 10e-10;}
                                textFieldText: inputControllerPhaseType.ui_a
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "Starting number of copies integration cutoff."
                                validator: DoubleValidator {bottom: 0; top: 10e-3;}
                                textFieldText: inputControllerPhaseType.ui_c
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Dist."
                            }

                            LabeledTextField {
                                id: inputM
                                text: "m: "
                                toolTipText: "TODO."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerPhaseType.ui_m
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Dist."
                            }

                            LabeledTextField {
                                id: inputK
                                text: "k: "
                                toolTipText: "Number of Moments."
                                textFieldText: inputControllerPhaseType.ui_k
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
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
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerPhaseType.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: "v: "
                                toolTipText: "Forward mutation rate."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerPhaseType.ui_v
                            }

                            LabeledCheckBox {
                                id: inputR
                                text: "r: "
                                toolTipText: "No recurrent mutation."
                                checked: inputControllerPhaseType.ui_r
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
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
                                validator: DoubleValidator {bottom: -1; top: 1;}
                                textFieldText: inputControllerPhaseType.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                validator: DoubleValidator {bottom: 0; top: 1;}
                                textFieldText: inputControllerPhaseType.ui_h
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
                                    checked: inputControllerPhaseType.ui_output_Q
                                    //enabled: //TODO

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: "R: "
                                    toolTipText: "Output R as CSV file."
                                    checked: inputControllerPhaseType.ui_output_R
                                    //enabled: //TODO
                                }

                                LabeledCheckBox {
                                    id: inputWriteP
                                    text: "P: "
                                    toolTipText: "Output P as CSV file."
                                    checked: inputControllerPhaseType.ui_output_P
                                    enabled: inputControllerPhaseType.ui_modelType == "Phase Type Dist."

                                }

                                LabeledCheckBox {
                                    id: inputWriteMoments
                                    text: "Moments: "
                                    toolTipText: "//TODO. (Always enabled)."
                                    checked: true
                                    enabledCheckBox: false
                                    enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
                                }

                                Label {
                                    // Empty, so Res is always at right.
                                }

                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: "Res: "
                                    toolTipText: "Output Res (Generated results at right side) as CSV file."
                                    checked: inputControllerPhaseType.ui_output_Res
                                    enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
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
                                ColumnLayout {
                                    width: childrenRect.width

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
                                            validator: IntValidator {bottom: 1;}
                                            textFieldText: inputControllerWfesSingle.ui_t
                                        }
                                    }
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
                                value: !outputControllerPhaseType.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerPhaseType.ui_stop
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
                                if(outputControllerPhaseType.ui_get_not_exec)
                                    imageOutputController.image_changed()
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerPhaseType.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()

                                updateBackend()

                                if(error === "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerPhaseType.ui_execute
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
                                textFieldText: outputControllerPhaseType.ui_get_mean
                                readOnly: true
                                enabled: radioButtonPhaseTypeMoments.checked
                            }

                            LabeledTextField {
                                id: outputStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Std: "
                                textFieldText: outputControllerPhaseType.ui_get_std
                                readOnly: true
                                enabled: radioButtonPhaseTypeMoments.checked
                            }

                        }

                    }

                    Label {
                        id: labelMoments
                        text: "Moments:"
                        enabled: radioButtonPhaseTypeMoments.checked
                    }

                    Rectangle {
                        width: outputStd.width
                        height: childrenRect.height + 1
                        color: "transparent"
                        border.width: 1
                        enabled: radioButtonPhaseTypeMoments.checked

                        Layout.alignment: Qt.AlignTop
                        Layout.margins: 10

                        ScrollView {
                            width: parent.width - 1
                            height: 200
                            clip: true
                            topPadding: 1
                            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                            contentHeight: 200
                            contentWidth: outputStd.width
                            enabled: radioButtonPhaseTypeMoments.checked
                            ListView {
                                id: listViewMoments
                                model: outputControllerPhaseType.ui_moments
                                enabled: radioButtonPhaseTypeMoments.checked
                                delegate: ItemDelegate {
                                  width: outputStd.width
                                  height: 25
                                  Text {
                                      text: modelData;
                                      width: parent.width;
                                      height: parent.height;
                                      enabled: radioButtonPhaseTypeMoments.checked
                                  }
                                }
                            }
                        }

                    }

                }
            }
        }

        Rectangle {
            height: 1
            width: parent.width
            color: Universal.baseHighColor
            anchors {
                top: content.bottom
                left: parent.left
            }
        }

        Binding {
            target: bottomMenu
            property: "visibleProgressBar"
            value: !outputControllerPhaseType.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerPhaseType.ui_progress

            executionTime: {
                outputControllerPhaseType.ui_get_time == "" ? "" : outputControllerPhaseType.ui_get_time + "s"
            }
            anchors {
                top: content.bottom
                left: parent.left
            }
        }

    }

    function updateGUI() {
        radioButtonPhaseTypeDist.checked = inputControllerPhaseType.ui_modelType == "Phase Type Dist."
        radioButtonPhaseTypeMoments.checked = inputControllerPhaseType.ui_modelType == "Phase Type Moments"

        inputN.textFieldText = inputControllerPhaseType.ui_n
        inputS.textFieldText = inputControllerPhaseType.ui_s
        inputH.textFieldText = inputControllerPhaseType.ui_h
        inputU.textFieldText = inputControllerPhaseType.ui_u
        inputV.textFieldText = inputControllerPhaseType.ui_v
        inputA.textFieldText = inputControllerPhaseType.ui_a
        inputT.textFieldText = inputControllerPhaseType.ui_t
        inputK.textFieldText = inputControllerPhaseType.ui_k
        inputC.textFieldText = inputControllerPhaseType.ui_c
        inputM.textFieldText = inputControllerPhaseType.ui_m
        inputR.checked = inputControllerPhaseType.ui_r

        inputWriteP.checked = inputControllerPhaseType.ui_output_P

        inputWriteQ.checked = inputControllerPhaseType.ui_output_Q
        inputWriteR.checked = inputControllerPhaseType.ui_output_R

        inputWriteRes.checked = inputControllerPhaseType.ui_output_Res
        inputWriteMoments.checked = inputControllerPhaseType.ui_output_Moments

        var library = inputControllerPhaseType.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerPhaseType.ui_solver
        if(library === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(library === "BicGStab")
            comboBoxSolver.currentIndex = 1
    }

    function updateBackend() {

        // Set mode in backend.
        if(radioButtonPhaseTypeDist.checked)
            inputControllerPhaseType.ui_modelType = "Phase Type Dist."
        if(radioButtonPhaseTypeMoments.checked)
            inputControllerPhaseType.ui_modelType = "Phase Type Moments"

        inputControllerPhaseType.ui_n = inputN.textFieldText
        inputControllerPhaseType.ui_s = inputS.textFieldText
        inputControllerPhaseType.ui_h = inputH.textFieldText
        inputControllerPhaseType.ui_u = inputU.textFieldText
        inputControllerPhaseType.ui_v = inputV.textFieldText
        inputControllerPhaseType.ui_a = inputA.textFieldText
        inputControllerPhaseType.ui_t = inputT.textFieldText
        inputControllerPhaseType.ui_k = inputK.textFieldText
        inputControllerPhaseType.ui_c = inputC.textFieldText
        inputControllerPhaseType.ui_m = inputM.textFieldText
        inputControllerPhaseType.ui_r = inputR.checked

        inputControllerPhaseType.ui_output_P = inputWriteP.checked

        inputControllerPhaseType.ui_output_Q = inputWriteQ.checked
        inputControllerPhaseType.ui_output_R = inputWriteR.checked

        inputControllerPhaseType.ui_output_Res = inputWriteRes.checked
        inputControllerPhaseType.ui_output_Moments = inputWriteMoments.checked

        inputControllerPhaseType.ui_library = comboBoxLibrary.currentText;
        inputControllerPhaseType.ui_solver = comboBoxSolver.currentText;

    }


    function checkIntegrity() {
        var error = ""

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
        if(parseFloat(inputC.textFieldText) > 10e-3)
            error += " - Integration Cutoff (c) is quite large. The maximum value allowed is 10e-3. \n \n"

        if(parseInt(inputM.textFieldText) < 2)
            error += " - Maximum Number of Generations (m) is quite small, it must be at least 2. \n \n"
        if(!inputForce.checked && parseInt(inputM.textFieldText) > 50000)
            error += " - Maximum Number of Generations (m) is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"

        // Moments (k) does not have upper limits, at least in the code. The default value is 20.
        if(parseInt(inputK.textFieldText) < 2)
            error += " - Number of Moments (k) is quite small, it must be at least 1. \n \n"

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

        // Number of threads (t) does not have upper limites, since it depends on the hardware available.
        if(parseInt(inputT.textFieldText) < 1)
            error += " - Number of Threads (t) is quite small, it must be at least 1. \n \n"

        //TODO Check if Initial Distribution (I) file exists.

        return error.split("\n \n")[0];

    }
}
