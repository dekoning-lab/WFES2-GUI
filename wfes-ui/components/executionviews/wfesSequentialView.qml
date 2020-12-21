import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

ApplicationWindow {
    id: rootWfesSequential
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFES Sequential)")

    color: Universal.chromeLowColor

    visible: false

    width: 955
    minimumWidth: 955
    maximumWidth: 955
    height: 460
    minimumHeight: 460
    maximumHeight: 460

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootWfesSequential.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = "Some input parameters are incorrect. The configuration will be available in this session, but cannot be saved for future sessions until you fix those values. Do you want to exit anyway?"
            messageDialogOnClose.open()
        } else {
            rootWfesSequential.hide();
            root.visible = true;
            rootWfesSequential.updateBackend()
            outputControllerWfesSequential.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: "Warning"
        text: ""
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfesSequential.hide();
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

                    Layout.margins: 10
                    Layout.alignment: Qt.AlignTop

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
                            urlComponent: "qrc:/components/executionviews/tabcomponents/tabWfesSequentialComponent.qml"
                            onAdd: function(){
                                var num_comps = inputControllerWfesSequential.ui_num_comp
                                inputControllerWfesSequential.ui_num_comp = parseInt(num_comps) + 1

                                var vector = inputControllerWfesSequential.ui_N_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_N_vec[num_comps-1]
                                inputControllerWfesSequential.ui_N_vec = vector

                                vector = inputControllerWfesSequential.ui_t_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_t_vec[num_comps-1]
                                inputControllerWfesSequential.ui_t_vec = vector

                                vector = inputControllerWfesSequential.ui_p_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_p_vec[num_comps-1]
                                inputControllerWfesSequential.ui_p_vec = vector

                                vector = inputControllerWfesSequential.ui_s_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_s_vec[num_comps-1]
                                inputControllerWfesSequential.ui_s_vec = vector

                                vector = inputControllerWfesSequential.ui_h_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_h_vec[num_comps-1]
                                inputControllerWfesSequential.ui_h_vec = vector

                                vector = inputControllerWfesSequential.ui_u_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_u_vec[num_comps-1]
                                inputControllerWfesSequential.ui_u_vec = vector

                                vector = inputControllerWfesSequential.ui_v_vec
                                vector[num_comps] = inputControllerWfesSequential.ui_v_vec[num_comps-1]
                                inputControllerWfesSequential.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfesSequential.ui_num_comp
                                inputControllerWfesSequential.ui_num_comp = parseInt(num_comps) - 1
                            }
                            onLoaded: function() {
                                var dummyString = outputControllerWfesSequential.ui_load_config
                                rootWfesSequential.updateGUI()
                                updateScaledParameters(false)
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
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSequential.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerWfesSequential.ui_a = inputA.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "Integration cutoff."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSequential.ui_c
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputC.textFieldText)) && parseFloat(inputC.textFieldText) >= 0) {
                                        inputControllerWfesSequential.ui_c = inputC.textFieldText
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
                                        checked: inputControllerWfesSequential.ui_output_Q
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteR
                                        text: "R: "
                                        toolTipText: "Output R vectors to file."
                                        checked: inputControllerWfesSequential.ui_output_R
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteN
                                        text: "N: "
                                        toolTipText: "Output N matrix to file."
                                        checked: inputControllerWfesSequential.ui_output_N
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteB
                                        text: "B: "
                                        toolTipText: "Output B vectors to file."
                                        checked: inputControllerWfesSequential.ui_output_B
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNExt
                                        text: "N<sub>Ext</sub>: "
                                        toolTipText: "Output extinction-conditional sojourn to file."
                                        checked: inputControllerWfesSequential.ui_output_N_Ext
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNFix
                                        text: "N<sub>Fix</sub>: "
                                        toolTipText: "Output fixation-conditional sojourn to file."
                                        checked: inputControllerWfesSequential.ui_output_N_Fix
                                    }
                                    LabeledCheckBox {
                                        id: inputWriteNTmo
                                        text: "N<sub>Tmo</sub>: "
                                        toolTipText: "Output timeout-conditional sojourn to file."
                                        checked: inputControllerWfesSequential.ui_output_N_Tmo
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteRes
                                        text: "Res: "
                                        toolTipText: "Output Res (Generated results at right side) as CSV file."
                                        checked: inputControllerWfesSequential.ui_output_Res
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
                                            checked: inputControllerWfesSequential.ui_force
                                        }

                                        LabeledTextField {
                                            id: inputT
                                            text: "t: "
                                            labelPreferredWidth: 10
                                            toolTipText: "Number of threads for OpenMP."
                                            validator: DoubleValidator {bottom: 2; top: 50000;}
                                            textFieldText: inputControllerWfesSequential.ui_t
                                            textFieldTextEdited: function(){
                                                if(!Number.isNaN(Number(inputT.textFieldText)) && parseInt(inputT.textFieldText) >= 1) {
                                                    inputControllerWfesSequential.ui_t = inputT.textFieldText
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

                                        /*LabeledTextField {
                                            id: inputI
                                            text: "I. Dist.: "
                                            toolTipText: "Path to initial probability distribution CSV file."
                                            labelPreferredWidth: 75
                                            textFieldPreferredWidth: 185
                                            textFieldText: inputControllerWfesSequential.ui_initial_distribution
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
                                Layout.margins: 10
                                Layout.alignment: Qt.AlignRight
                                text: "Stop"

                                Binding {
                                    target: stopButton
                                    property: "enabled"
                                    value: !outputControllerWfesSequential.ui_get_not_exec

                                }

                                onClicked: {
                                    outputControllerWfesSequential.ui_stop
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
                                    if(outputControllerWfesSequential.ui_get_not_exec)
                                        imageOutputController.image_changed()
                                    console.log(outputControllerWfesSequential.ui_get_error_message)
                                    if(outputControllerWfesSequential.ui_get_error_message !== "") {
                                        messageDialog.text = outputControllerWfesSequential.ui_get_error_message
                                        messageDialog.open()
                                        outputControllerWfesSequential.ui_reset_error
                                    }
                                }

                                Binding {
                                    target: executeButton
                                    property: "enabled"
                                    value: outputControllerWfesSequential.ui_get_not_exec

                                }

                                // All changes made in backend from GUI are done here.
                                onClicked: {
                                    var error = checkIntegrity()


                                    if(error === "") {
                                        updateBackend()
                                        executeButton.enabled = false
                                        stopButton.enabled = true
                                        bottomMenu.visibleProgressBar = true
                                        outputControllerWfesSequential.ui_execute
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
                            text: "P<sub>ext</sub>: "
                            toolTipText: "Probability of extintion."
                            textFieldText: outputControllerWfesSequential.ui_get_p_ext
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputPFix
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "P<sub>fix</sub>: "
                            toolTipText: "Probability of fixation."
                            textFieldText: outputControllerWfesSequential.ui_get_p_fix
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputPtmo
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "P<sub>tmo</sub>: "
                            toolTipText: "Probability of timeout."
                            textFieldText: outputControllerWfesSequential.ui_get_p_tmo
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputText
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T<sub>ext</sub>: "
                            toolTipText: "Expected number of generations until extinction."
                            textFieldText: outputControllerWfesSequential.ui_get_t_ext
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputTextStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T<sub>ext std</sub>: "
                            toolTipText: "Standard deviation of expected number of generations until extinction."
                            textFieldText: outputControllerWfesSequential.ui_get_t_ext_std
                            readOnly: true
                        }


                        LabeledTextField {
                            id: outputTFix
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T<sub>fix</sub>: "
                            toolTipText: "Expected number of generations until fixation."
                            textFieldText: outputControllerWfesSequential.ui_get_t_fix
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputTFixStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T<sub>fix std</sub>: "
                            toolTipText: "Standard deviation of expected number of generations until fixation."
                            textFieldText: outputControllerWfesSequential.ui_get_t_fix_std
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputTtmo
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T<sub>tmo</sub>: "
                            toolTipText: "Expected number of generations until time out."
                            textFieldText: outputControllerWfesSequential.ui_get_t_tmo
                            readOnly: true
                        }

                        LabeledTextField {
                            id: outputTtmoStd
                            labelPreferredWidth: 100
                            textFieldPreferredWidth: 180
                            text: "T<sub>tmo std</sub>: "
                            toolTipText: "Standard deviation of expected number of generations until time out."
                            textFieldText: outputControllerWfesSequential.ui_get_t_tmo_std
                            readOnly: true
                        }

                    }

                    Button {
                        text: "Copy to Clipboard"

                        Layout.alignment: Qt.AlignHCenter

                        onClicked: {
                            outputControllerWfesSequential.coppyToClipboard()
                        }
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
            value: !outputControllerWfesSequential.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfesSequential.ui_progress

            executionTime: {
                outputControllerWfesSequential.ui_get_time == "" ? "" : outputControllerWfesSequential.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }
    }

    function updateGUI() {
        inputA.textFieldText = inputControllerWfesSequential.ui_a
        inputC.textFieldText = inputControllerWfesSequential.ui_c

        var N_vec = inputControllerWfesSequential.ui_N_vec
        var t_vec = inputControllerWfesSequential.ui_t_vec
        var p_vec = inputControllerWfesSequential.ui_p_vec
        var u_vec = inputControllerWfesSequential.ui_u_vec
        var v_vec = inputControllerWfesSequential.ui_v_vec
        var s_vec = inputControllerWfesSequential.ui_s_vec
        var h_vec = inputControllerWfesSequential.ui_h_vec

        // Minus 2 because we don't have to count the add and delete tabs.
        // If the number of current tabs is less than the number of components to load,
        // add a tab.
        if(componentsSectionTabView.children[0].count - 2 < inputControllerWfesSequential.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 < inputControllerWfesSequential.ui_num_comp) {
                // Create new tab.
                componentsSectionTabView.children[0].addTab()
                // Don't update ui_num_comp
                inputControllerWfesSequential.ui_num_comp = inputControllerWfesSequential.ui_num_comp - 1
            }
        // If the number of current tabs is greater than the number of components to load,
        // remove a tab.
        } else if(componentsSectionTabView.children[0].count - 2 > inputControllerWfesSequential.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 > inputControllerWfesSequential.ui_num_comp) {
                // Delete a tab.
                componentsSectionTabView.children[0].deleteTab()
                // Don't update ui_num_comp
                inputControllerWfesSequential.ui_num_comp = parseInt(inputControllerWfesSequential.ui_num_comp) + 1
            }
        }

        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText = N_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText = t_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText = p_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText = h_vec[i]
        }
        inputWriteQ.checked = inputControllerWfesSequential.ui_output_Q
        inputWriteR.checked = inputControllerWfesSequential.ui_output_R
        inputWriteN.checked = inputControllerWfesSequential.ui_output_N
        inputWriteB.checked = inputControllerWfesSequential.ui_output_B
        inputWriteNExt.checked = inputControllerWfesSequential.ui_output_N_Ext
        inputWriteNFix.checked = inputControllerWfesSequential.ui_output_N_Fix
        inputWriteNTmo.checked = inputControllerWfesSequential.ui_output_N_Tmo
        inputWriteRes.checked = inputControllerWfesSequential.ui_output_Res
        inputT.textFieldText = inputControllerWfesSequential.ui_t
        inputForce.checked = inputControllerWfesSequential.ui_force

        //inputI.textFieldText = inputControllerWfesSequential.ui_initial_distribution

        var library = inputControllerWfesSequential.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfesSequential.ui_solver
        if(solver === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(solver === "BicGStab")
            comboBoxSolver.currentIndex = 1

        // Update boxes.
        for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
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

    function updateBackend(){
        inputControllerWfesSequential.ui_a = inputA.textFieldText
        inputControllerWfesSequential.ui_c = inputC.textFieldText
        var N_vec = []
        var t_vec = []
        var p_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var t = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var p = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            t_vec.push(t)
            p_vec.push(p)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerWfesSequential.ui_N_vec = N_vec
        inputControllerWfesSequential.ui_t_vec = t_vec
        inputControllerWfesSequential.ui_p_vec = p_vec
        inputControllerWfesSequential.ui_u_vec = u_vec
        inputControllerWfesSequential.ui_v_vec = v_vec
        inputControllerWfesSequential.ui_s_vec = s_vec
        inputControllerWfesSequential.ui_h_vec = h_vec

        inputControllerWfesSequential.ui_output_Q = inputWriteQ.checked
        inputControllerWfesSequential.ui_output_R = inputWriteR.checked
        inputControllerWfesSequential.ui_output_N = inputWriteN.checked
        inputControllerWfesSequential.ui_output_B = inputWriteB.checked
        inputControllerWfesSequential.ui_output_N_Ext = inputWriteNExt.checked
        inputControllerWfesSequential.ui_output_N_Fix = inputWriteNFix.checked
        inputControllerWfesSequential.ui_output_N_Tmo = inputWriteNTmo.checked
        inputControllerWfesSequential.ui_output_Res = inputWriteRes.checked
        inputControllerWfesSequential.ui_t = inputT.textFieldText
        inputControllerWfesSequential.ui_force = inputForce.checked

        //inputControllerWfesSequential.ui_initial_distribution = inputI.textFieldText

        inputControllerWfesSequential.ui_library = comboBoxLibrary.currentText;
        inputControllerWfesSequential.ui_solver = comboBoxSolver.currentText;
    }

    function checkIntegrity() {
        var error = ""

        if(inputA.textFieldText == "")
            error += " - Tail Truncation Cutoff (a) is empty. \n \n"
        if(Number.isNaN(Number(inputA.textFieldText)))
            error += " - Tail Truncation Cutoff (a) is not a valid number. \n \n"
        if(parseFloat(inputA.textFieldText) < 0)
            error += " - Tail Truncation Cutoff (a) is quite small. It must be at least 0. \n \n"
        if(!inputForce.checked && parseFloat(inputA.textFieldText) > 1e-5)
            error += " - Tail Truncation Cutoff (a) value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore. \n \n"

        if(inputC.textFieldText == "")
            error += " - Integration Cutoff (c) is empty. \n \n"
        if(Number.isNaN(Number(inputC.textFieldText)))
            error += " - Integration Cutoff (c) is not a valid number. \n \n"
        if(parseFloat(inputC.textFieldText) < 0)
            error += " - Integration Cutoff (c) is quite small. It must be at least 0. \n \n"
        if(parseFloat(inputC.textFieldText) > 10e-3)
            error += " - Integration Cutoff (c) is quite large. The maximum value allowed is 10e-3. \n \n"

        var N_vec = []
        var t_vec = []
        var p_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var t = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var p = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            t_vec.push(t)
            p_vec.push(p)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }

        for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            if(N === "")
                error += " - Population Size (N" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(N_vec[i])))
                error += " - Population Size (N" + (i + 1) + ") is not a valid number. \n \n"
            if(parseInt(N_vec[i]) < 2)
                error += " - Population Size (N" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(N_vec[i]) > 50000)
                error +=  " - Population Size (N" + (i + 1) + ") is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"
        }

        for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            t = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            if(t === "")
                error += " - Expected Time (t" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(t_vec[i])))
                error += " - Expected Time (t" + (i + 1) + ") is not a valid number. \n \n"
            if(parseInt(t_vec[i]) < 1)
                error += " - Expected Time (t" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
            // No upper limit for this.
        }


        for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            p = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            if(p === "")
                error += " - Probability of starting (p" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(p_vec[i])))
                error += " - Probability of starting (p" + (i + 1) + ") is not a valid number. \n \n"
            if(parseInt(p_vec[i]) < 0)
                error += " - Probability of starting (p" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
            if(parseInt(p_vec[i]) > 1)
                error += " - Probability of starting (p" + (i + 1) + ") is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"
        }

        if(globalConfiguration.ui_population_scaled) {
            for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
                if(u === "")
                    error += " - Backward Mutation (u" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(u_vec[i])))
                    error += " - Backward Mutation (u" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(u_vec[i].textFieldText) <= 0)
                    error += " - Backward Mutation (u" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && parseFloat(u_vec[i]) > 1)
                    error += " - Backward Mutation (u" + (i + 1) + ") is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
                if(v === "")
                    error += " - Forward Mutation (v" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(v_vec[i])))
                    error += " - Forward Mutation (v" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(v_vec[i].textFieldText) <= 0)
                    error += " - Forward Mutation (v" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && parseFloat(v_vec[i]) > 1)
                    error += " - Forward Mutation (v" + (i + 1) + ") is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
                if(s === "")
                    error += " - Selection Coefficient (s" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(s_vec[i])))
                    error += " - Selection Coefficient (s" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(s_vec[i]) < -1 * (2 * parseInt(N_vec[i])))
                    error += " - Selection Coefficient (s" + (i + 1) + ") is quite negative. It must be at least -2N \n \n"
                if(parseFloat(s_vec[i]) > 1 * (2 * parseInt(N_vec[i])))
                    error += " - Selection Coefficient (s" + (i + 1) + ") is quite large. The maximum value allowed is 2N. \n \n"
            }
        } else {
            for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
                if(u === "")
                    error += " - Backward Mutation (u" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(u_vec[i])))
                    error += " - Backward Mutation (u" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(u_vec[i].textFieldText) <= 0)
                    error += " - Backward Mutation (u" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && parseFloat(u_vec[i]) > 1 / (4 * parseInt(N_vec[i])))
                    error += " - Backward Mutation (u" + (i + 1) + ") is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
                if(v === "")
                    error += " - Forward Mutation (v" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(v_vec[i])))
                    error += " - Forward Mutation (v" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(v_vec[i].textFieldText) <= 0)
                    error += " - Backward Mutation (v" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && parseFloat(v_vec[i]) > 1 / (4 * parseInt(N_vec[i])))
                    error += " - Backward Mutation (v" + (i + 1) + ") is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
                if(s === "")
                    error += " - Selection Coefficient (s" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(s_vec[i])))
                    error += " - Selection Coefficient (s" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(s_vec[i]) < -1)
                    error += " - Selection Coefficient (s" + (i + 1) + ") is quite negative. It must be at least -2N \n \n"
                if(parseFloat(s_vec[i]) > 1 )
                    error += " - Selection Coefficient (s" + (i + 1) + ") is quite large. The maximum value allowed is 2N. \n \n"
            }
        }


        for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            if(h === "")
                error += " - Dominance Coefficient (h" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(h_vec[i])))
                error += " - Dominance Coefficient (h" + (i + 1) + ") is not a valid number. \n \n"
            if(parseFloat(h_vec[i]) < 0)
                error += " - Dominance Coefficient (h" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
            if(parseFloat(h_vec[i]) > 1)
                error += " - Dominance Coefficient (h" + (i + 1) + ") is quite large. The maximum value allowed is 1. \n \n"
        }

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
        var loadedComponents = true
        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
            if(typeof(componentsSectionTabView.children[0].getTab(i)) === "undefined") {
                loadedComponents = false
            }
        }
        if(loadedComponents) {
            var u, v, s
            var u_vec, v_vec, s_vec = []
            if(globalConfiguration.ui_population_scaled) {
                u = inputControllerWfesSequential.ui_u_vec
                v = inputControllerWfesSequential.ui_v_vec
                s = inputControllerWfesSequential.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] * (4 * parseInt(inputControllerWfesSequential.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] * (4 * parseInt(inputControllerWfesSequential.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] * (2 * parseInt(inputControllerWfesSequential.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfesSequential.ui_u_vec = u_vec
                inputControllerWfesSequential.ui_v_vec = v_vec
                inputControllerWfesSequential.ui_s_vec = s_vec


            } else if(updateNonChecked){
                u = inputControllerWfesSequential.ui_u_vec
                v = inputControllerWfesSequential.ui_v_vec
                s = inputControllerWfesSequential.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] / (4 * parseInt(inputControllerWfesSequential.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] / (4 * parseInt(inputControllerWfesSequential.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] / (2 * parseInt(inputControllerWfesSequential.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfesSequential.ui_u_vec = u_vec
                inputControllerWfesSequential.ui_v_vec = v_vec
                inputControllerWfesSequential.ui_s_vec = s_vec

            }
        }
    }
}
