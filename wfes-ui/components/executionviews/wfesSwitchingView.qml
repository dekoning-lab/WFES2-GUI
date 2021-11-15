import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0

ApplicationWindow {
    id: rootWfesSwitching
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.wfesSwitching + ")"

    color: Universal.chromeLowColor

    visible: false

    width: column1.width + column2.width + column3.width + (Style.marginSmall * 6)
    minimumWidth: column1.width + column2.width + column3.width + (Style.marginSmall * 6)
    maximumWidth: column1.width + column2.width + column3.width + (Style.marginSmall * 6)
    height: upperMenu.height + Math.max(column1.height, column2.height, column3.height) + bottomMenu.height
    minimumHeight: upperMenu.height + Math.max(column1.height, column2.height, column3.height) + bottomMenu.height
    maximumHeight: upperMenu.height + Math.max(column1.height, column2.height, column3.height) + bottomMenu.height

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootWfesSwitching.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
            messageDialogOnClose.open()
        } else {
            rootWfesSwitching.hide();
            root.visible = true;
            rootWfesSwitching.updateBackend()
            outputControllerWfesSwitching.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfesSwitching.hide();
            root.visible = true;
        }
    }


    Component.onCompleted: {
        // Center window in screen.
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

                    Layout.margins: Style.marginSmall
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
                                margins: Style.marginSmall
                            }

                            RadioButton {
                                id: radioButtonWfesSwitchingAbsorption
                                checked: inputControllerWfesSwitching.ui_modelType === "Absorption"
                                text: Strings.wfesSwitchingAbsorption

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSwitchingAbsorptionTooltip

                                onCheckedChanged: {
                                    inputA.enabled = checked;
                                    inputC.enabled = !checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = checked;
                                    inputWriteB.enabled = checked;
                                    inputWriteNExt.enabled = checked;
                                    inputWriteNFix.enabled = checked;

                                    outputPExt.visible = checked;
                                    outputPFix.visible = checked;
                                    outputText.visible = checked;
                                    outputTextStd.visible = checked;
                                    outputTFix.visible = !checked;
                                    outputTFixAbsMode.visible = checked;
                                    outputTFixStd.visible = checked;
                                    outputRate.visible = !checked;
                                }
                            }
                            RadioButton {
                                id: radioButtonWfesSwitchingFixation
                                checked: inputControllerWfesSwitching.ui_modelType == "Fixation"
                                text: Strings.wfesSwitchingFixation

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSwitchingFixationTooltip

                                onCheckedChanged: {
                                    inputA.enabled = checked;
                                    inputC.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteN.enabled = checked;
                                    inputWriteB.enabled = checked;
                                    inputWriteNExt.enabled = !checked;
                                    inputWriteNFix.enabled = !checked;

                                    outputPExt.visible = !checked;
                                    outputPFix.visible = !checked;
                                    outputText.visible = !checked;
                                    outputTextStd.visible = !checked;
                                    outputTFix.visible = checked;
                                    outputTFixAbsMode.visible = !checked;
                                    outputTFixStd.visible = !checked;
                                    outputRate.visible = checked;
                                }
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: componentsSection.width
                        color: Universal.baseHighColor
                    }

                    Label {
                        id: labelComponents
                        text: Strings.components + Strings.colon
                        font.bold: true
                    }

                    Rectangle {
                        id: componentsSection
                        width: commonSection.width + Style.marginSmall
                        height: childrenRect.height

                        color: "transparent"

                        Layout.alignment: Qt.AlignTop

                        DynamicTabView {
                            id: componentsSectionTabView
                            width: commonSection.width + Style.marginSmall
                            height: 270
                            tabNames: Strings.comp
                            urlComponent: "qrc:/components/executionviews/tabcomponents/tabWfesSwitchingComponent.qml"
                            onAdd: function(){
                                var num_comps = inputControllerWfesSwitching.ui_num_comp
                                inputControllerWfesSwitching.ui_num_comp = parseInt(num_comps) + 1

                                // Update previous adding 1
                                var vector = inputControllerWfesSwitching.ui_r_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_r_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_r_vec = vector

                                vector = inputControllerWfesSwitching.ui_N_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_N_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_N_vec = vector

                                vector = inputControllerWfesSwitching.ui_p_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_p_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_p_vec = vector

                                vector = inputControllerWfesSwitching.ui_s_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_s_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_s_vec = vector

                                vector = inputControllerWfesSwitching.ui_h_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_h_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_h_vec = vector

                                vector = inputControllerWfesSwitching.ui_u_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_u_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_u_vec = vector

                                vector = inputControllerWfesSwitching.ui_v_vec
                                vector[num_comps] = inputControllerWfesSwitching.ui_v_vec[num_comps-1]
                                inputControllerWfesSwitching.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfesSwitching.ui_num_comp
                                inputControllerWfesSwitching.ui_num_comp = parseInt(num_comps) - 1
                            }
                            onLoaded: function() {
                                var dummyString = outputControllerWfesSwitching.ui_load_config
                                rootWfesSwitching.updateGUI()
                                updateScaledParameters(false)
                            }
                            changeBoxColor: function() {
                                for(var i = 0; i < componentsSectionTabView.children[0].count - 2; i++)
                                    componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldTextEdited()
                            }
                        }

                    }

                    Rectangle {
                        height: 1
                        width: componentsSectionTabView.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: commonSection
                        width: childrenRect.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelCommonParameters
                            text: Strings.commonParameters + Strings.colon
                            font.bold: true
                        }

                        GridLayout {
                            id: commonSectionGrid
                            columns: 2
                            anchors {
                                top: labelCommonParameters.bottom
                                left: parent.left
                                margins: Style.marginSmall
                            }

                            LabeledTextField {
                                id: inputA
                                text: Strings.a + Strings.colon
                                toolTipText: Strings.aTooltip
                                validator: DoubleValidator {bottom: 0}
                                textFieldText: inputControllerWfesSwitching.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerWfesSwitching.ui_a = inputA.textFieldText
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
                                validator: DoubleValidator {bottom: 0}
                                textFieldText: inputControllerWfesSwitching.ui_c
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputC.textFieldText)) && parseFloat(inputC.textFieldText) >= 0) {
                                        inputControllerWfesSwitching.ui_c = inputC.textFieldText
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
                    Layout.topMargin: Style.marginSmall
                    Layout.bottomMargin: Style.marginSmall
                }

                ColumnLayout {
                    id: column2
                    Layout.preferredHeight: parent.height

                    ColumnLayout {
                        Layout.alignment: Qt.AlignTop
                        Layout.margins: Style.marginSmall

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
                                        margins: Style.marginSmall
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteQ
                                        text: Strings.outputQ + Strings.colon
                                        toolTipText: Strings.outputQTooltip
                                        checked: inputControllerWfesSwitching.ui_output_Q
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteR
                                        text: Strings.outputR + Strings.colon
                                        toolTipText: Strings.outputRTooltip
                                        checked: inputControllerWfesSwitching.ui_output_R
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteN
                                        text: Strings.outputN + Strings.colon
                                        toolTipText: Strings.outputNTooltip
                                        checked: inputControllerWfesSwitching.ui_output_N
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteB
                                        text: Strings.outputB + Strings.colon
                                        toolTipText: Strings.outputBTooltip
                                        checked: inputControllerWfesSwitching.ui_output_B
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNExt
                                        text: Strings.outputNExt + Strings.colon
                                        toolTipText: Strings.outputNExtTooltip
                                        checked: inputControllerWfesSwitching.ui_output_N_Ext
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNFix
                                        text: Strings.outputNFix + Strings.colon
                                        toolTipText: Strings.outputNFixTooltip
                                        checked: inputControllerWfesSwitching.ui_output_N_Fix
                                    }

                                    Label {
                                        // Empty, so Res is always at right.
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteRes
                                        text: Strings.outputRes + Strings.colon
                                        toolTipText: Strings.outputResTooltip
                                        checked: inputControllerWfesSwitching.ui_output_Res
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
                                        margins: Style.marginSmall
                                    }
                                    RowLayout {
                                        width: childrenRect.width

                                        LabeledCheckBox {
                                            id: inputForce
                                            text: Strings.force + Strings.colon
                                            toolTipText: Strings.forceTooltip
                                            checked: inputControllerWfesSwitching.ui_force
                                        }

                                        LabeledTextField {
                                            id: inputT
                                            text: Strings.t + Strings.colon
                                            labelPreferredWidth: Style.marginSmall
                                            toolTipText: Strings.tTooltip
                                            validator: IntValidator {bottom: 1;}
                                            textFieldText: inputControllerWfesSwitching.ui_t
                                            textFieldTextEdited: function(){
                                                if(parseInt(inputT.textFieldText) >= 1) {
                                                    inputControllerWfesSwitching.ui_t = inputT.textFieldText
                                                    borderColor = "#555555"
                                                } else {
                                                    borderColor = "#ff0000"
                                                }
                                            }
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

                                        /*LabeledTextField {
                                            id: inputI
                                            text: Strings.iDist + Strings.colon
                                            toolTipText: Strings.iDistTooltip
                                            labelPreferredWidth: 75
                                            textFieldPreferredWidth: 185
                                            textFieldText: inputControllerWfesSwitching.ui_initial_distribution
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
                                        }*/

                                    }

                                }
                            }

                        }

                        RowLayout {
                            id: row2
                            Layout.preferredWidth: parent.width

                            Button {
                                id: stopButton
                                Layout.margins: Style.marginSmall
                                Layout.alignment: Qt.AlignRight
                                text: Strings.stopButton

                                Binding {
                                    target: stopButton
                                    property: "enabled"
                                    value: !outputControllerWfesSwitching.ui_get_not_exec

                                }

                                onClicked: {
                                    outputControllerWfesSwitching.ui_stop
                                    stopButton.enabled = false
                                    executeButton.enabled = true
                                    bottomMenu.visibleProgressBar = false
                                }
                            }

                            Button {
                                id: executeButton
                                Layout.margins: Style.marginSmall
                                Layout.alignment: Qt.AlignRight
                                text: Strings.executeButton

                                onEnabledChanged: {
                                    if(outputControllerWfesSwitching.ui_get_not_exec)
                                        imageOutputController.image_changed()
                                    console.log(outputControllerWfesSwitching.ui_get_error_message)
                                    if(outputControllerWfesSwitching.ui_get_error_message !== "") {
                                        messageDialog.text = outputControllerWfesSwitching.ui_get_error_message
                                        messageDialog.open()
                                        outputControllerWfesSwitching.ui_reset_error
                                    }
                                }

                                Binding {
                                    target: executeButton
                                    property: "enabled"
                                    value: outputControllerWfesSwitching.ui_get_not_exec

                                }

                                // All changes made in backend from GUI are done here.
                                onClicked: {
                                    var error = checkIntegrity()


                                    if(error === "") {
                                        updateBackend()
                                        executeButton.enabled = false
                                        stopButton.enabled = true
                                        bottomMenu.visibleProgressBar = true
                                        outputControllerWfesSwitching.ui_execute
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
                    Layout.topMargin: Style.marginSmall
                    Layout.bottomMargin: Style.marginSmall
                }

                ColumnLayout {
                    id: column3
                    Layout.margins: Style.marginSmall
                    Layout.alignment: Qt.AlignTop

                    Label {
                        id: labelFinalOutput
                        text: Strings.output + Strings.colon
                        font.bold: true
                    }

                    ColumnLayout {

                        LabeledTextField {
                            id: outputPExt
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.pExt + Strings.colon
                            toolTipText: Strings.pExtTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_p_ext
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputPFix
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.pFix + Strings.colon
                            toolTipText: Strings.pFixTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_p_fix
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputText
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.tExt + Strings.colon
                            toolTipText: Strings.tExtTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_t_ext
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputTextStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.tExtStd + Strings.colon
                            toolTipText: Strings.tExtStdTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_t_ext_std
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }


                        LabeledTextField {
                            id: outputTFix
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.tFix + Strings.colon
                            toolTipText: Strings.tFixTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_t_fix
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Fixation")
                        }

                        LabeledTextField {
                            id: outputTFixAbsMode
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.tFix + Strings.colon
                            toolTipText: Strings.tFixTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_t_fix_abs_mode
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputTFixStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.tFixStd + Strings.colon
                            toolTipText: Strings.tFixStdTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_t_fix_std
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputRate
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: Strings.rate + Strings.colon
                            toolTipText: Strings.rateTooltip
                            textFieldText: outputControllerWfesSwitching.ui_get_rate
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Fixation")
                        }


                        Button {
                            text: Strings.copyToClipboard

                            Layout.alignment: Qt.AlignHCenter

                            onClicked: {
                                outputControllerWfesSwitching.coppyToClipboard()
                            }
                        }
                        //Vectors P_cond_ext, V_cond_ext... cannot be shown in the GUI, takes too much space, so
                        //those vectors are printed directly into the csv file.
                    }

                }
            }
        }

        Rectangle {
            id: separatorBottomBar
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
            value: !outputControllerWfesSwitching.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfesSwitching.ui_progress

            executionTime: {
                outputControllerWfesSwitching.ui_get_time == "" ? "" : outputControllerWfesSwitching.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }
    }

    function updateGUI() {
        radioButtonWfesSwitchingAbsorption.checked = inputControllerWfesSwitching.ui_modelType == "Absorption"
        radioButtonWfesSwitchingFixation.checked = inputControllerWfesSwitching.ui_modelType == "Fixation"

        inputA.textFieldText = inputControllerWfesSwitching.ui_a
        inputC.textFieldText = inputControllerWfesSwitching.ui_c

        var N_vec = inputControllerWfesSwitching.ui_N_vec
        var p_vec = inputControllerWfesSwitching.ui_p_vec
        var r_vec = inputControllerWfesSwitching.ui_r_vec
        var u_vec = inputControllerWfesSwitching.ui_u_vec
        var v_vec = inputControllerWfesSwitching.ui_v_vec
        var s_vec = inputControllerWfesSwitching.ui_s_vec
        var h_vec = inputControllerWfesSwitching.ui_h_vec

        // Minus 2 because we don't have to count the add and delete tabs.
        // If the number of current tabs is less than the number of components to load,
        // add a tab.
        if(componentsSectionTabView.children[0].count - 2 < inputControllerWfesSwitching.ui_num_comp) {
            while(componentsSectionTabView.children[0].count - 2 < inputControllerWfesSwitching.ui_num_comp) {
                // Create new tab.
                componentsSectionTabView.children[0].addTab()
                // Don't update ui_num_comp
                inputControllerWfesSwitching.ui_num_comp = parseInt(inputControllerWfesSwitching.ui_num_comp) - 1
            }
        // If the number of current tabs is greater than the number of components to load,
        // remove a tab.
        } else if(componentsSectionTabView.children[0].count - 2 > inputControllerWfesSwitching.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 > inputControllerWfesSwitching.ui_num_comp) {
                // Delete a tab.
                componentsSectionTabView.children[0].deleteTab()
                // Don't update ui_num_comp
                inputControllerWfesSwitching.ui_num_comp = parseInt(inputControllerWfesSwitching.ui_num_comp) + 1
            }
        }

        console.log(inputControllerWfesSwitching.ui_num_comp)
        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText = N_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText = p_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText = r_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText = h_vec[i]
        }

        inputWriteQ.checked = inputControllerWfesSwitching.ui_output_Q
        inputWriteR.checked = inputControllerWfesSwitching.ui_output_R
        inputWriteN.checked = inputControllerWfesSwitching.ui_output_N
        inputWriteB.checked = inputControllerWfesSwitching.ui_output_B
        inputWriteNExt.checked = inputControllerWfesSwitching.ui_output_N_Ext
        inputWriteNFix.checked = inputControllerWfesSwitching.ui_output_N_Fix
        inputWriteRes.checked = inputControllerWfesSwitching.ui_output_Res
        inputT.textFieldText = inputControllerWfesSwitching.ui_t
        inputForce.checked = inputControllerWfesSwitching.ui_force

        //inputI.textFieldText = inputControllerWfesSwitching.ui_initial_distribution

        var library = inputControllerWfesSwitching.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfesSwitching.ui_solver
        if(solver === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(solver === "BicGStab")
            comboBoxSolver.currentIndex = 1

        // Update boxes.
        for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldTextEdited()
        }
        inputA.textFieldTextEdited()
        inputC.textFieldTextEdited()
        inputT.textFieldTextEdited()

    }

    function updateBackend() {
        // Set mode in backend.
        if(radioButtonWfesSwitchingAbsorption.checked)
            inputControllerWfesSwitching.ui_modelType = "Absorption"
        else if (radioButtonWfesSwitchingFixation.checked)
            inputControllerWfesSwitching.ui_modelType = "Fixation"

        inputControllerWfesSwitching.ui_a = inputA.textFieldText
        inputControllerWfesSwitching.ui_c = inputC.textFieldText
        var N_vec = []
        var p_vec = []
        var r_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < componentsSectionTabView.children[0].count - 2; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var p = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var r = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            r_vec.push(r)
            p_vec.push(p)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerWfesSwitching.ui_N_vec = N_vec
        inputControllerWfesSwitching.ui_r_vec = r_vec
        inputControllerWfesSwitching.ui_p_vec = p_vec
        inputControllerWfesSwitching.ui_u_vec = u_vec
        inputControllerWfesSwitching.ui_v_vec = v_vec
        inputControllerWfesSwitching.ui_s_vec = s_vec
        inputControllerWfesSwitching.ui_h_vec = h_vec

        inputControllerWfesSwitching.ui_output_Q = inputWriteQ.checked
        inputControllerWfesSwitching.ui_output_R = inputWriteR.checked
        inputControllerWfesSwitching.ui_output_N = inputWriteN.checked
        inputControllerWfesSwitching.ui_output_B = inputWriteB.checked
        inputControllerWfesSwitching.ui_output_N_Ext = inputWriteNExt.checked
        inputControllerWfesSwitching.ui_output_N_Fix = inputWriteNFix.checked
        inputControllerWfesSwitching.ui_output_Res = inputWriteRes.checked
        inputControllerWfesSwitching.ui_t = inputT.textFieldText
        inputControllerWfesSwitching.ui_force = inputForce.checked

        //inputControllerWfesSwitching.ui_initial_distribution = inputI.textFieldText

        inputControllerWfesSwitching.ui_library = comboBoxLibrary.currentText;
        inputControllerWfesSwitching.ui_solver = comboBoxSolver.currentText;
        inputControllerWfesSwitching.ui_num_comp = componentsSectionTabView.children[0].count - 2
    }

    function checkIntegrity() {
        var error = ""

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
        if(parseFloat(inputC.textFieldText) < 0)
            error += Strings.hyphen + Strings.cIsSmall + Strings.endOfError
        if(parseFloat(inputC.textFieldText) > 10e-3)
            error += Strings.hyphen + Strings.cIsLarge + Strings.endOfError

        var N_vec = []
        var p_vec = []
        var r_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < componentsSectionTabView.children[0].count - 2; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var p = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var r = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            r_vec.push(r)
            p_vec.push(p)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }

        for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            if(N === "")
                error += Strings.hyphen + Strings.nMulIsEmpty.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(N_vec[i])))
                error += Strings.hyphen + Strings.nMulIsNotValid.arg(i + 1) + Strings.endOfError
            if(parseInt(N_vec[i]) < 2)
                error += Strings.hyphen + Strings.nMulIsSmall.arg(i + 1) + Strings.endOfError
            if(!inputForce.checked && parseInt(N_vec[i]) > 50000)
                error += Strings.hyphen + Strings.nMulIsLargeScaled.arg(i + 1) + Strings.endOfError
        }

        for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            p = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            if(p === "")
                error += Strings.hyphen + Strings.pStartMulIsEmpty.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(p_vec[i])))
                error += Strings.hyphen + Strings.pStartMulIsNotValid.arg(i + 1) + Strings.endOfError
            if(parseInt(p_vec[i]) < 0)
                error += Strings.hyphen + Strings.pStartMulIsSmall.arg(i + 1) + Strings.endOfError
            if(parseInt(p_vec[i]) > 1)
                error += Strings.hyphen + Strings.pStartMulIsLarge.arg(i + 1) + Strings.endOfError
        }

        for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            r = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            if(r === "")
                error += Strings.hyphen + Strings.rSwitchMulIsEmpty.arg(i + 1) + Strings.endOfError
            var splitted = r_vec[i].split(", ")
            if(splitted.length !== parseInt(inputControllerWfesSwitching.ui_num_comp))
                error += Strings.hyphen + Strings.rSwitchMulNumComps.arg(i + 1).arg(splitted.length).arg(inputControllerWfesSwitching.ui_num_comp) + Strings.endOfError
            if(splitted.length > 1) {
                var valid = true;
                for(var j = 0; j < splitted.length; j++) {
                    if(splitted[j] === "")
                        error += Strings.hyphen + Strings.rSwitchMulIsEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(splitted[j])))
                        error += Strings.hyphen + Strings.rSwitchMulIsNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(splitted[j]) < 0) {
                        error += Strings.hyphen + Strings.rSwitchMulIsSmall.arg(i + 1) + Strings.endOfError
                        break;
                    } else if (parseFloat(splitted[j]) > 1) {
                        error += Strings.hyphen + Strings.rSwitchMulIsLarge.arg(i + 1) + Strings.endOfError
                        break;
                    }
                }
            } else {
                if(r_vec[i] === "")
                    error += Strings.hyphen + Strings.rSwitchMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(r_vec[i])))
                    error += Strings.hyphen + Strings.rSwitchMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(r_vec[i]) < 0) {
                    error += Strings.hyphen + Strings.rSwitchMulIsSmall.arg(i + 1) + Strings.endOfError
                    break;
                } else if (parseFloat(r_vec[i]) > 1) {
                    error += Strings.hyphen + Strings.rSwitchMulIsLarge.arg(i + 1) + Strings.endOfError
                    break;
                }
            }
        }

        if(globalConfiguration.ui_population_scaled) {
            for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
                if(u === "")
                    error += Strings.hyphen + Strings.uMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(u_vec[i].textFieldText) <= 0)
                    error += Strings.hyphen + Strings.uMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(u_vec[i]) > 1)
                    error += Strings.hyphen + Strings.uMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
                if(v === "")
                    error += Strings.hyphen + Strings.vMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(v_vec[i])))
                    error += Strings.hyphen + Strings.vMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(v_vec[i].textFieldText) <= 0)
                    error += Strings.hyphen + Strings.vMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(v_vec[i]) > 1)
                    error += Strings.hyphen + Strings.vMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
                if(s === "")
                    error += Strings.hyphen + Strings.sMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(s_vec[i])))
                    error += Strings.hyphen + Strings.sMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(s_vec[i]) < -1 * (2 * parseInt(N_vec[i])))
                    error += Strings.hyphen + Strings.sMulIsSmall.arg(i + 1) + Strings.endOfError
                if(parseFloat(s_vec[i]) > 1 * (2 * parseInt(N_vec[i])))
                    error += Strings.hyphen + Strings.sMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }
        } else {
            for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
                if(u === "")
                    error += Strings.hyphen + Strings.uMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(u_vec[i].textFieldText) <= 0)
                    error += Strings.hyphen + Strings.uMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(u_vec[i]) > 1 / (4 * parseInt(N_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsLarge.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
                if(v === "")
                    error += Strings.hyphen + Strings.vMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(v_vec[i])))
                    error += Strings.hyphen + Strings.vMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(v_vec[i].textFieldText) <= 0)
                    error += Strings.hyphen + Strings.vMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(v_vec[i]) > 1 / (4 * parseInt(N_vec[i])))
                    error += Strings.hyphen + Strings.vMulIsLarge.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
                if(s === "")
                    error += Strings.hyphen + Strings.sMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(s_vec[i])))
                    error += Strings.hyphen + Strings.sMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(s_vec[i]) < -1)
                    error += Strings.hyphen + Strings.sMulIsSmall.arg(i + 1) + Strings.endOfError
                if(parseFloat(s_vec[i]) > 1 )
                    error += Strings.hyphen + Strings.sMulIsLarge.arg(i + 1) + Strings.endOfError
            }
        }


        for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            if(h === "")
                error += Strings.hyphen + Strings.hMulIsEmpty.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(h_vec[i])))
                error += Strings.hyphen + Strings.hMulIsNotValid.arg(i + 1) + Strings.endOfError
            if(parseFloat(h_vec[i]) < 0)
                error += Strings.hyphen + Strings.hMulIsSmall.arg(i + 1) + Strings.endOfError
            if(parseFloat(h_vec[i]) > 1)
                error += Strings.hyphen + Strings.hMulIsLarge.arg(i + 1) + Strings.endOfError
        }

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
        var loadedComponents = true
        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            if(typeof(componentsSectionTabView.children[0].getTab(i)) === "undefined") {
                loadedComponents = false
            }
        }
        if(loadedComponents) {
            var u, v, s
            var u_vec, v_vec, s_vec = []
            if(globalConfiguration.ui_population_scaled) {
                u = inputControllerWfesSwitching.ui_u_vec
                v = inputControllerWfesSwitching.ui_v_vec
                s = inputControllerWfesSwitching.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] * (4 * parseInt(inputControllerWfesSwitching.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] * (4 * parseInt(inputControllerWfesSwitching.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] * (2 * parseInt(inputControllerWfesSwitching.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfesSwitching.ui_u_vec = u_vec
                inputControllerWfesSwitching.ui_v_vec = v_vec
                inputControllerWfesSwitching.ui_s_vec = s_vec


            } else if(updateNonChecked){
                u = inputControllerWfesSwitching.ui_u_vec
                v = inputControllerWfesSwitching.ui_v_vec
                s = inputControllerWfesSwitching.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] / (4 * parseInt(inputControllerWfesSwitching.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] / (4 * parseInt(inputControllerWfesSwitching.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] / (2 * parseInt(inputControllerWfesSwitching.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfesSwitching.ui_u_vec = u_vec
                inputControllerWfesSwitching.ui_v_vec = v_vec
                inputControllerWfesSwitching.ui_s_vec = s_vec

            }
        }
    }
}
