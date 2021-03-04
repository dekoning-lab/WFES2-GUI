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
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.wfesSingle + ")"

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
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
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
        title: Strings.dialogWarning
        text: Strings.empty
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
        title: Strings.dialogWarning
        text: Strings.empty
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
                            text: Strings.mode + Strings.colon
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
                                text: Strings.wfesSingleAbsorption

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleAbsorptionTooltip

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

                                    inputWriteN.checked = inputControllerWfesSingle.ui_output_N
                                    inputWriteN.enabledCheckBox = checked
                                    inputWriteE.enabledCheckBox = !checked
                                    inputp.textFieldTextEdited()
                                }
                            }
                            RadioButton {
                                id: radioButtonFixation
                                checked: inputControllerWfesSingle.ui_modelType === "Fixation"
                                text: Strings.wfesSingleFixation

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleFixationTooltip

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

                                    inputWriteN.checked = inputControllerWfesSingle.ui_output_N
                                    inputWriteN.enabledCheckBox = checked
                                    inputWriteE.enabledCheckBox = !checked
                                    inputp.textFieldTextEdited()
                                }
                            }

                            RadioButton {
                                id: radioButtonEstablishment
                                checked: inputControllerWfesSingle.ui_modelType === "Establishment"
                                text: Strings.wfesSingleEstablishment

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleEstablishmentTooltip

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

                                    inputWriteN.checked = inputControllerWfesSingle.ui_output_N
                                    inputWriteN.enabledCheckBox = !checked
                                    inputWriteE.enabledCheckBox = !checked
                                    inputp.textFieldTextEdited()
                                }
                            }
                            RadioButton {
                                id: radioButtonFundamental
                                checked: inputControllerWfesSingle.ui_modelType === "Fundamental"
                                text: Strings.wfesSingleFundamental

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleFundamentalTooltip

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

                                    inputWriteN.checked = true
                                    inputWriteN.enabledCheckBox = false
                                    inputWriteE.enabledCheckBox = !checked
                                    inputp.textFieldTextEdited()
                                }
                            }
                            RadioButton {
                                id: radioButtonNonAbsorbing
                                checked: inputControllerWfesSingle.ui_modelType === "Non Absorbing"
                                text: Strings.wfesSingleNonAbsorbing

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleNonAbsorbingTooltip

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

                                    inputWriteN.checked = inputControllerWfesSingle.ui_output_N
                                    inputWriteN.enabledCheckBox = !checked
                                    inputWriteE.enabledCheckBox = !checked
                                    inputp.textFieldTextEdited()
                                }
                            }

                            RadioButton {
                                id: radioButtonEquilibrium
                                checked: inputControllerWfesSingle.ui_modelType === "Equilibrium"
                                text: Strings.wfesSingleEquilibrium

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleEquilibriumTooltip

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

                                    inputWriteN.checked = inputControllerWfesSingle.ui_output_N
                                    inputWriteN.enabledCheckBox = !checked
                                    inputWriteE.enabledCheckBox = false
                                    inputp.textFieldTextEdited()
                                }
                            }
                            RadioButton {
                                id: radioButtonAlleleAge
                                checked: inputControllerWfesSingle.ui_modelType === "Allele Age"
                                text: Strings.wfesSingleAlleleAge

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSingleAlleleAgeTooltip

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

                                    inputWriteN.checked = inputControllerWfesSingle.ui_output_N
                                    inputWriteN.enabledCheckBox = !checked
                                    inputWriteE.enabledCheckBox = !checked
                                    inputp.textFieldTextEdited()
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
                            text: Strings.population + Strings.colon
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
                                text: Strings.n + Strings.colon
                                toolTipText: Strings.nTooltip
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
                                text: Strings.a + Strings.colon
                                toolTipText: Strings.aTooltip
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
                                text: Strings.p + Strings.colon
                                toolTipText: Strings.pTooltip
                                validator: IntValidator {bottom: 0; top: 500000;}
                                textFieldText: inputControllerWfesSingle.ui_p
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputp.textFieldText)) && parseInt(inputp.textFieldText) >= 0) {
                                        inputControllerWfesSingle.ui_p = inputp.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        print(parseInt(inputp.textFieldText) >= 0)
                                        borderColor = "#ff0000"
                                    }

                                    //Maximum value for Starting copies (p) depends on the executable used.
                                    if(radioButtonAbsorption.checked) {
                                        if(!Number.isNaN(Number(inputp.textFieldText)) && parseInt(inputp.textFieldText) >= (2 * parseInt(inputN.textFieldText)) - 1) {
                                            borderColor = "#ff0000"
                                        }
                                    } else if(radioButtonFixation.checked) {
                                        if(!Number.isNaN(Number(inputp.textFieldText)) && parseInt(inputp.textFieldText) >= (2 * parseInt(inputN.textFieldText))) {
                                            borderColor = "#ff0000"
                                        }
                                    } else if(radioButtonEstablishment.checked) {
                                        if(!Number.isNaN(Number(inputp.textFieldText)) && parseInt(inputp.textFieldText) >= (parseInt(inputN.textFieldText)) - 1) {
                                            borderColor = "#ff0000"
                                        }
                                    } else if(radioButtonAlleleAge.checked) {
                                        if(!Number.isNaN(Number(inputp.textFieldText)) && parseInt(inputp.textFieldText) >= (2 * parseInt(inputN.textFieldText)) - 1) {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        borderColor = "#555555"
                                    }

                                }
                                enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                          inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                          inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                          inputControllerWfesSingle.ui_modelType == "Allele Age")
                            }

                            LabeledTextField {
                                id: inputc
                                text: Strings.c + Strings.colon
                                toolTipText: Strings.cTooltip
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
                                text: Strings.xObserved + Strings.colon
                                toolTipText: Strings.xObservedTooltip
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
                                text: Strings.kOdds + Strings.colon
                                toolTipText: Strings.kOddsTooltip
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
                            text: Strings.mutation + Strings.colon
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
                                        return Strings.uScaled + Strings.colon
                                    else
                                        return Strings.u + Strings.colon
                                }
                                toolTipText: Strings.uTooltip
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
                                        return Strings.vScaled + Strings.colon
                                    else
                                        return Strings.v + Strings.colon
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
                                toolTipText: Strings.vTooltip
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSingle.ui_v
                            }

                            LabeledCheckBox {
                                id: inputM
                                text: Strings.mMut + Strings.colon
                                toolTipText: Strings.mMutTooltip
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
                            text: Strings.selection + Strings.colon
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
                                        return Strings.sScaled + Strings.colon
                                    else
                                        return Strings.s + Strings.colon
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
                                toolTipText: Strings.sTooltip
                                // Validator has no sense here, since any range from -2N to 2N is allowed.
                                textFieldText: inputControllerWfesSingle.ui_s
                            }

                            LabeledTextField {
                                id: inputH
                                text: Strings.h + Strings.colon
                                toolTipText: Strings.hTooltip
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
                                text: Strings.outputOptions + Strings.colon
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
                                    text: Strings.outputQ + Strings.colon
                                    toolTipText: Strings.outputQTooltip
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
                                    text: Strings.outputR + Strings.colon
                                    toolTipText: Strings.outputRTooltip
                                    checked: inputControllerWfesSingle.ui_output_R
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                              inputControllerWfesSingle.ui_modelType == "Fundamental" ||
                                              inputControllerWfesSingle.ui_modelType == "Establishment" ||
                                              inputControllerWfesSingle.ui_modelType == "Allele Age")
                                }

                                LabeledCheckBox {
                                    id: inputWriteB
                                    text: Strings.outputB + Strings.colon
                                    toolTipText: Strings.outputBTooltip
                                    checked: inputControllerWfesSingle.ui_output_B
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteN
                                    text: Strings.outputN + Strings.colon
                                    toolTipText: Strings.outputNTooltip
                                    checked: inputControllerWfesSingle.ui_output_N
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fixation" ||
                                              inputControllerWfesSingle.ui_modelType == "Absorption" ||
                                              inputControllerWfesSingle.ui_modelType == "Fundamental")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNExt
                                    text: Strings.outputNExt + Strings.colon
                                    toolTipText: Strings.outputNExtTooltip
                                    checked: inputControllerWfesSingle.ui_output_NExt
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteNFix
                                    text: Strings.outputNFix + Strings.colon
                                    toolTipText: Strings.outputNFixTooltip
                                    checked: inputControllerWfesSingle.ui_output_NFix
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Absorption")
                                }

                                LabeledCheckBox {
                                    id: inputWriteI
                                    text: Strings.outputI + Strings.colon
                                    toolTipText: Strings.outputITooltip
                                    checked: inputControllerWfesSingle.ui_output_I
                                }

                                LabeledCheckBox {
                                    id: inputWriteE
                                    text: Strings.outputE + Strings.colon
                                    toolTipText: Strings.outputNExtTooltip
                                    checked: inputControllerWfesSingle.ui_output_E
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Equilibrium")
                                }

                                LabeledCheckBox {
                                    id: inputWriteV
                                    text: Strings.outputV + Strings.colon
                                    toolTipText: Strings.outputVTooltip
                                    checked: inputControllerWfesSingle.ui_output_V
                                    enabled: (inputControllerWfesSingle.ui_modelType == "Fundamental")
                                }


                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: Strings.outputRes + Strings.colon
                                    toolTipText: Strings.outputResTooltip
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
                                text: Strings.execution + Strings.colon
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
                                        text: Strings.force + Strings.colon
                                        toolTipText: Strings.forceTooltip
                                        checked: inputControllerWfesSingle.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: Strings.t + Strings.colon
                                        toolTipText: Strings.tTooltip
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
                                        text: Strings.library + Strings.colon
                                        model: ["Pardiso", "ViennaCL"]
                                        toolTipText: Strings.libraryTooltip
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
                                        text: Strings.solver + Strings.colon
                                        toolTipText: Strings.solverTooltip
                                        model: ["GMRes", "BicGStab"]
                                        enabled: (comboBoxLibrary.currentText === "ViennaCL")
                                    }

                                    LabeledTextField {
                                        id: inputI
                                        text: Strings.iDist + Strings.colon
                                        toolTipText: Strings.iDistTooltip
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputControllerWfesSingle.ui_initial_distribution
                                    }

                                    Button{
                                        text: Strings.searchButton
                                        onClicked: fileDialog.open()
                                    }


                                    FileDialog {
                                        id: fileDialog
                                        title: Strings.iDistDialogTitle
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
                            text: Strings.stopButton

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
                            text: Strings.executeButton

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
                                if(inputControllerWfesSingle.ui_modelType == "Equilibrium") {
                                    upperMenu.updateWfesSingleEquilibrium()
                                    if(enabled) {
                                        upperMenu.chartVisible = true
                                    }
                                } else if (inputControllerWfesSingle.ui_modelType == "Fundamental") {
                                    if(globalConfiguration.ui_generate_images) {
                                        if(enabled) {
                                            upperMenu.matrixVisible = true
                                        }
                                    }
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
                            text: Strings.output + Strings.colon
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
                                text: Strings.pExt + Strings.colon
                                toolTipText: Strings.pExtTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_p_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputPFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.pFix + Strings.colon
                                toolTipText: Strings.pFixTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_p_fix
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbs
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tAbs + Strings.colon
                                toolTipText: Strings.tAbsTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_abs
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTAbsStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tAbsStd + Strings.colon
                                toolTipText: Strings.tAbsStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_abs_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputText
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tExt + Strings.colon
                                toolTipText: Strings.tExtTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTextStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tExtStd + Strings.colon
                                toolTipText: Strings.tExtStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_ext_std
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputNext
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.nExt + Strings.colon
                                toolTipText: Strings.nExtTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_n_ext
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tFix + Strings.colon
                                toolTipText: Strings.tFixTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputTFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tFixStd + Strings.colon
                                toolTipText: Strings.tFixStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_std
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputTFixAbsMode
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tFix + Strings.colon
                                toolTipText: Strings.tFixTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_abs_mode
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputTFixStdAbsMode
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tFixStd + Strings.colon
                                toolTipText: Strings.tFixStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_fix_std_abs_mode
                                readOnly: true
                                visible: radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.rate + Strings.colon
                                toolTipText: Strings.rateTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }

                            LabeledTextField {
                                id: outputEFreqMut
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.eFreqMut + Strings.colon
                                toolTipText: Strings.eFreqMutTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_e_freq_mut
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputEFreqWt
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.eFreqWt + Strings.colon
                                toolTipText: Strings.eFreqWtTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_e_freq_wt
                                readOnly: true
                                visible: radioButtonEquilibrium.checked
                            }

                            LabeledTextField {
                                id: outputFEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.fEst + Strings.colon
                                toolTipText: Strings.fEstTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_f_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputPEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.pEst + Strings.colon
                                toolTipText: Strings.pEstTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_p_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSeg
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tSeg + Strings.colon
                                toolTipText: Strings.tSegTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tSegStd + Strings.colon
                                toolTipText: Strings.tSegStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tSegExt + Strings.colon
                                toolTipText: Strings.tSegExtTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tSegExtStd + Strings.colon
                                toolTipText: Strings.tSegExtStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tSegFix + Strings.colon
                                toolTipText: Strings.tSegFixTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_fix
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTSegFixStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tSegFixStd + Strings.colon
                                toolTipText: Strings.tSegFixStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_seg_fix_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEst
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tEst + Strings.colon
                                toolTipText: Strings.tEstTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_est
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputTEstStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tEstStd + Strings.colon
                                toolTipText: Strings.tEstStdTooltip
                                textFieldText: outputControllerWfesSingle.ui_get_t_est_std
                                readOnly: true
                                visible: radioButtonEstablishment.checked
                            }

                            LabeledTextField {
                                id: outputEA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.eA + Strings.colon
                                toolTipText: Strings.eATooltip
                                textFieldText: outputControllerWfesSingle.ui_get_e_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            LabeledTextField {
                                id: outputSA
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.sA + Strings.colon
                                toolTipText: Strings.sATooltip
                                textFieldText: outputControllerWfesSingle.ui_get_s_a
                                readOnly: true
                                visible: radioButtonAlleleAge.checked
                            }

                            Button {
                                text: Strings.copyToClipboard

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

        // Update boxes.
        inputN.textFieldTextEdited()
        inputA.textFieldTextEdited()
        inputp.textFieldTextEdited()
        inputc.textFieldTextEdited()
        inputX.textFieldTextEdited()
        inputK.textFieldTextEdited()
        inputU.textFieldTextEdited()
        inputV.textFieldTextEdited()
        inputS.textFieldTextEdited()
        inputH.textFieldTextEdited()
        inputT.textFieldTextEdited()

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
            error += Strings.hyphen + Strings.nIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputN.textFieldText)))
            error += Strings.hyphen + Strings.nIsNotValid + Strings.endOfError
        if(parseInt(inputN.textFieldText) < 2)
            error += Strings.hyphen + Strings.nIsSmall + Strings.endOfError
        if(!inputForce.checked && parseInt(inputN.textFieldText) > 50000)
            error += Strings.hyphen + Strings.nIsLarge + Strings.endOfError

        if(inputA.textFieldText == "")
            error += Strings.hyphen + Strings.aIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputA.textFieldText)))
            error += Strings.hyphen + Strings.aIsNotValid + Strings.endOfError
        if(parseFloat(inputA.textFieldText) < 0)
            error += Strings.hyphen + Strings.aIsSmall + Strings.endOfError
        if(!inputForce.checked && parseFloat(inputA.textFieldText) > 1e-5)
            error += Strings.hyphen + Strings.aIsLarge + Strings.endOfError

        if(inputp.textFieldText == "")
            error += Strings.hyphen + Strings.pStartIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputp.textFieldText)))
            error += Strings.hyphen + Strings.pStartIsNotValid + Strings.endOfError
        if(parseInt(inputp.textFieldText) < 0)
            error += Strings.hyphen + Strings.pStartIsSmall + Strings.endOfError

        //Maximum value for Starting copies (p) depends on the executable used.
        if(radioButtonAbsorption.checked) {
            if(parseInt(inputp.textFieldText) > (2 * parseInt(inputN.textFieldText)) - 2)
                error += Strings.hyphen + Strings.pStartIsLargeAbsorption + Strings.endOfError
        } else if(radioButtonFixation.checked) {
            if(parseInt(inputp.textFieldText) > (2 * parseInt(inputN.textFieldText)) -1)
                error += Strings.hyphen + Strings.pStartIsLargeFixation + Strings.endOfError
        }else if(radioButtonEstablishment.checked) {
            if(parseInt(inputp.textFieldText) > (parseInt(inputN.textFieldText)) - 2)
                error += Strings.hyphen + Strings.pStartIsLargeEstablishment + Strings.endOfError
        } else if(radioButtonAlleleAge.checked) {
            if(parseInt(inputp.textFieldText) > (2 * parseInt(inputN.textFieldText)) - 2)
                error += Strings.hyphen + Strings.pStartIsLargeAlleleAge + Strings.endOfError
        }

        if(inputc.textFieldText == "")
            error += Strings.hyphen + Strings.cIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputc.textFieldText)))
            error += Strings.hyphen + Strings.cIsNotValid + Strings.endOfError
        if(parseFloat(inputc.textFieldText) < 0)
            error += Strings.hyphen + Strings.cIsSmall + Strings.endOfError
        if(parseFloat(inputc.textFieldText) > 10e-3)
            error += Strings.hyphen + Strings.cIsLarge + Strings.endOfError

        if(inputX.textFieldText == "")
            error += Strings.hyphen + Strings.xIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputX.textFieldText)))
            error += Strings.hyphen + Strings.xIsNotValid + Strings.endOfError
        if(parseInt(inputX.textFieldText) < 1)
            error += Strings.hyphen + Strings.xIsSmall + Strings.endOfError
        if(parseInt(inputX.textFieldText) > parseInt(inputN.textFieldText))
            error += Strings.hyphen + Strings.xIsLarge + Strings.endOfError

        // Odds ratio (k) does not have limits, at least in the code. The default value is 1.
        if(inputK.textFieldText == "")
            error += Strings.hyphen + Strings.kOddsIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputK.textFieldText)))
            error += Strings.hyphen + Strings.kOddsIsNotValid + Strings.endOfError

        if(globalConfiguration.ui_population_scaled) {
            if(inputU.textFieldText == "")
                error += Strings.hyphen + Strings.uIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputU.textFieldText)))
                error += Strings.hyphen + Strings.uIsNotValid + Strings.endOfError
            if(parseFloat(inputU.textFieldText) <= 0)
                error += Strings.hyphen + Strings.uIsSmall + Strings.endOfError
            if(!inputForce.checked && parseFloat(inputU.textFieldText) > 1)
                error += Strings.hyphen + Strings.uIsLargeScaled + Strings.endOfError

            if(inputV.textFieldText == "")
                error += Strings.hyphen + Strings.uIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputV.textFieldText)))
                error += Strings.hyphen + Strings.vIsNotValid + Strings.endOfError
            if(parseFloat(inputV.textFieldText) <= 0)
                error += Strings.hyphen + Strings.vIsSmall + Strings.endOfError
            if(!inputForce.checked && parseFloat(inputV.textFieldText) > 1)
                error += Strings.hyphen + Strings.vIsLargeScaled + Strings.endOfError

            if(inputS.textFieldText == "")
                error += Strings.hyphen + Strings.sIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputS.textFieldText)))
                error += Strings.hyphen + Strings.sIsNotValid + Strings.endOfError
            if(parseFloat(inputS.textFieldText) < -1 * (2 * parseInt(inputN.textFieldText)))
                error += Strings.hyphen + Strings.sIsSmall + Strings.endOfError
            if(parseFloat(inputS.textFieldText) > 1 * (2 * parseInt(inputN.textFieldText)))
                error += Strings.hyphen + Strings.sIsLargeScaled + Strings.endOfError
        } else {
            if(inputU.textFieldText == "")
                error += Strings.hyphen + Strings.uIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputU.textFieldText)))
                error += Strings.hyphen + Strings.uIsNotValid + Strings.endOfError
            if(parseFloat(inputU.textFieldText) <= 0)
                error += Strings.hyphen + Strings.uIsSmall + Strings.endOfError
            if(!inputForce.checked && parseFloat(inputU.textFieldText) > 1 / (4 * parseInt(inputN.textFieldText)))
                error += Strings.hyphen + Strings.uIsLarge + Strings.endOfError

            if(inputV.textFieldText == "")
                error += Strings.hyphen + Strings.uIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputV.textFieldText)))
                error += Strings.hyphen + Strings.vIsNotValid + Strings.endOfError
            if(parseFloat(inputV.textFieldText) <= 0)
                error += Strings.hyphen + Strings.vIsSmall + Strings.endOfError
            if(!inputForce.checked && parseFloat(inputV.textFieldText) > 1 / (4 * parseInt(inputN.textFieldText)))
                error += Strings.hyphen + Strings.vIsLarge + Strings.endOfError

            if(inputS.textFieldText == "")
                error += Strings.hyphen + Strings.sIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputS.textFieldText)))
                error += Strings.hyphen + Strings.sIsNotValid + Strings.endOfError
            if(parseFloat(inputS.textFieldText) < -1)
                error += Strings.hyphen + Strings.sIsSmall + Strings.endOfError
            if(parseFloat(inputS.textFieldText) > 1)
                error += Strings.hyphen + Strings.sIsLarge + Strings.endOfError
        }

        if(inputH.textFieldText == "")
            error += Strings.hyphen + Strings.hIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputH.textFieldText)))
            error += Strings.hyphen + Strings.hIsNotValid + Strings.endOfError
        if(parseFloat(inputH.textFieldText) < 0)
            error += Strings.hyphen + Strings.hIsSmall + Strings.endOfError
        if(parseFloat(inputH.textFieldText) > 1)
            error += Strings.hyphen + Strings.hIsLarge + Strings.endOfError

        if(inputT.textFieldText == "")
            error += Strings.hyphen + Strings.tIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputT.textFieldText)))
            error += Strings.hyphen + Strings.tIsNotValid + Strings.endOfError
        if(parseInt(inputT.textFieldText) < 1)
            error += Strings.hyphen + Strings.tIsSmall + Strings.endOfError
        // Number of threads (t) does not have upper limites, since it depends on the hardware available.

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
