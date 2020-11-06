import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

//TODO Implement value validators and return exceptions.
ApplicationWindow {
    id: rootWfesSwitching
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFES Switching)")

    color: Universal.chromeLowColor

    visible: true

    width: 955
    minimumWidth: 955
    maximumWidth: 955
    height: 530
    minimumHeight: 530
    maximumHeight: 530

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootWfesSwitching.destroy();
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
                                id: radioButtonWfesSwitchingAbsorption
                                checked: inputControllerWfesSwitching.ui_modelType === "Absorption"
                                text: qsTr("Absorption")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("//TODO.")

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
                                    outputTFix.visible = checked;
                                    outputTFixStd.visible = checked;
                                    outputRate.visible = !checked;
                                }
                            }
                            RadioButton {
                                id: radioButtonWfesSwitchingFixation
                                checked: inputControllerWfesSwitching.ui_modelType == "Fixation"
                                text: qsTr("Fixation")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("//TODO.")

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
                                    outputTFixStd.visible = !checked;
                                    outputRate.visible = checked;
                                }
                            }

                        }

                    }

                    Rectangle {
                        id: separator1column1
                        height: 1
                        width: commonSection.width + 10
                        color: Universal.baseHighColor
                    }

                    Label {
                        id: labelComponents
                        text: "Components:"
                        font.bold: true
                    }

                    Rectangle {
                        id: componentsSection
                        width: commonSection.width + 10
                        height: childrenRect.height

                        color: "transparent"

                        Layout.alignment: Qt.AlignTop

                        DynamicTabView {
                            id: componentsSectionTabView
                            width: commonSection.width + 10
                            height: 270
                            tabNames: "Comp."
                            urlComponent: "qrc:/views/executionviews/tabcomponents/tabWfesSwitchingComponent.qml"
                            onAdd: function(){

                                //Increase arrays size.
                                var num_comps = parseInt(componentsSectionTabView.children[0].count - 2) + 1
                                inputControllerWfesSwitching.ui_num_comp = parseInt(num_comps)

                                // Update previous adding 1
                                var vector = inputControllerWfesSwitching.ui_r_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_r_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_r_vec = vector

                                vector = inputControllerWfesSwitching.ui_N_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_N_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_N_vec = vector

                                vector = inputControllerWfesSwitching.ui_p_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_p_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_p_vec = vector

                                vector = inputControllerWfesSwitching.ui_s_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_s_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_s_vec = vector

                                vector = inputControllerWfesSwitching.ui_h_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_h_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_h_vec = vector

                                vector = inputControllerWfesSwitching.ui_u_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_u_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_u_vec = vector

                                vector = inputControllerWfesSwitching.ui_v_vec
                                vector[num_comps-1] = inputControllerWfesSwitching.ui_v_vec[num_comps-2]
                                inputControllerWfesSwitching.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfesSwitching.ui_num_comp
                                inputControllerWfesSwitching.ui_num_comp = parseInt(num_comps) - 1
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
                            text: "Common Parameters"
                            font.bold: true
                        }

                        GridLayout {
                            id: commonSectionGrid
                            columns: 2
                            anchors {
                                top: labelCommonParameters.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSwitching.ui_a
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "Starting number of copies integration cutoff."
                                validator: DoubleValidator {bottom: 0; top: 1;}
                                textFieldText: inputControllerWfesSwitching.ui_c
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

                        ColumnLayout {
                            Layout.alignment: Qt.AlignTop
                            Layout.margins: 10
                            height: childrenRect.height

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
                                        toolTipText: "Output Q matrix to file."
                                        checked: inputControllerWfesSwitching.ui_output_Q
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteR
                                        text: "R: "
                                        toolTipText: "Output R vectors to file."
                                        checked: inputControllerWfesSwitching.ui_output_R
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteN
                                        text: "N: "
                                        toolTipText: "Output N matrix to file."
                                        checked: inputControllerWfesSwitching.ui_output_N
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteB
                                        text: "B: "
                                        toolTipText: "Output B vectors to file."
                                        checked: inputControllerWfesSwitching.ui_output_B
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNExt
                                        text: "N Ext.: "
                                        toolTipText: "Output extinction-conditional sojourn to file."
                                        checked: inputControllerWfesSwitching.ui_output_N_Ext
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNFix
                                        text: "N Fix.: "
                                        toolTipText: "Output fixation-conditional sojourn to file."
                                        checked: inputControllerWfesSwitching.ui_output_N_Fix
                                    }

                                    Label {
                                        // Empty, so Res is always at right.
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteRes
                                        text: "Res: "
                                        toolTipText: "Output Res (Generated results at right side) as CSV file."
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
                                            checked: inputControllerWfesSwitching.ui_force
                                        }

                                        LabeledTextField {
                                            id: inputT
                                            text: "t: "
                                            labelPreferredWidth: 10
                                            toolTipText: "Number of threads for OpenMP."
                                            validator: DoubleValidator {bottom: 2; top: 50000;}
                                            textFieldText: inputControllerWfesSwitching.ui_t
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
                                            textFieldText: inputControllerWfesSwitching.ui_initial_distribution
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
                            Layout.preferredWidth: parent.width

                            Button {
                                id: stopButton
                                Layout.margins: 10
                                Layout.alignment: Qt.AlignRight
                                text: "Stop"

                                Binding {
                                    target: stopButton
                                    property: "enabled"
                                    value: !outputControllerWfesSwitching.ui_get_not_exec

                                }

                                onClicked: {
                                    outputControllerWfesSwitching.ui_stop
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
                                    if(outputControllerWfesSwitching.ui_get_not_exec)
                                        imageOutputController.image_changed()
                                }

                                Binding {
                                    target: executeButton
                                    property: "enabled"
                                    value: outputControllerWfesSwitching.ui_get_not_exec

                                }

                                // All changes made in backend from GUI are done here.
                                onClicked: {
                                    bottomMenu.visibleProgressBar = true

                                    updateBackend()

                                    console.log(outputControllerWfesSwitching.ui_get_error_message)
                                    if(outputControllerWfesSwitching.ui_get_error_message === "") {
                                        executeButton.enabled = false
                                        stopButton.enabled = true
                                        outputControllerWfesSwitching.ui_execute
                                    } else {
                                        messageDialog.text = outputControllerWfesSwitching.ui_get_error_message
                                        messageDialog.open()
                                    }
                                    outputControllerWfesSwitching.ui_reset_error
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

                    Label {
                        id: labelFinalOutput
                        text: "Output:"
                        font.bold: true
                    }

                    ColumnLayout {

                        LabeledTextField {
                            id: outputPExt
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "P ext. : "
                            toolTipText: "Probability of extintion."
                            textFieldText: outputControllerWfesSwitching.ui_get_p_ext
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputPFix
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "P fix. : "
                            toolTipText: "Probability of fixation."
                            textFieldText: outputControllerWfesSwitching.ui_get_p_fix
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputText
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T ext.: "
                            toolTipText: "Extintion time."
                            textFieldText: outputControllerWfesSwitching.ui_get_t_ext
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputTextStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T ext. std.: "
                            toolTipText: "Standard extintion time."
                            textFieldText: outputControllerWfesSwitching.ui_get_t_ext_std
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }


                        LabeledTextField {
                            id: outputTFix
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T fix.: "
                            toolTipText: "Fixation time."
                            textFieldText: outputControllerWfesSwitching.ui_get_t_fix
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputTFixStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T fix. std.: "
                            toolTipText: "Standard fixation time."
                            textFieldText: outputControllerWfesSwitching.ui_get_t_fix_std
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Absorption")
                        }

                        LabeledTextField {
                            id: outputRate
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "Rate: "
                            toolTipText: "//TODO"
                            textFieldText: outputControllerWfesSwitching.ui_get_rate
                            readOnly: true
                            visible: (inputControllerWfesSwitching.ui_modelType == "Fixation")
                        }

                        //TODO Vectors P_cond_ext, V_cond_ext... cannot be shown in the GUI, takes too much space, so
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
        var r_vec = inputControllerWfesSwitching.ui_r_vec
        var p_vec = inputControllerWfesSwitching.ui_p_vec
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
                inputControllerWfesSwitching.ui_num_comp = inputControllerWfesSwitching.ui_num_comp - 1
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

        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText = N_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText = r_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText = p_vec[i]
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

        inputI.textFieldText = inputControllerWfesSwitching.ui_initial_distribution

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
        var r_vec = []
        var p_vec = []
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

        inputControllerWfesSwitching.ui_initial_distribution = inputI.textFieldText

        inputControllerWfesSwitching.ui_library = comboBoxLibrary.currentText;
        inputControllerWfesSwitching.ui_solver = comboBoxSolver.currentText;

    }

}
