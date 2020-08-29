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
    id: root
    title: qsTr("WFES - Wright-Fisher Exact Solver (wfes_single)")

    color: Universal.chromeLowColor

    visible: true

    width: 945
    minimumWidth: 945
    height: 570
    minimumHeight: 570
    maximumWidth: 945
    maximumHeight: 570

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
                                id: radioButtonAbsorption
                                checked: true
                                text: qsTr("Absorption")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Both fixation and extinction states are absorbing.")

                                onCheckedChanged: {
                                    outputPExt.visible = checked
                                    outputPFix.visible = checked;
                                    outputTAbs.visible = checked;
                                    outputTAbsStd.visible = checked;
                                    outputText.visible = checked;
                                    outputTextStd.visible = checked;
                                    outputNext.visible = checked;
                                    outputTFix.visible = checked;
                                    outputTFixStd.visible = checked;
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
                                textFieldText: inputController.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_a
                            }

                            LabeledTextField {
                                id: inputp
                                text: "p: "
                                toolTipText: "Starting number of copies - no integration."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_p
                                enabled: (inputController.ui_modelType == "Fixation" ||
                                          inputController.ui_modelType == "Absorption" ||
                                          inputController.ui_modelType == "Establishment" ||
                                          inputController.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputc
                                text: "c: "
                                toolTipText: "Starting number of copies integration cutoff."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_c
                            }

                            LabeledTextField {
                                id: inputX
                                text: "x: "
                                toolTipText: "Observed number of copies (--allele-age only)."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_x
                                enabled: (inputController.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputK
                                text: "k: "
                                toolTipText: "Odds ratio (--establishment only)."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_k
                                enabled: (inputController.ui_modelType == "Establishment")
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
                                textFieldText: inputController.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: "v: "
                                toolTipText: "Forward mutation rate."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_v
                            }

                            LabeledCheckBox {
                                id: inputM
                                text: "m: "
                                toolTipText: "No recurrent mutation."
                                checked: inputController.ui_m
                                enabled: (inputController.ui_modelType == "Fixation" ||
                                          inputController.ui_modelType == "Absorption" ||
                                          inputController.ui_modelType == "Fundamental" ||
                                          inputController.ui_modelType == "Establishment" ||
                                          inputController.ui_modelType == "Allele Age" ||
                                          inputController.ui_modelType == "Non Absorbing")
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
                                textFieldText: inputController.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_h
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
                                    checked: inputController.ui_output_Q
                                    enabled: (inputController.ui_modelType == "Fixation" ||
                                              inputController.ui_modelType == "Absorption" ||
                                              inputController.ui_modelType == "Fundamental" ||
                                              inputController.ui_modelType == "Establishment" ||
                                              inputController.ui_modelType == "Allele Age" ||
                                              inputController.ui_modelType == "Non Absorbing")

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: "R: "
                                    toolTipText: "Output R as CSV file."
                                    checked: inputController.ui_output_R
                                    enabled: (inputController.ui_modelType == "Fixation" ||
                                              inputController.ui_modelType == "Absorption" ||
                                              inputController.ui_modelType == "Fundamental" ||
                                              inputController.ui_modelType == "Establishment" ||
                                              inputController.ui_modelType == "Allele Age")
                                }

                                LabeledCheckBox {
                                    id: inputWriteB
                                    text: "B: "
                                    toolTipText: "Output B as CSV file."
                                    checked: inputController.ui_output_B
                                    enabled: (inputController.ui_modelType == "Fixation" ||
                                              inputController.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteN
                                    text: "N: "
                                    toolTipText: "Output N as CSV file."
                                    checked: inputController.ui_output_N
                                    enabled: (inputController.ui_modelType == "Fixation" ||
                                              inputController.ui_modelType == "Absorption" ||
                                              inputController.ui_modelType == "Fundamental")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNExt
                                    toolTipText: "Output N ext. (extintion-conditional sojourn) as CSV file."
                                    text: "N ext.: "
                                    checked: inputController.ui_output_NExt
                                    enabled: (inputController.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNFix
                                    text: "N fix.: "
                                    toolTipText: "Output N fix. (fixation-conditional sojourn) as CSV file."
                                    checked: inputController.ui_output_NFix
                                    enabled: (inputController.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteI
                                    text: "I: "
                                    toolTipText: "Output I (Initial probability distribution) as CSV file."
                                    checked: inputController.ui_output_I
                                }

                                LabeledCheckBox {
                                    id: inputWriteE
                                    text: "E: "
                                    toolTipText: "Output E (Equilibrium frequencies) as CSV file (Equilibrium mode only)."
                                    checked: inputController.ui_output_E
                                    enabled: (inputController.ui_modelType == "Equilibrium")
                                }

                                LabeledCheckBox {
                                    id: inputWriteV
                                    text: "V: "
                                    toolTipText: "Output V (Variance time matrix) as CSV file (Fundamental mode only)."
                                    checked: inputController.ui_output_V
                                    enabled: (inputController.ui_modelType == "Fundamental")
                                }


                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: "Res: "
                                    toolTipText: "Output Res (Generated results at right side) as CSV file."
                                    checked: inputController.ui_output_Res
                                    enabled: (inputController.ui_modelType == "Fixation" ||
                                              inputController.ui_modelType == "Absorption" ||
                                              inputController.ui_modelType == "Equilibrium" ||
                                              inputController.ui_modelType == "Establishment" ||
                                              inputController.ui_modelType == "Allele Age")
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
                                        checked: inputController.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputController.ui_t
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
                                        model: ["MixedCG", "CG", "BicGStab", "GMRes"]
                                        enabled: (comboBoxLibrary.currentText === "ViennaCL")
                                    }

                                    LabeledComboBox {
                                        id: comboBoxBackend
                                        text: "Backend:"
                                        toolTipText: "Backend used by ViennaCL."
                                        model: [ "OpenCL", "OpenMP", "CUDA" ]
                                        enabled: (comboBoxLibrary.currentText === "ViennaCL")
                                    }

                                    LabeledTextField {
                                        id: inputI
                                        text: "I. Dist.: "
                                        toolTipText: "Path to initial probability distribution CSV file."
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputController.ui_initial_distribution
                                    }

                                    Button{
                                        text: "Search"
                                        onClicked: fileDialog.open()
                                    }


                                    FileDialog {
                                        id: fileDialog
                                        title: "Please choose a csv file"
                                        folder: shortcuts.home
                                        nameFilters: [ "csv files (*.csv *.png)" ]
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
                                value: !outputController.ui_get_not_exec

                            }

                            onClicked: {
                                outputController.ui_stop
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
                                value: outputController.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                    // Set mode in backend.
                                    if(radioButtonAbsorption.checked)
                                        inputController.ui_modelType = "Absorption"
                                    else if (radioButtonFixation.checked)
                                        inputController.ui_modelType = "Fixation"
                                    else if (radioButtonEstablishment.checked)
                                        inputController.ui_modelType = "Establishment"
                                    else if (radioButtonFundamental.checked)
                                        inputController.ui_modelType = "Fundamental"
                                    else if (radioButtonNonAbsorbing.checked)
                                        inputController.ui_modelType = "Non Absorbing"
                                    else if (radioButtonEquilibrium.checked)
                                        inputController.ui_modelType = "Equilibrium"
                                    else if (radioButtonAlleleAge.checked)
                                        inputController.ui_modelType = "Allele Age"

                                    inputController.ui_n = inputN.textFieldText
                                    inputController.ui_a = inputA.textFieldText
                                    if(inputController.ui_modelType == "Fixation" || inputController.ui_modelType == "Absorption" || inputController.ui_modelType == "Establishment" || inputController.ui_modelType == "Allele Age")
                                        inputController.ui_p = inputp.textFieldText
                                    inputController.ui_c = inputc.textFieldText
                                    if(inputController.ui_modelType == "Allele Age")
                                        inputController.ui_x = inputX.textFieldText
                                    if(inputController.ui_modelType == "Establishment")
                                        inputController.ui_k = inputK.textFieldText
                                    inputController.ui_u = inputU.textFieldText
                                    inputController.ui_v = inputV.textFieldText
                                    inputController.ui_m = inputM.checked
                                    inputController.ui_s = inputS.textFieldText
                                    inputController.ui_h = inputH.textFieldText

                                    inputController.ui_output_Q = inputWriteQ.checked
                                    inputController.ui_output_R = inputWriteR.checked
                                    inputController.ui_output_B = inputWriteB.checked
                                    inputController.ui_output_N = inputWriteN.checked
                                    inputController.ui_output_NExt = inputWriteNExt.checked
                                    inputController.ui_output_NFix = inputWriteNFix.checked
                                    inputController.ui_output_I = inputWriteI.checked
                                    inputController.ui_output_E = inputWriteE.checked
                                    inputController.ui_output_V = inputWriteV.checked
                                    inputController.ui_output_Res = inputWriteRes.checked

                                    inputController.ui_force = inputForce.checked
                                    inputController.ui_t = inputT.textFieldText

                                    inputController.ui_initial_distribution = inputI.textFieldText

                                    inputController.ui_library = comboBoxLibrary.currentText;
                                    inputController.ui_solver = comboBoxSolver.currentText;

                                if(outputController.ui_get_error_message == "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    outputController.ui_execute
                                } else {
                                    messageDialog.text = outputController.ui_get_error_message
                                    messageDialog.open()
                                }
                                outputController.ui_reset_error
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
                                id: outputPExt
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P ext. : "
                                toolTipText: "Probability of extintion."
                                textFieldText: outputController.ui_get_p_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputPFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P fix. : "
                                toolTipText: "Probability of fixation."
                                textFieldText: outputController.ui_get_p_fix
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbs
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T abs. : "
                                toolTipText: "Absorption time."
                                textFieldText: outputController.ui_get_t_abs
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbsStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T abs. std.: "
                                toolTipText: "Standard absorption time."
                                textFieldText: outputController.ui_get_t_abs_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputText
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T ext.: "
                                toolTipText: "Extintion time."
                                textFieldText: outputController.ui_get_t_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTextStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T ext. std.: "
                                toolTipText: "Standard extintion time."
                                textFieldText: outputController.ui_get_t_ext_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputNext
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "N ext.: "
                                toolTipText: "Number of generations till extintion."
                                textFieldText: outputController.ui_get_n_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix.: "
                                toolTipText: "Fixation time."
                                textFieldText: outputController.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix. std.: "
                                toolTipText: "Standard fixation time."
                                textFieldText: outputController.ui_get_t_fix_std
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Rate: "
                                toolTipText: "Rate."
                                textFieldText: outputController.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputEFreqMut
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E[freq mut]: "
                                textFieldText: outputController.ui_get_e_freq_mut
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputEFreqWt
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E[freq  wt]: "
                                textFieldText: outputController.ui_get_e_freq_wt
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputFEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "F est.: "
                                textFieldText: outputController.ui_get_f_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputPEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P est.: "
                                textFieldText: outputController.ui_get_p_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSeg
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg.: "
                                textFieldText: outputController.ui_get_t_seg
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. std.: "
                                textFieldText: outputController.ui_get_t_seg_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. ext.: "
                                textFieldText: outputController.ui_get_t_seg_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. ext. std.: "
                                textFieldText: outputController.ui_get_t_seg_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. fix.: "
                                textFieldText: outputController.ui_get_t_seg_fix
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T seg. fix. std.: "
                                textFieldText: outputController.ui_get_t_seg_fix_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T est.: "
                                textFieldText: outputController.ui_get_t_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T est. std.: "
                                textFieldText: outputController.ui_get_t_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputEA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E(A): "
                                textFieldText: outputController.ui_get_e_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            LabeledTextField {
                                id: outputSA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "S(A): "
                                textFieldText: outputController.ui_get_s_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }


                            LabeledTextField {
                                id: outputTime
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Time (s): "
                                toolTipText: "Execution time in seconds."
                                textFieldText: outputController.ui_get_time
                                readOnly: true
                            }

                            LabeledTextField {
                                id: prueba
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Status: "
                                toolTipText: "Status of the current execution."
                                readOnly: true
                                textFieldText: outputController.ui_progress
                            }
                        }
                    }
                }
            }
        }
    }

}
