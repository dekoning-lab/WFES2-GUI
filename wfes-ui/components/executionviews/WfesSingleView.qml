import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0

ApplicationWindow {
    property var firstLoad: true

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

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootWfesSingle.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = "Some input parameters are incorrect. The configuration will be available in this session, but cannot be saved for future sessions until you fix those values. Do you want to exit anyway?"
            messageDialogOnClose.open()

        } else {
            rootWfesSingle.hide();
            root.visible = true;
            rootWfesSingle.updateBackend()
            outputControllerWfesSingle.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: "Warning"
        text: ""
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfesSingle.hide();
            root.visible = true;
        }
    }



    Component.onCompleted: {
        // Center window in screen.
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputN.textFieldText)) && parseInt(inputN.textFieldText) > 1) {
                                        inputControllerWfesSingle.ui_n = inputN.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                    inputU.textFieldTextEdited()
                                    inputV.textFieldTextEdited()
                                    inputX.textFieldTextEdited()
                                    inputp.textFieldTextEdited()
                                }
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSingle.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerWfesSingle.ui_a = inputA.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputp
                                text: "p: "
                                toolTipText: "Starting number of copies."
                                validator: IntValidator {bottom: 0; top: 500000;}
                                textFieldText: inputControllerWfesSingle.ui_p
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputp.textFieldText)) && parseInt(inputp.textFieldText) >= 0 && parseInt(inputp.textFieldText) <= parseInt(inputN.textFieldText)) {
                                        inputControllerWfesSingle.ui_p = inputp.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                                enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                          inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                          inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                          inputControllerWfesSingle.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputc
                                text: "c: "
                                toolTipText: "Integration cutoff."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputc.textFieldText)) && parseFloat(inputc.textFieldText) >= 0) {
                                        inputControllerWfesSingle.ui_c = inputc.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                                textFieldText: inputControllerWfesSingle.ui_c
                            }

                            LabeledTextField {
                                id: inputX
                                text: "x: "
                                toolTipText: "Observed number of copies (allele age only)."
                                validator: IntValidator {bottom: 0; top: 500000;}
                                textFieldText: inputControllerWfesSingle.ui_x
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputX.textFieldText)) && parseInt(inputX.textFieldText) >= 0 && parseInt(inputX.textFieldText) <= parseInt(inputN.textFieldText)) {
                                        inputControllerWfesSingle.ui_x = inputX.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                                enabled: (inputControllerWfesSingle.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputK
                                text: "k: "
                                toolTipText: "Odds ratio (establishment only)."
                                textFieldText: inputControllerWfesSingle.ui_k
                                enabled: (inputControllerWfesSingle.ui_modelType == "Establishment")
                                textFieldTextEdited: function(){
                                    // Odds ratio (k) does not have limits, at least in the code.
                                    if(!Number.isNaN(Number(inputK.textFieldText)) && parseInt(inputK.textFieldText) >= 0) {
                                        inputControllerWfesSingle.ui_k = inputK.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
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
                                text: {
                                    if(globalConfiguration.ui_population_scaled)
                                        return "4Nu: "
                                    else
                                        return "u: "
                                }
                                toolTipText: "Backward mutation rate."
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1) {
                                            inputControllerWfesSingle.ui_u = inputU.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                            inputControllerWfesSingle.ui_u = inputU.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    }
                                }
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSingle.ui_u
                            }

                            LabeledTextField {
                                id: inputV
                                text: {
                                    if(globalConfiguration.ui_population_scaled)
                                        return "4Nv: "
                                    else
                                        return "v: "
                                }
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1) {
                                            inputControllerWfesSingle.ui_v = inputV.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                            inputControllerWfesSingle.ui_v = inputV.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    }
                                }
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
                                text: {
                                    if(globalConfiguration.ui_population_scaled)
                                        return "2Ns: "
                                    else
                                        return "s: "
                                }
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                            inputControllerWfesSingle.ui_s = inputS.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 && parseFloat(inputS.textFieldText) <= 1) {
                                            inputControllerWfesSingle.ui_s = inputS.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    }
                                }
                                toolTipText: "Selection coefficient."
                                // Validator has no sense here, since any range from -2N to 2N is allowed.
                                textFieldText: inputControllerWfesSingle.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: "h: "
                                toolTipText: "Dominance coefficient."
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= 0 && parseFloat(inputH.textFieldText) <= 1) {
                                        inputControllerWfesSingle.ui_h = inputH.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
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
                                    text: "N<sub>ext</sub>: "
                                    checked: inputControllerWfesSingle.ui_output_NExt
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNFix
                                    text: "N<sub>fix</sub>: "
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
                                        textFieldTextEdited: function(){
                                            if(!Number.isNaN(Number(inputT.textFieldText)) && parseInt(inputT.textFieldText) >= 1) {
                                                inputControllerWfesSingle.ui_t = inputT.textFieldText
                                                borderColor = "#555555"
                                            } else {
                                                borderColor = "#ff0000"
                                            }
                                        }
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


                                if(error === "") {
                                    updateBackend();
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
                                text: "P<sub>ext</sub>: "
                                toolTipText: "Probability of extintion."
                                textFieldText: outputControllerWfesSingle.ui_get_p_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputPFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P<sub>fix</sub>: "
                                toolTipText: "Probability of fixation."
                                textFieldText: outputControllerWfesSingle.ui_get_p_fix
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbs
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>abs</sub>: "
                                toolTipText: "Expected number of generations until absorption."
                                textFieldText: outputControllerWfesSingle.ui_get_t_abs
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbsStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>abs std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations until absorption."
                                textFieldText: outputControllerWfesSingle.ui_get_t_abs_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputText
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>ext</sub>: "
                                toolTipText: "Expected number of generations until extinction."
                                textFieldText: outputControllerWfesSingle.ui_get_t_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTextStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>ext std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations until extinction."
                                textFieldText: outputControllerWfesSingle.ui_get_t_ext_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputNext
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "N<sub>ext</sub>: "
                                toolTipText: "Number of generations until extintion."
                                textFieldText: outputControllerWfesSingle.ui_get_n_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>fix</sub>: "
                                toolTipText: "Expected number of generations between two fixation events."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputTFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>fix std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations between two fixation events."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_std
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputTFixAbsMode
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>fix</sub>: "
                                toolTipText: "Expected number of generations until fixation."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_abs_mode
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFixStdAbsMode
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>fix std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations until fixation."
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_std_abs_mode
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Rate: "
                                toolTipText: "Rate of substitution."
                                textFieldText: outputControllerWfesSingle.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputEFreqMut
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E[freq mut]: "
                                toolTipText: "Expected frequency."
                                textFieldText: outputControllerWfesSingle.ui_get_e_freq_mut
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputEFreqWt
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E[freq  wt]: "
                                toolTipText: "One minus expected frequency."
                                textFieldText: outputControllerWfesSingle.ui_get_e_freq_wt
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputFEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "F<sub>est</sub>: "
                                toolTipText: "Frequency of establishment."
                                textFieldText: outputControllerWfesSingle.ui_get_f_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputPEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "P<sub>est</sub>: "
                                toolTipText: "Probability of establishment."
                                textFieldText: outputControllerWfesSingle.ui_get_p_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSeg
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>seg</sub>: "
                                toolTipText: "Expected number of generations until segregation."
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>seg std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations until segregation."
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>seg ext</sub>: "
                                toolTipText: "Expected number of generations until segregation (Extinction)."
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>seg ext std<sub>: "
                                toolTipText: "Standard deviation of expected number of generations until segregation (Extinction)."
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>seg fix</sub>: "
                                toolTipText: "Expected number of generations until segregation (Fixation)."
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_fix
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>seg fix std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations until segregation (Fixation)."
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_fix_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>est</sub>: "
                                toolTipText: "Expected number of generations until establishment."
                                textFieldText: outputControllerWfesSingle.ui_get_t_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>est std</sub>: "
                                toolTipText: "Standard deviation of expected number of generations until establishment."
                                textFieldText: outputControllerWfesSingle.ui_get_t_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputEA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "E(A): "
                                toolTipText: "Expectation of the allele age."
                                textFieldText: outputControllerWfesSingle.ui_get_e_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            LabeledTextField {
                                id: outputSA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "S(A): "
                                toolTipText: "Standard deviation of the allele age."
                                textFieldText: outputControllerWfesSingle.ui_get_s_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            Button {
                                text: "Copy to Clipboard"

                                visible: {
                                    !radioButtonNonAbsorbing.checked && !radioButtonFundamental.checked
                                }

                                Layout.alignment: Qt.AlignHCenter

                                onClicked: {
                                    outputControllerWfesSingle.coppyToClipboard()
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

        if(inputN.textFieldText == "")
            error += " - Population Size (N) is empty. \n \n"
        if(Number.isNaN(Number(inputN.textFieldText)))
            error += " - Population Size (N) is not a valid number. \n \n"
        if(parseInt(inputN.textFieldText) < 2)
            error += " - Population Size (N) is quite small, it must be at least 2. \n \n"
        if(!inputForce.checked && parseInt(inputN.textFieldText) > 50000)
            error += " - Population Size (N) is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"

        if(inputA.textFieldText == "")
            error += " - Tail Truncation Cutoff (a) is empty. \n \n"
        if(Number.isNaN(Number(inputA.textFieldText)))
            error += " - Tail Truncation Cutoff (a) is not a valid number. \n \n"
        if(parseFloat(inputA.textFieldText) < 0)
            error += " - Tail Truncation Cutoff (a) is quite small. It must be at least 0. \n \n"
        if(!inputForce.checked && parseFloat(inputA.textFieldText) > 1e-5)
            error += " - Tail Truncation Cutoff (a) value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore. \n \n"

        if(inputp.textFieldText == "")
            error += " - Starting copies (p) is empty. \n \n"
        if(Number.isNaN(Number(inputp.textFieldText)))
            error += " - Starting copies (p) is not a valid number. \n \n"
        if(parseInt(inputp.textFieldText) < 0)
            error += " - Starting copies (p) is quite small, if you want to disable it just use 0. \n \n"
        if(parseInt(inputp.textFieldText) > parseInt(inputN.textFieldText))
            error += " - Starting Copies (p) is quite large. The maximum value allowed is N. \n \n"

        if(inputc.textFieldText == "")
            error += " - Integration Cutoff (c) is empty. \n \n"
        if(Number.isNaN(Number(inputc.textFieldText)))
            error += " - Integration Cutoff (c) is not a valid number. \n \n"
        if(parseFloat(inputc.textFieldText) < 0)
            error += " - Integration Cutoff (c) is quite small. It must be at least 0. \n \n"
        if(parseFloat(inputc.textFieldText) > 10e-3)
            error += " - Integration Cutoff (c) is quite large. The maximum value allowed is 10e-3. \n \n"

        if(inputX.textFieldText == "")
            error += " - Observed copies (x) is empty. \n \n"
        if(Number.isNaN(Number(inputX.textFieldText)))
            error += " - Observed copies (x) is not a valid number. \n \n"
        if(parseInt(inputX.textFieldText) < 1)
            error += " - Observed copies (x) is quite small. It must be at least 1. \n \n"
        if(parseInt(inputX.textFieldText) > parseInt(inputN.textFieldText))
            error += " - Observed Copies (x) is quite large. The maximum value allowed is N. \n \n"

        // Odds ratio (k) does not have limits, at least in the code. The default value is 1.
        if(inputK.textFieldText == "")
            error += " - Odds ratio (k) is empty. \n \n"
        if(Number.isNaN(Number(inputK.textFieldText)))
            error += " - Odds ratio (k) is not a valid number. \n \n"

        if(globalConfiguration.ui_population_scaled) {
            if(inputU.textFieldText == "")
                error += " - Backward Mutation (u) is empty. \n \n"
            if(Number.isNaN(Number(inputU.textFieldText)))
                error += " - Backward Mutation (u) is not a valid number. \n \n"
            if(parseFloat(inputU.textFieldText) <= 0)
                error += " - Backward Mutation (u) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && parseFloat(inputU.textFieldText) > 1)
                error += " - Backward Mutation (u) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore. \n \n"

            if(inputV.textFieldText == "")
                error += " - Forward Mutation (v) is empty. \n \n"
            if(Number.isNaN(Number(inputV.textFieldText)))
                error += " - Forward Mutation (v) is not a valid number. \n \n"
            if(parseFloat(inputV.textFieldText) <= 0)
                error += " - Forward Mutation (v) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && parseFloat(inputV.textFieldText) > 1)
                error += " - Forward Mutation (v) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore. \n \n"

            if(inputS.textFieldText == "")
                error += " - Selection Coefficient (s) is empty. \n \n"
            if(Number.isNaN(Number(inputS.textFieldText)))
                error += " - Selection Coefficient (s) is not a valid number. \n \n"
            if(parseFloat(inputS.textFieldText) < -1 * (2 * parseInt(inputN.textFieldText)))
                error += " - Selection Coefficient (s) is quite small. It must be at least -2N. \n \n"
            if(parseFloat(inputS.textFieldText) > 1 * (2 * parseInt(inputN.textFieldText)))
                error += " - Selection Coefficient (s) is quite large. The maximum value allowed is 2N. \n \n"
        } else {
            if(inputU.textFieldText == "")
                error += " - Backward Mutation (u) is empty. \n \n"
            if(Number.isNaN(Number(inputU.textFieldText)))
                error += " - Backward Mutation (u) is not a valid number. \n \n"
            if(parseFloat(inputU.textFieldText) <= 0)
                error += " - Backward Mutation (u) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && parseFloat(inputU.textFieldText) > 1 / (4 * parseInt(inputN.textFieldText)))
                error += " - Backward Mutation (u) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore. \n \n"

            if(inputV.textFieldText == "")
                error += " - Forward Mutation (v) is empty. \n \n"
            if(Number.isNaN(Number(inputV.textFieldText)))
                error += " - Forward Mutation (v) is not a valid number. \n \n"
            if(parseFloat(inputV.textFieldText) <= 0)
                error += " - Forward Mutation (v) is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && parseFloat(inputV.textFieldText) > 1 / (4 * parseInt(inputN.textFieldText)))
                error += " - Forward Mutation (v) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore. \n \n"

            if(inputS.textFieldText == "")
                error += " - Selection Coefficient (s) is empty. \n \n"
            if(Number.isNaN(Number(inputS.textFieldText)))
                error += " - Selection Coefficient (s) is not a valid number. \n \n"
            if(parseFloat(inputS.textFieldText) < -1)
                error += " - Selection Coefficient (s) is quite small. It must be at least -1. \n \n"
            if(parseFloat(inputS.textFieldText) > 1)
                error += " - Selection Coefficient (s) is quite large. The maximum value allowed is 1. \n \n"
        }

        if(inputH.textFieldText == "")
            error += " - Dominance Coefficient (h) is empty. \n \n"
        if(Number.isNaN(Number(inputH.textFieldText)))
            error += " - Dominance Coefficient (h) is not a valid number. \n \n"
        if(parseFloat(inputH.textFieldText) < 0)
            error += " - Dominance Coefficient (h) is quite small. It must be at least 0. \n \n"
        if(parseFloat(inputH.textFieldText) > 1)
            error += " - Dominance Coefficient (h) is quite large. The maximum value allowed is 1. \n \n"

        if(inputT.textFieldText == "")
            error += " - Number of Threads (t) is empty. \n \n"
        if(Number.isNaN(Number(inputT.textFieldText)))
            error += " - Number of Threads (t) is not a valid number. \n \n"
        // Number of threads (t) does not have upper limites, since it depends on the hardware available.
        if(parseInt(inputT.textFieldText) < 1)
            error += " - Number of Threads (t) is quite small, it must be at least 1. \n \n"

        //TODO Check if Initial Distribution (I) file exists.

        return error.split("\n \n")[0];
    }


    function updateScaledParameters(updateNonChecked) {
        if(globalConfiguration.ui_population_scaled) {
            inputControllerWfesSingle.ui_s = parseFloat(inputControllerWfesSingle.ui_s) * (2 * parseInt(inputControllerWfesSingle.ui_n))
            inputS.textFieldText = inputControllerWfesSingle.ui_s
            inputControllerWfesSingle.ui_u = parseFloat(inputControllerWfesSingle.ui_u) * (4 * parseInt(inputControllerWfesSingle.ui_n))
            inputU.textFieldText = inputControllerWfesSingle.ui_u
            inputControllerWfesSingle.ui_v = parseFloat(inputControllerWfesSingle.ui_v) * (4 * parseInt(inputControllerWfesSingle.ui_n))
            inputV.textFieldText = inputControllerWfesSingle.ui_v
        } else if(updateNonChecked){
            inputControllerWfesSingle.ui_s = parseFloat(inputControllerWfesSingle.ui_s) / (2 * parseInt(inputControllerWfesSingle.ui_n))
            inputS.textFieldText = inputControllerWfesSingle.ui_s
            inputControllerWfesSingle.ui_u = parseFloat(inputControllerWfesSingle.ui_u) / (4 * parseInt(inputControllerWfesSingle.ui_n))
            inputU.textFieldText = inputControllerWfesSingle.ui_u
            inputControllerWfesSingle.ui_v = parseFloat(inputControllerWfesSingle.ui_v) / (4 * parseInt(inputControllerWfesSingle.ui_n))
            inputV.textFieldText = inputControllerWfesSingle.ui_v
        }
    }
}
