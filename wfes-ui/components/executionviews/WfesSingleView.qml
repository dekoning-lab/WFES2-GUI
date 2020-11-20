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
    id: rootWfesSingle
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFES Single)")

    color: Universal.chromeLowColor

    visible: false

    width: 945
    minimumWidth: 945
    maximumWidth: 945
    height: 560
    minimumHeight: 560
    maximumHeight: 560

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootWfesSingle.hide();
        root.visible = true;
        rootWfesSingle.updateBackend()
        outputControllerWfesSingle.ui_save_config
    }

    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
        outputControllerWfesSingle.ui_load_config
        rootWfesSingle.updateGUI()
    }

    MessageDialog {
        id: messageDialog
        title: "Warning"
        text: ""
        icon: StandardIcon.Warning
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
                                id: radioButtonAbsorption
                                checked: inputControllerWfesSingle.ui_modelType === "Absorption"
                                text: qsTr("Absorption")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Both fixation and extinction states are absorbing.")

                                onCheckedChanged: {
                                    outputPExt.visible = checked;
                                    outputPFix.visible = checked;
                                    outputTAbs.visible = checked;
                                    outputTAbsStd.visible = checked;
                                    outputText.visible = checked;
                                    outputTextStd.visible = checked;
                                    outputNext.visible = checked;
                                    outputTFix.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputTFixAbsMode.visible = checked;
                                    outputTFixStdAbsMode.visible = checked;
                                    outputRate.visible = !checked;
                                    outputEFreqMut.visible = !checked;
                                    outputEFreqWt.visible = !checked;
                                    outputFEst.visible = !checked;
                                    outputPEst.visible = !checked;
                                    outputTSeg.visible = !checked;
                                    outputTSegStd.visible = !checked;
                                    outputTSegEst.visible = !checked;
                                    outputTSegEstStd.visible = !checked;
                                    outputTSegFix.visible = !checked;
                                    outputTSegFixStd.visible = !checked;
                                    outputTEst.visible = !checked;
                                    outputTEstStd.visible = !checked;
                                    outputEA.visible = !checked;
                                    outputSA.visible = !checked;

                                    inputX.enabled = !checked;
                                    inputM.enabled = checked;
                                    inputp.enabled = checked;
                                    inputX.enabled = !checked;
                                    inputK.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteV.enabled = !checked;
                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = checked;
                                    inputWriteNExt.enabled = checked;
                                    inputWriteNFix.enabled = checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteB.enabled = checked;
                                    inputWriteRes.enabled = checked;

                                }
                            }
                            RadioButton {
                                id: radioButtonFixation
                                checked: inputControllerWfesSingle.ui_modelType === "Fixation"
                                text: qsTr("Fixation")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Only fixation state is absorbing.")

                                onCheckedChanged: {
                                    outputPExt.visible = !checked
                                    outputPFix.visible = !checked;
                                    outputTAbs.visible = !checked;
                                    outputTAbsStd.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputNext.visible = !checked;
                                    outputTFix.visible = checked;
                                    outputTFixStd.visible = checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStdAbsMode.visible = !checked;
                                    outputRate.visible = checked;
                                    outputEFreqMut.visible = !checked;
                                    outputEFreqWt.visible = !checked;
                                    outputFEst.visible = !checked;
                                    outputPEst.visible = !checked;
                                    outputTSeg.visible = !checked;
                                    outputTSegStd.visible = !checked;
                                    outputTSegEst.visible = !checked;
                                    outputTSegEstStd.visible = !checked;
                                    outputTSegFix.visible = !checked;
                                    outputTSegFixStd.visible = !checked;
                                    outputTEst.visible = !checked;
                                    outputTEstStd.visible = !checked;
                                    outputEA.visible = !checked;
                                    outputSA.visible = !checked;

                                    inputX.enabled = !checked;
                                    inputM.enabled = checked;
                                    inputp.enabled = checked;
                                    inputX.enabled = !checked;
                                    inputK.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteV.enabled = !checked;
                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteB.enabled = checked;
                                    inputWriteRes.enabled = checked;
                                }
                            }

                            RadioButton {
                                id: radioButtonEstablishment
                                checked: inputControllerWfesSingle.ui_modelType === "Establishment"
                                text: qsTr("Establishment")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Calculate establishment properties.")

                                onCheckedChanged: {
                                    outputPExt.visible = !checked
                                    outputPFix.visible = !checked;
                                    outputTAbs.visible = !checked;
                                    outputTAbsStd.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputNext.visible = !checked;
                                    outputTFix.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStdAbsMode.visible = !checked;
                                    outputRate.visible = !checked;
                                    outputEFreqMut.visible = !checked;
                                    outputEFreqWt.visible = !checked;
                                    outputFEst.visible = checked;
                                    outputPEst.visible = checked;
                                    outputTSeg.visible = checked;
                                    outputTSegStd.visible = checked;
                                    outputTSegEst.visible = checked;
                                    outputTSegEstStd.visible = checked;
                                    outputTSegFix.visible = checked;
                                    outputTSegFixStd.visible = checked;
                                    outputTEst.visible = checked;
                                    outputTEstStd.visible = checked;
                                    outputEA.visible = !checked;
                                    outputSA.visible = !checked;

                                    inputX.enabled = !checked;
                                    inputM.enabled = checked;
                                    inputp.enabled = checked;
                                    inputX.enabled = !checked;
                                    inputK.enabled = checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteV.enabled = !checked;
                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = !checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteB.enabled = !checked;
                                    inputWriteRes.enabled = checked;
                                }
                            }
                            RadioButton {
                                id: radioButtonFundamental
                                checked: inputControllerWfesSingle.ui_modelType === "Fundamental"
                                text: qsTr("Fundamental")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Calculate the entire fundamental matrix (slow).")

                                onCheckedChanged: {
                                    outputPExt.visible = !checked
                                    outputPFix.visible = !checked;
                                    outputTAbs.visible = !checked;
                                    outputTAbsStd.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputNext.visible = !checked;
                                    outputTFix.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStdAbsMode.visible = !checked;
                                    outputRate.visible = !checked;
                                    outputEFreqMut.visible = !checked;
                                    outputEFreqWt.visible = !checked;
                                    outputFEst.visible = !checked;
                                    outputPEst.visible = !checked;
                                    outputTSeg.visible = !checked;
                                    outputTSegStd.visible = !checked;
                                    outputTSegEst.visible = !checked;
                                    outputTSegEstStd.visible = !checked;
                                    outputTSegFix.visible = !checked;
                                    outputTSegFixStd.visible = !checked;
                                    outputTEst.visible = !checked;
                                    outputTEstStd.visible = !checked;
                                    outputEA.visible = !checked;
                                    outputSA.visible = !checked;

                                    inputX.enabled = !checked;
                                    inputM.enabled = checked;
                                    inputp.enabled = !checked;
                                    inputX.enabled = !checked;
                                    inputK.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteV.enabled = checked;
                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteB.enabled = !checked;
                                    inputWriteRes.enabled = !checked;
                                }
                            }
                            RadioButton {
                                id: radioButtonNonAbsorbing
                                checked: inputControllerWfesSingle.ui_modelType === "Non Absorbing"
                                text: qsTr("Non Absorbing")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Build a non-absorbing WF matrix.")

                                onCheckedChanged: {
                                    outputPExt.visible = !checked
                                    outputPFix.visible = !checked;
                                    outputTAbs.visible = !checked;
                                    outputTAbsStd.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputNext.visible = !checked;
                                    outputTFix.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStdAbsMode.visible = !checked;
                                    outputRate.visible = !checked;
                                    outputEFreqMut.visible = !checked;
                                    outputEFreqWt.visible = !checked;
                                    outputFEst.visible = !checked;
                                    outputPEst.visible = !checked;
                                    outputTSeg.visible = !checked;
                                    outputTSegStd.visible = !checked;
                                    outputTSegEst.visible = !checked;
                                    outputTSegEstStd.visible = !checked;
                                    outputTSegFix.visible = !checked;
                                    outputTSegFixStd.visible = !checked;
                                    outputTEst.visible = !checked;
                                    outputTEstStd.visible = !checked;
                                    outputEA.visible = !checked;
                                    outputSA.visible = !checked;

                                    inputX.enabled = !checked;
                                    inputM.enabled = checked;
                                    inputp.enabled = !checked;
                                    inputX.enabled = !checked;
                                    inputK.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteV.enabled = !checked;
                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = !checked;
                                    inputWriteN.enabled = !checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteB.enabled = !checked;
                                    inputWriteRes.enabled = !checked;
                                }
                            }

                            RadioButton {
                                id: radioButtonEquilibrium
                                checked: inputControllerWfesSingle.ui_modelType === "Equilibrium"
                                text: qsTr("Equilibrium")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Calculate the equilibrium distribtion of allele states.")

                                onCheckedChanged: {
                                    outputPExt.visible = !checked
                                    outputPFix.visible = !checked;
                                    outputTAbs.visible = !checked;
                                    outputTAbsStd.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputNext.visible = !checked;
                                    outputRate.visible = !checked;
                                    outputTFix.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStdAbsMode.visible = !checked;
                                    outputEFreqMut.visible = checked;
                                    outputEFreqWt.visible = checked;
                                    outputFEst.visible = !checked;
                                    outputPEst.visible = !checked;
                                    outputTSeg.visible = !checked;
                                    outputTSegStd.visible = !checked;
                                    outputTSegEst.visible = !checked;
                                    outputTSegEstStd.visible = !checked;
                                    outputTSegFix.visible = !checked;
                                    outputTSegFixStd.visible = !checked;
                                    outputTEst.visible = !checked;
                                    outputTEstStd.visible = !checked;
                                    outputEA.visible = !checked;
                                    outputSA.visible = !checked;

                                    inputX.enabled = !checked;
                                    inputM.enabled = !checked;
                                    inputp.enabled = !checked;
                                    inputX.enabled = !checked;
                                    inputK.enabled = !checked;
                                    inputWriteE.enabled = checked;
                                    inputWriteV.enabled = !checked;
                                    inputWriteQ.enabled = !checked;
                                    inputWriteR.enabled = !checked;
                                    inputWriteN.enabled = !checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;
                                    inputWriteE.enabled = checked;
                                    inputWriteB.enabled = !checked;
                                    inputWriteRes.enabled = checked;
                                }
                            }
                            RadioButton {
                                id: radioButtonAlleleAge
                                checked: inputControllerWfesSingle.ui_modelType === "Allele Age"
                                text: qsTr("Allele Age")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Calculate age of an allele.")

                                onCheckedChanged: {
                                    outputPExt.visible = !checked
                                    outputPFix.visible = !checked;
                                    outputTAbs.visible = !checked;
                                    outputTAbsStd.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputNext.visible = !checked;
                                    outputTFix.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStdAbsMode.visible = !checked;
                                    outputRate.visible = !checked;
                                    outputEFreqMut.visible = !checked;
                                    outputEFreqWt.visible = !checked;
                                    outputFEst.visible = !checked;
                                    outputPEst.visible = !checked;
                                    outputTSeg.visible = !checked;
                                    outputTSegStd.visible = !checked;
                                    outputTSegEst.visible = !checked;
                                    outputTSegEstStd.visible = !checked;
                                    outputTSegFix.visible = !checked;
                                    outputTSegFixStd.visible = !checked;
                                    outputTEst.visible = !checked;
                                    outputTEstStd.visible = !checked;
                                    outputEA.visible = checked;
                                    outputSA.visible = checked;

                                    inputX.enabled = checked;
                                    inputM.enabled = checked;
                                    inputp.enabled = checked;
                                    inputX.enabled = checked;
                                    inputK.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteV.enabled = !checked;
                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = !checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;
                                    inputWriteE.enabled = !checked;
                                    inputWriteB.enabled = !checked;
                                    inputWriteRes.enabled = checked;
                                }
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: modeSectionGrid.width + 10
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
                                textFieldText: inputControllerWfesSingle.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 10e-10;}
                                textFieldText: inputControllerWfesSingle.ui_a
                            }

                            LabeledTextField {
                                id: inputp
                                text: "p: "
                                toolTipText: "Starting number of copies - no integration."
                                validator: IntValidator {bottom: 0; top: 500000;}
                                textFieldText: inputControllerWfesSingle.ui_p
                                enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                          inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                          inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                          inputControllerWfesSingle.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputc
                                text: "c: "
                                toolTipText: "Starting number of copies integration cutoff."
                                validator: DoubleValidator {bottom: 0; top: 10e-3;}
                                textFieldText: inputControllerWfesSingle.ui_c
                            }

                            LabeledTextField {
                                id: inputX
                                text: "x: "
                                toolTipText: "Observed number of copies (--allele-age only)."
                                validator: IntValidator {bottom: 0; top: 500000;}
                                textFieldText: inputControllerWfesSingle.ui_x
                                enabled: (inputControllerWfesSingle.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputK
                                text: "k: "
                                toolTipText: "Odds ratio (--establishment only)."
                                textFieldText: inputControllerWfesSingle.ui_k
                                enabled: (inputControllerWfesSingle.ui_modelType == "Establishment")
                            }
                        }

                    }

                    Rectangle {
                        height: 1
                        width: modeSectionGrid.width + 10
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
                                textFieldText: inputControllerWfesSingle.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: "v: "
                                toolTipText: "Forward mutation rate."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSingle.ui_v
                            }

                            LabeledCheckBox {
                                id: inputM
                                text: "m: "
                                toolTipText: "No recurrent mutation."
                                checked: inputControllerWfesSingle.ui_m
                                enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                          inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                          inputControllerWfesSingle.ui_modelType == "Fundamental" ||
                                          inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                          inputControllerWfesSingle.ui_modelType == "Allele Age" ||
                                          inputControllerWfesSingle.ui_modelType == "Non Absorbing")
                            }
                        }
                    }

                    Rectangle {
                        height: 1
                        width: modeSectionGrid.width + 10
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
                                textFieldText: inputControllerWfesSingle.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                validator: DoubleValidator {bottom: 0; top: 1;}
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
                                    checked: inputControllerWfesSingle.ui_output_Q
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                              inputControllerWfesSingle.ui_modelType == "Fundamental" ||
                                              inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                              inputControllerWfesSingle.ui_modelType == "Allele Age" ||
                                              inputControllerWfesSingle.ui_modelType == "Non Absorbing")

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: "R: "
                                    toolTipText: "Output R as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_R
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                              inputControllerWfesSingle.ui_modelType == "Fundamental" ||
                                              inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                              inputControllerWfesSingle.ui_modelType == "Allele Age")
                                }

                                LabeledCheckBox {
                                    id: inputWriteB
                                    text: "B: "
                                    toolTipText: "Output B as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_B
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteN
                                    text: "N: "
                                    toolTipText: "Output N as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_N
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                              inputControllerWfesSingle.ui_modelType == "Fundamental")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNExt
                                    toolTipText: "Output N ext. (extintion-conditional sojourn) as CSV file."
                                    text: "N ext.: "
                                    checked: inputControllerWfesSingle.ui_output_NExt
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNFix
                                    text: "N fix.: "
                                    toolTipText: "Output N fix. (fixation-conditional sojourn) as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_NFix
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteI
                                    text: "I: "
                                    toolTipText: "Output I (Initial probability distribution) as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_I
                                }

                                LabeledCheckBox {
                                    id: inputWriteE
                                    text: "E: "
                                    toolTipText: "Output E (Equilibrium frequencies) as CSV file (Equilibrium mode only)."
                                    checked: inputControllerWfesSingle.ui_output_E
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Equilibrium")
                                }

                                LabeledCheckBox {
                                    id: inputWriteV
                                    text: "V: "
                                    toolTipText: "Output V (Variance time matrix) as CSV file (Fundamental mode only)."
                                    checked: inputControllerWfesSingle.ui_output_V
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fundamental")
                                }


                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: "Res: "
                                    toolTipText: "Output Res (Generated results at right side) as CSV file."
                                    checked: inputControllerWfesSingle.ui_output_Res
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                              inputControllerWfesSingle.ui_modelType == "Equilibrium" ||
                                              inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                              inputControllerWfesSingle.ui_modelType == "Allele Age")
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
                                bottomMenu.visibleProgressBar = false
                            }
                        }

                        Button {
                            id: executeButton
                            Layout.margins: 10
                            Layout.alignment: Qt.AlignRight
                            text: "Execute"

                            onEnabledChanged: {
                                if(outputControllerWfesSingle.ui_get_not_exec) {
                                    imageOutputController.image_changed()
                                }
                                console.log(outputControllerWfesSingle.ui_get_error_message)
                                if(outputControllerWfesSingle.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerWfesSingle.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerWfesSingle.ui_reset_error
                                }
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerWfesSingle.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {

                                var error = checkIntegrity()

                                updateBackend();

                                if(error === "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerWfesSingle.ui_execute
                                } else {
                                    messageDialog.text = error
                                    messageDialog.open()
                                }

                            }

                        }

                    }
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
                            font.bold: true
                        }

                        ColumnLayout {

                            anchors {
                                top: labelFinalOutput.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: outputPExt
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P ext. : "
                                toolTipText: "Probability of extintion."
                                textFieldText: outputControllerWfesSingle.ui_get_p_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputPFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P fix. : "
                                toolTipText: "Probability of fixation."
                                textFieldText: outputControllerWfesSingle.ui_get_p_fix
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbs
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T abs. : "
                                toolTipText: "Absorption time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_abs
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbsStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T abs. std.: "
                                toolTipText: "Standard absorption time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_abs_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputText
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T ext.: "
                                toolTipText: "Extintion time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTextStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T ext. std.: "
                                toolTipText: "Standard extintion time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_ext_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputNext
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "N ext.: "
                                toolTipText: "Number of generations till extintion."
                                textFieldText: outputControllerWfesSingle.ui_get_n_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix.: "
                                toolTipText: "Fixation time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputTFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix. std.: "
                                toolTipText: "Standard fixation time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_std
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputTFixAbsMode
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix.: "
                                toolTipText: "Fixation time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_abs_mode
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFixStdAbsMode
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix. std.: "
                                toolTipText: "Standard fixation time."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_std_abs_mode
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Rate: "
                                toolTipText: "Rate."
                                textFieldText: outputControllerWfesSingle.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputEFreqMut
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E[freq mut]: "
                                textFieldText: outputControllerWfesSingle.ui_get_e_freq_mut
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputEFreqWt
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E[freq  wt]: "
                                textFieldText: outputControllerWfesSingle.ui_get_e_freq_wt
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputFEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "F est.: "
                                textFieldText: outputControllerWfesSingle.ui_get_f_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputPEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P est.: "
                                textFieldText: outputControllerWfesSingle.ui_get_p_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSeg
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. std.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. ext.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. ext. std.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. fix.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_fix
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. fix. std.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_fix_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T est.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T est. std.: "
                                textFieldText: outputControllerWfesSingle.ui_get_t_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputEA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E(A): "
                                textFieldText: outputControllerWfesSingle.ui_get_e_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            LabeledTextField {
                                id: outputSA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "S(A): "
                                textFieldText: outputControllerWfesSingle.ui_get_s_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
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
            value: !outputControllerWfesSingle.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfesSingle.ui_progress

            executionTime: {
                outputControllerWfesSingle.ui_get_time == "" ? "" : outputControllerWfesSingle.ui_get_time + "s"
            }
            anchors {
                top: content.bottom
                left: parent.left
            }
        }
    }

    function updateGUI() {
        radioButtonAbsorption.checked = inputControllerWfesSingle.ui_modelType == "Absorption"
        radioButtonFixation.checked = inputControllerWfesSingle.ui_modelType == "Fixation"
        radioButtonEstablishment.checked = inputControllerWfesSingle.ui_modelType == "Establishment"
        radioButtonFundamental.checked = inputControllerWfesSingle.ui_modelType == "Fundamental"
        radioButtonNonAbsorbing.checked = inputControllerWfesSingle.ui_modelType == "Non Absorbing"
        radioButtonEquilibrium.checked = inputControllerWfesSingle.ui_modelType == "Equilibrium"
        radioButtonAlleleAge.checked = inputControllerWfesSingle.ui_modelType == "Allele Age"

        inputN.textFieldText = inputControllerWfesSingle.ui_n
        inputA.textFieldText = inputControllerWfesSingle.ui_a
        inputp.textFieldText = inputControllerWfesSingle.ui_p
        inputc.textFieldText = inputControllerWfesSingle.ui_c
        inputX.textFieldText = inputControllerWfesSingle.ui_x
        inputK.textFieldText = inputControllerWfesSingle.ui_k
        inputU.textFieldText = inputControllerWfesSingle.ui_u
        inputV.textFieldText = inputControllerWfesSingle.ui_v
        inputM.checked = inputControllerWfesSingle.ui_m
        inputS.textFieldText = inputControllerWfesSingle.ui_s
        inputH.textFieldText = inputControllerWfesSingle.ui_h

        inputWriteQ.checked = inputControllerWfesSingle.ui_output_Q
        inputWriteR.checked = inputControllerWfesSingle.ui_output_R
        inputWriteB.checked = inputControllerWfesSingle.ui_output_B
        inputWriteN.checked = inputControllerWfesSingle.ui_output_N
        inputWriteNExt.checked = inputControllerWfesSingle.ui_output_NExt
        inputWriteNFix.checked = inputControllerWfesSingle.ui_output_NFix
        inputWriteI.checked = inputControllerWfesSingle.ui_output_I
        inputWriteE.checked = inputControllerWfesSingle.ui_output_E
        inputWriteV.checked = inputControllerWfesSingle.ui_output_V
        inputWriteRes.checked = inputControllerWfesSingle.ui_output_Res

        inputForce.checked = inputControllerWfesSingle.ui_force
        inputT.textFieldText = inputControllerWfesSingle.ui_t
        inputI.textFieldText = inputControllerWfesSingle.ui_initial_distribution

        var library = inputControllerWfesSingle.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfesSingle.ui_solver
        if(library === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(library === "BicGStab")
            comboBoxSolver.currentIndex = 1
    }

    function updateBackend() {

        // Set mode in backend.
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
        inputControllerWfesSingle.ui_p = inputp.textFieldText
        inputControllerWfesSingle.ui_c = inputc.textFieldText
        inputControllerWfesSingle.ui_x = inputX.textFieldText
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

        if(parseInt(inputp.textFieldText) < 0)
            error += " - Starting copies (p) is quite small, if you want to disable it just use 0. \n \n"
        if(parseInt(inputp.textFieldText) > parseInt(inputN.textFieldText))
            error += " - Starting Copies (p) is quite large. The maximum value allowed is N. \n \n"

        if(parseFloat(inputc.textFieldText) < 0)
            error += " - Integration Cutoff (c) is quite small. It must be at least 0. \n \n"
        if(parseFloat(inputc.textFieldText) > 10e-3)
            error += " - Integration Cutoff (c) is quite large. The maximum value allowed is 10e-3. \n \n"

        if(parseInt(inputX.textFieldText) < 1)
            error += " - Observed copies (x) is quite small. It must be at least 1. \n \n"
        if(parseInt(inputX.textFieldText) > parseInt(inputN.textFieldText))
            error += " - Observed Copies (x) is quite large. The maximum value allowed is N. \n \n"

        // Odds ratio (k) does not have limits, at least in the code. The default value is 1.

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