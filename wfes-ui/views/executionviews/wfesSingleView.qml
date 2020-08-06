import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0


ApplicationWindow {
    id: root
    title: qsTr("WFES - Wright-Fisher Exact Solver (wfes_single)")

    color: Universal.chromeLowColor

    visible: true

    width: 920
    minimumWidth: 920
    height: 540
    minimumHeight: 540
    maximumWidth: 920
    maximumHeight: 540

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
                                }
                            }
                            RadioButton {
                                id: radioButtonFixation
                                text: qsTr("Fixation")
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
                                }
                            }

                            RadioButton {
                                id: radioButtonEstablishment
                                text: qsTr("Establishment")
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
                                }
                            }
                            RadioButton {
                                id: radioButtonFundamental
                                text: qsTr("Fundamental")
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
                                }
                            }
                            RadioButton {
                                id: radioButtonNonAbsorbing
                                text: qsTr("Non Absorbing")
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
                                }
                            }

                            RadioButton {
                                id: radioButtonEquilibrium
                                text: qsTr("Equilibrium")
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
                                }
                            }
                            RadioButton {
                                id: radioButtonAlleleAge
                                text: qsTr("Allele Age")
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
                                text: "N: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputController.ui_n
                                fun: function(){inputController.ui_n = textFieldText;}
                            }

                            LabeledTextField {
                                text: "a: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_a
                                fun: function(){inputController.ui_a = textFieldText;}
                            }

                            LabeledTextField {
                                text: "p: "
                                //TODO Top is N
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_p
                                fun: function(){inputController.ui_p = textFieldText;}
                            }

                            LabeledTextField {
                                text: "c: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_c
                                fun: function(){inputController.ui_c = textFieldText;}
                            }

                            LabeledTextField {
                                text: "x: "
                                //TODO Top is N
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_x
                                fun: function(){inputController.ui_x = textFieldText;}
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
                                text: "u: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputController.ui_u
                                fun: function(){inputController.ui_u = textFieldText;}
                            }

                            LabeledTextField {
                                text: "v: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_v
                                fun: function(){inputController.ui_v = textFieldText;}
                            }

                            LabeledCheckBox {
                                text: "m: "
                                checked: inputController.ui_m
                                fun: function(){inputController.ui_m = checked}
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
                                text: "s: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputController.ui_s
                                fun: function(){inputController.ui_s = textFieldText;}
                            }

                            LabeledTextField {
                                text: "h: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputController.ui_h
                                fun: function(){inputController.ui_h = textFieldText;}
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
                                    text: "Q: "
                                    checked: inputController.ui_output_Q
                                    fun: function(){inputController.ui_output_Q = checked}

                                }

                                LabeledCheckBox {
                                    text: "R: "
                                    checked: inputController.ui_output_R
                                    fun: function(){inputController.ui_output_R = checked}
                                }

                                LabeledCheckBox {
                                    text: "N: "
                                    checked: inputController.ui_output_N
                                    fun: function(){inputController.ui_output_N = checked}
                                }

                                LabeledCheckBox {
                                    text: "B: "
                                    checked: inputController.ui_output_B
                                    fun: function(){inputController.ui_output_B = checked}
                                }

                                LabeledCheckBox {
                                    text: "I: "
                                    checked: inputController.ui_output_I
                                    fun: function(){inputController.ui_output_I = checked}
                                }

                                LabeledCheckBox {
                                    text: "E: "
                                    checked: inputController.ui_output_E
                                    fun: function(){inputController.ui_output_E = checked}
                                }

                                LabeledCheckBox {
                                    text: "V: "
                                    checked: inputController.ui_output_V
                                    fun: function(){inputController.ui_output_V = checked}
                                }


                                LabeledCheckBox {
                                    text: "Res: "
                                    checked: inputController.ui_output_Res
                                    fun: function(){inputController.ui_output_Res = checked}
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
                                        text: "Force: "
                                        checked: inputController.ui_force
                                        fun: function(){inputController.ui_force = checked}
                                    }

                                    LabeledTextField {
                                        text: "t: "
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputController.ui_t
                                        fun: function(){inputController.ui_t = textFieldText;}
                                    }
                                }

                                ColumnLayout {
                                    width: childrenRect.width

                                    LabeledComboBox {
                                        text: "Solver:"
                                        model: [ "ViennaCL", "Pardiso" ]
                                    }

                                    LabeledComboBox {
                                        text: "Backend:"
                                        model: [ "1 Threaded", "OpenMP", "OpenCL", "CUDA" ]
                                    }
                                }

                            }
                        }

                    }

                    Button {
                        Layout.margins: 10
                        Layout.alignment: Qt.AlignRight
                        text: "Execute"
                        onClicked: outputController.ui_execute
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
                        }

                        ColumnLayout {

                            anchors {
                                top: labelFinalOutput.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: outputPExt
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "P. ext. : "
                                textFieldText: outputController.ui_get_p_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputPFix
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "P. fix. : "
                                textFieldText: outputController.ui_get_p_fix
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbs
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. abs. : "
                                textFieldText: outputController.ui_get_t_abs
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbsStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. abs. std.: "
                                textFieldText: outputController.ui_get_t_abs_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputText
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. ext.: "
                                textFieldText: outputController.ui_get_t_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTextStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. ext. std.: "
                                textFieldText: outputController.ui_get_t_ext_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputNext
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "N. ext.: "
                                textFieldText: outputController.ui_get_n_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFix
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. fix.: "
                                textFieldText: outputController.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFixStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. fix. std.: "
                                textFieldText: outputController.ui_get_t_fix_std
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "Rate: "
                                //TODO
                                textFieldText: outputController.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputEFreqMut
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "E[freq mut]: "
                                //TODO
                                textFieldText: outputController.ui_get_e_freq_mut
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputEFreqWt
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "E[freq  wt]: "
                                //TODO
                                textFieldText: outputController.ui_get_e_freq_wt
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputFEst
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "F. est.: "
                                //TODO
                                textFieldText: outputController.ui_get_f_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputPEst
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "P. est.: "
                                //TODO
                                textFieldText: outputController.ui_get_p_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSeg
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. seg.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_seg
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. seg. std.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_seg_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEst
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. seg. ext.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_seg_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEstStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. seg. ext. std.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_seg_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFix
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. seg. fix.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_seg_fix
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFixStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. seg. fix. std.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_seg_fix_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEst
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. est.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEstStd
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "T. est. std.: "
                                //TODO
                                textFieldText: outputController.ui_get_t_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputEA
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "E(A): "
                                //TODO
                                textFieldText: outputController.ui_get_e_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            LabeledTextField {
                                id: outputSA
                                labelPreferredWidth: 75
                                textFieldPreferredWidth: 180
                                text: "S(A): "
                                //TODO
                                textFieldText: outputController.ui_get_s_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }
                        }
                    }
                }
            }
        }
    }

}
