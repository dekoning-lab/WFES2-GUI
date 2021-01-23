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

    id: rootPhaseType
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.phaseType + ")"

    color: Universal.chromeLowColor

    visible: false

    width: 945
    minimumWidth: 945
    maximumWidth: 945
    height: 490
    minimumHeight: 490
    maximumHeight: 490

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootPhaseType.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
            messageDialogOnClose.open()
        } else {
            rootPhaseType.hide();
            root.visible = true;
            rootPhaseType.updateBackend()
            outputControllerPhaseType.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootPhaseType.hide();
            root.visible = true;
        }
    }

    Component.onCompleted: {
        // Center window in screen.
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
        // Load config when create window.
        outputControllerPhaseType.ui_load_config
        rootPhaseType.updateGUI()
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
                            columns: 1
                            anchors {
                                top: labelModel.bottom
                                left: parent.left
                                margins: 10
                            }

                            RadioButton {
                                id: radioButtonPhaseTypeDist
                                checked: inputControllerPhaseType.ui_modelType === "Phase Type Dist."
                                text: Strings.phaseTypeDist

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.phaseTypeDistTooltip

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
                                text: Strings.phaseTypeMoments

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.phaseTypeMomentsTooltip

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
                        width: populationSectionGrid.width + 10
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: populationSection
                        width: childrenRect.width
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
                                textFieldText: inputControllerPhaseType.ui_n
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputN.textFieldText)) && parseInt(inputN.textFieldText) > 1) {
                                        inputControllerPhaseType.ui_n = inputN.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                    inputU.textFieldTextEdited()
                                    inputV.textFieldTextEdited()
                                }
                            }

                            LabeledTextField {
                                id: inputA
                                text: Strings.a + Strings.colon
                                toolTipText: Strings.aTooltip
                                validator: DoubleValidator {bottom: 0; top: 10e-10;}
                                textFieldText: inputControllerPhaseType.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerPhaseType.ui_a = inputA.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputC
                                text: Strings.c + Strings.colon
                                toolTipText: Strings.cTooltip
                                validator: DoubleValidator {bottom: 0; top: 1;}
                                textFieldText: inputControllerPhaseType.ui_c
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Dist."
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputC.textFieldText)) && parseFloat(inputC.textFieldText) >= 0) {
                                        inputControllerPhaseType.ui_c = inputC.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputM
                                text: Strings.m + Strings.colon
                                toolTipText: Strings.mTooltip
                                validator: DoubleValidator {bottom: 1;}
                                textFieldText: inputControllerPhaseType.ui_m
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Dist."
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputM.textFieldText)) && parseInt(inputM.textFieldText) >= 1) {
                                        inputControllerPhaseType.ui_m = inputM.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputK
                                text: Strings.k + Strings.colon
                                validator: IntValidator {bottom: 1;}
                                toolTipText: Strings.kTooltip
                                textFieldText: inputControllerPhaseType.ui_k
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputK.textFieldText)) && parseInt(inputK.textFieldText) >= 2) {
                                        inputControllerPhaseType.ui_k = inputK.textFieldText
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
                        width: populationSectionGrid.width + 10
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
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerPhaseType.ui_u
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1) {
                                            inputControllerPhaseType.ui_u = inputU.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                            inputControllerPhaseType.ui_u = inputU.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputV
                                text: {
                                    if(globalConfiguration.ui_population_scaled)
                                        return Strings.vScaled + Strings.colon
                                    else
                                        return Strings.v + Strings.colon
                                }
                                toolTipText: Strings.vTooltip
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerPhaseType.ui_v
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1) {
                                            inputControllerPhaseType.ui_v = inputV.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                            inputControllerPhaseType.ui_v = inputV.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    }
                                }
                            }

                            LabeledCheckBox {
                                id: inputR
                                text: Strings.rMut + Strings.colon
                                toolTipText: Strings.rMutTooltip
                                checked: inputControllerPhaseType.ui_r
                                enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
                            }
                        }
                    }

                    Rectangle {
                        height: 1
                        width: mutationSectionGrid.width + 10
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
                                toolTipText: Strings.sTooltip
                                validator: DoubleValidator {bottom: -1; top: 1;}
                                textFieldText: inputControllerPhaseType.ui_s
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                            inputControllerPhaseType.ui_s = inputS.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 && parseFloat(inputS.textFieldText) <= 1) {
                                            inputControllerPhaseType.ui_s = inputS.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputH
                                text: Strings.h + Strings.colon
                                toolTipText: Strings.hTooltip
                                validator: DoubleValidator {bottom: 0; top: 1;}
                                textFieldText: inputControllerPhaseType.ui_h
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= 0 && parseFloat(inputH.textFieldText) <= 1) {
                                        inputControllerPhaseType.ui_h = inputH.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
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
                                    checked: inputControllerPhaseType.ui_output_Q
                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: Strings.outputR + Strings.colon
                                    toolTipText: Strings.outputRTooltip
                                    checked: inputControllerPhaseType.ui_output_R
                                }

                                LabeledCheckBox {
                                    id: inputWriteP
                                    text: Strings.outputP + Strings.colon
                                    toolTipText: Strings.outputPTooltip
                                    checked: inputControllerPhaseType.ui_output_P
                                    enabled: inputControllerPhaseType.ui_modelType == "Phase Type Dist."
                                }

                                LabeledCheckBox {
                                    id: inputWriteMoments
                                    text: Strings.outputMoments + Strings.colon
                                    toolTipText: Strings.outputMomentsTooltip
                                    checked: true
                                    enabledCheckBox: false
                                    enabled: inputControllerPhaseType.ui_modelType == "Phase Type Moments"
                                }

                                Label {
                                    // Empty, so Res is always at right.
                                }

                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: Strings.outputRes + Strings.colon
                                    toolTipText: Strings.outputResTooltip
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
                                ColumnLayout {
                                    width: childrenRect.width

                                    RowLayout {
                                        width: childrenRect.width

                                        LabeledCheckBox {
                                            id: inputForce
                                            text: Strings.force + Strings.colon
                                            toolTipText: Strings.forceTooltip
                                            checked: inputControllerPhaseType.ui_force
                                        }

                                        LabeledTextField {
                                            id: inputT
                                            text: Strings.t + Strings.colon
                                            toolTipText: Strings.tTooltip
                                            labelPreferredWidth: 10
                                            validator: IntValidator {bottom: 1;}
                                            textFieldText: inputControllerPhaseType.ui_t
                                            textFieldTextEdited: function(){
                                                if(!Number.isNaN(Number(inputT.textFieldText)) && parseInt(inputT.textFieldText) >= 1) {
                                                    inputControllerPhaseType.ui_t = inputT.textFieldText
                                                    borderColor = "#555555"
                                                } else {
                                                    borderColor = "#ff0000"
                                                }
                                            }
                                        }
                                    }

                                    LabeledTextField {
                                        id: inputSamplingFrequency
                                        text: Strings.sf + Strings.colon
                                        toolTipText: Strings.sfTooltip
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        validator: IntValidator {bottom: 1;}
                                        enabled: radioButtonPhaseTypeDist.checked
                                        textFieldText: inputControllerPhaseType.ui_sampling_frequency
                                        textFieldTextEdited: function(){
                                            if(!Number.isNaN(Number(inputSamplingFrequency.textFieldText)) && parseInt(inputSamplingFrequency.textFieldText) >= 1 && parseInt(inputSamplingFrequency.textFieldText) <= parseInt(inputM.textFieldText)) {
                                                inputControllerPhaseType.ui_sampling_frequency = inputSamplingFrequency.textFieldText
                                                borderColor = "#555555"
                                            } else {
                                                borderColor = "#ff0000"
                                            }
                                        }
                                    }

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
                                value: !outputControllerPhaseType.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerPhaseType.ui_stop
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
                                if(outputControllerPhaseType.ui_get_not_exec)
                                    imageOutputController.image_changed()
                                console.log(outputControllerPhaseType.ui_get_error_message)
                                if(outputControllerPhaseType.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerPhaseType.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerPhaseType.ui_reset_error
                                }

                                if(inputControllerPhaseType.ui_modelType == "Phase Type Dist.") {
                                    upperMenu.updatePhaseTypeDistChart()
                                    if(enabled)
                                        upperMenu.chartVisible = true
                                }
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerPhaseType.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()


                                if(error === "") {
                                    updateBackend()
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
                    title: Strings.dialogWarning
                    text: Strings.empty
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
                                id: outputMean
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.mean + Strings.colon
                                toolTipText: Strings.meanTooltip
                                textFieldText: outputControllerPhaseType.ui_get_mean
                                readOnly: true
                                enabled: radioButtonPhaseTypeMoments.checked
                            }

                            LabeledTextField {
                                id: outputStd
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.std + Strings.colon
                                toolTipText: Strings.stdTooltip
                                textFieldText: outputControllerPhaseType.ui_get_std
                                readOnly: true
                                enabled: radioButtonPhaseTypeMoments.checked
                            }

                        }

                    }

                    Label {
                        id: labelMoments
                        text: Strings.moments + Strings.colon
                        enabled: radioButtonPhaseTypeMoments.checked
                        font.bold: true
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

                    Button {
                        text: Strings.copyToClipboard

                        Layout.alignment: Qt.AlignHCenter

                        visible: radioButtonPhaseTypeMoments.checked

                        onClicked: {
                            outputControllerPhaseType.coppyToClipboard()
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

        inputSamplingFrequency.textFieldText = inputControllerPhaseType.ui_sampling_frequency

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

        inputN.textFieldTextEdited()
        inputS.textFieldTextEdited()
        inputH.textFieldTextEdited()
        inputU.textFieldTextEdited()
        inputV.textFieldTextEdited()
        inputA.textFieldTextEdited()
        inputT.textFieldTextEdited()
        inputK.textFieldTextEdited()
        inputC.textFieldTextEdited()
        inputM.textFieldTextEdited()
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

        inputControllerPhaseType.ui_sampling_frequency = inputSamplingFrequency.textFieldText

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

        if(inputC.textFieldText == "")
            error += Strings.hyphen + Strings.cIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputC.textFieldText)))
            error += Strings.hyphen + Strings.cIsNotValid + Strings.endOfError
        if(parseFloat(inputC.textFieldText) <= 0)
            error += Strings.hyphen + Strings.cIsSmall + Strings.endOfError
        if(parseFloat(inputC.textFieldText) > 1)
            error += Strings.hyphen + Strings.cIsLarge + Strings.endOfError

        if(inputM.textFieldText == "")
            error += Strings.hyphen + Strings.mIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputM.textFieldText)))
            error += Strings.hyphen + Strings.mIsNotValid + Strings.endOfError
        if(parseInt(inputM.textFieldText) < 1)
            error += Strings.hyphen + Strings.mIsSmall + Strings.endOfError
        // Deleted limit for m in phase_type_dist.

        if(inputK.textFieldText == "")
            error += Strings.hyphen + Strings.kIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputK.textFieldText)))
            error += Strings.hyphen + Strings.kIsNotValid + Strings.endOfError
        if(parseInt(inputK.textFieldText) < 2)
            error += Strings.hyphen + Strings.kIsSmall + Strings.endOfError
        // Moments (k) does not have upper limits, at least in the code. The default value is 20.

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
                error += Strings.hyphen + Strings.vIsEmpty + Strings.endOfError
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
                error += Strings.hyphen + Strings.vIsEmpty + Strings.endOfError
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

        if(inputSamplingFrequency.textFieldText == "")
            error += Strings.hyphen + Strings.sfIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputSamplingFrequency.textFieldText)))
            error += Strings.hyphen + Strings.sfIsNotValid + Strings.endOfError
        if(parseInt(inputSamplingFrequency.textFieldText) < 1)
            error += Strings.hyphen + Strings.sfIsSmall + Strings.endOfError
        if(parseInt(inputSamplingFrequency.textFieldText) > parseInt(inputM.textFieldText))
            error += Strings.hyphen + Strings.sfIsLarge + Strings.endOfError

        //TODO Check if Initial Distribution (I) file exists.

        return error.split(" \n \n")[0];

    }

    function updateScaledParameters(updateNonChecked) {
        if(globalConfiguration.ui_population_scaled) {
            inputControllerPhaseType.ui_s = parseFloat(inputControllerPhaseType.ui_s) * (2 * parseInt(inputControllerPhaseType.ui_n))
            inputS.textFieldText = inputControllerPhaseType.ui_s
            inputControllerPhaseType.ui_u = parseFloat(inputControllerPhaseType.ui_u) * (4 * parseInt(inputControllerPhaseType.ui_n))
            inputU.textFieldText = inputControllerPhaseType.ui_u
            inputControllerPhaseType.ui_v = parseFloat(inputControllerPhaseType.ui_v) * (4 * parseInt(inputControllerPhaseType.ui_n))
            inputV.textFieldText = inputControllerPhaseType.ui_v
        } else if(updateNonChecked){
            inputControllerPhaseType.ui_s = parseFloat(inputControllerPhaseType.ui_s) / (2 * parseInt(inputControllerPhaseType.ui_n))
            inputS.textFieldText = inputControllerPhaseType.ui_s
            inputControllerPhaseType.ui_u = parseFloat(inputControllerPhaseType.ui_u) / (4 * parseInt(inputControllerPhaseType.ui_n))
            inputU.textFieldText = inputControllerPhaseType.ui_u
            inputControllerPhaseType.ui_v = parseFloat(inputControllerPhaseType.ui_v) / (4 * parseInt(inputControllerPhaseType.ui_n))
            inputV.textFieldText = inputControllerPhaseType.ui_v
        }
    }
}
