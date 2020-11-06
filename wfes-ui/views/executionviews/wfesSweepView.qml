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
    id: rootWfesSweep
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFES Sweep)")

    color: Universal.chromeLowColor

    visible: true

    width: 955
    minimumWidth: 955
    maximumWidth: 955
    height: 490
    minimumHeight: 490
    maximumHeight: 490

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootWfesSweep.destroy();
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
                            columns: 2
                            anchors {
                                top: labelModel.bottom
                                left: parent.left
                                margins: 10
                            }
                            RadioButton {
                                id: radioButtonFixation
                                checked: true
                                text: qsTr("Fixation")

                                ToolTip.visible: hovered
                                ToolTip.delay: 1000
                                ToolTip.timeout: 5000
                                ToolTip.text: qsTr("Only fixation state is absorbing.")

                                onCheckedChanged: {

                                }
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: componentsSection.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: componentsSection
                        width: commonSection.width + 10
                        height: childrenRect.height

                        color: "transparent"

                        Layout.alignment: Qt.AlignTop

                        TabView {
                            id: componentsSectionTabView
                            width: parent.width
                            height: 170
                            Tab {
                                id: comp1
                                title: "Comp. 1"
                                height: parent.height
                                GridLayout {
                                    id: tabGrid1
                                    columns: 1
                                    anchors {
                                        top: parent.top
                                        left: parent.left
                                    }

                                    Rectangle {
                                        id: mutationSection1
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"


                                        Label {
                                            id: labelMutation1
                                            text: "Mutation:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: mutationSectionGrid1
                                            columns: 4
                                            anchors {
                                                top: labelMutation1.bottom
                                                left: parent.left
                                                margins: 10
                                            }

                                            LabeledTextField {
                                                id: inputU1
                                                text: "u1: "
                                                toolTipText: "Backward mutation rate."
                                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                                textFieldText: {
                                                    var u_vec = inputControllerWfesSweep.ui_u_vec
                                                    return u_vec[0]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputV1
                                                text: "v1: "
                                                toolTipText: "Forward mutation rate."
                                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                                textFieldText: {
                                                    var v_vec = inputControllerWfesSweep.ui_v_vec
                                                    return v_vec[0]
                                                }
                                            }


                                        }
                                    }


                                    Rectangle {
                                        id: selectionSection1
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"


                                        Label {
                                            id: labelSelection1
                                            text: "Selection:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: selectionSectionGrid1
                                            columns: 4
                                            anchors {
                                                top: labelSelection1.bottom
                                                left: parent.left
                                                margins: 10
                                            }

                                            LabeledTextField {
                                                id: inputS1
                                                text: "s1: "
                                                toolTipText: "Selection coefficient."
                                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                                textFieldText: {
                                                    var s_vec = inputControllerWfesSweep.ui_s_vec
                                                    return s_vec[0]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH1
                                                text: "h1: "
                                                toolTipText: "Dominance coefficient."
                                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                                textFieldText: {
                                                    var h_vec = inputControllerWfesSweep.ui_h_vec
                                                    return h_vec[0]
                                                }
                                            }


                                        }
                                    }
                                }
                            }

                            Tab {
                                id: comp2
                                title: "Comp. 2"
                                height: parent.height
                                GridLayout {
                                    id: tabGrid2
                                    columns: 1
                                    anchors {
                                        top: parent.top
                                        left: parent.left
                                    }

                                    Rectangle {
                                        id: mutationSection2
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"


                                        Label {
                                            id: labelMutation2
                                            text: "Mutation:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: mutationSectionGrid2
                                            columns: 4
                                            anchors {
                                                top: labelMutation2.bottom
                                                left: parent.left
                                                margins: 10
                                            }

                                            LabeledTextField {
                                                id: inputU2
                                                text: "u2: "
                                                toolTipText: "Backward mutation rate."
                                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                                textFieldText: {
                                                    var u_vec = inputControllerWfesSweep.ui_u_vec
                                                    return u_vec[1]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputV2
                                                text: "v2: "
                                                toolTipText: "Forward mutation rate."
                                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                                textFieldText: {
                                                    var v_vec = inputControllerWfesSweep.ui_v_vec
                                                    return v_vec[1]
                                                }
                                            }


                                        }
                                    }


                                    Rectangle {
                                        id: selectionSection2
                                        width: parent.width
                                        height: childrenRect.height

                                        color: "transparent"


                                        Label {
                                            id: labelSelection2
                                            text: "Selection:"
                                            anchors {
                                                left: parent.left
                                                margins: {
                                                    left: 5
                                                }
                                            }
                                        }

                                        GridLayout {
                                            id: selectionSectionGrid2
                                            columns: 4
                                            anchors {
                                                top: labelSelection2.bottom
                                                left: parent.left
                                                margins: 10
                                            }

                                            LabeledTextField {
                                                id: inputS2
                                                text: "s2: "
                                                toolTipText: "Selection coefficient."
                                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                                textFieldText: {
                                                    var s_vec = inputControllerWfesSweep.ui_s_vec
                                                    return s_vec[1]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH2
                                                text: "h2: "
                                                toolTipText: "Dominance coefficient."
                                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                                textFieldText: {
                                                    var h_vec = inputControllerWfesSweep.ui_h_vec
                                                    return h_vec[1]
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
                        width: commonSection.width
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
                                id: inputN
                                text: "N: "
                                toolTipText: "Size of the population in the Wright Fisher Model."
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputControllerWfesSweep.ui_n
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSweep.ui_a
                            }

                            LabeledTextField {
                                id: inputL
                                text: "l: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSweep.ui_l
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSweep.ui_c
                            }

                            LabeledTextField {
                                id: inputP
                                text: "p: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfesSweep.ui_c
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
                                    checked: inputControllerWfesSweep.ui_output_Q

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: "R: "
                                    toolTipText: "Output R as CSV file."
                                    checked: inputControllerWfesSweep.ui_output_R
                                }

                                LabeledCheckBox {
                                    id: inputWriteB
                                    text: "B: "
                                    toolTipText: "Output B as CSV file."
                                    checked: inputControllerWfesSweep.ui_output_B
                                }

                                LabeledCheckBox {
                                    id: inputWriteN
                                    text: "N: "
                                    toolTipText: "Output N as CSV file."
                                    checked: inputControllerWfesSweep.ui_output_N
                                }

                                LabeledCheckBox {
                                    id: inputWriteI
                                    text: "I: "
                                    toolTipText: "Output I (Initial probability distribution) as CSV file."
                                    checked: inputControllerWfesSweep.ui_output_I
                                }

                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: "Res: "
                                    toolTipText: "Output Res (Generated results at right side) as CSV file."
                                    checked: inputControllerWfesSweep.ui_output_Res
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
                                        checked: inputControllerWfesSweep.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        labelPreferredWidth: 10
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputControllerWfesSweep.ui_t
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
                                        textFieldText: inputControllerWfesSweep.ui_initial_distribution
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
                                value: !outputControllerWfesSweep.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerWfesSweep.ui_stop
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
                                if(outputControllerWfesSweep.ui_get_not_exec)
                                    imageOutputController.image_changed()
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerWfesSweep.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                bottomMenu.visibleProgressBar = true

                                updateBackend()

                                console.log(outputControllerWfesSweep.ui_get_error_message)
                                if(outputControllerWfesSweep.ui_get_error_message === "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    outputControllerWfesSweep.ui_execute
                                } else {
                                    messageDialog.text = outputControllerWfesSweep.ui_get_error_message
                                    messageDialog.open()
                                }
                                outputControllerWfesSweep.ui_reset_error
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
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T fix.: "
                                toolTipText: "Fixation time."
                                textFieldText: outputControllerWfesSweep.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Rate: "
                                toolTipText: "Rate."
                                textFieldText: outputControllerWfesSweep.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }
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
                topMargin: 30
            }
        }

        Binding {
            target: bottomMenu
            property: "visibleProgressBar"
            value: !outputControllerWfesSweep.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfesSweep.ui_progress

            executionTime: {
                outputControllerWfesSweep.ui_get_time == "" ? "" : outputControllerWfesSweep.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }

    }

    function updateGUI() {
        radioButtonFixation.checked = inputControllerWfesSweep.ui_modelType == "Fixation"

        inputN.textFieldText = inputControllerWfesSweep.ui_n
        inputA.textFieldText = inputControllerWfesSweep.ui_a
        inputL.textFieldText = inputControllerWfesSweep.ui_l
        inputC.textFieldText = inputControllerWfesSweep.ui_c
        inputP.textFieldText = inputControllerWfesSweep.ui_p

        var u_vec = inputControllerWfesSweep.ui_u_vec
        var v_vec = inputControllerWfesSweep.ui_v_vec
        var s_vec = inputControllerWfesSweep.ui_s_vec
        var h_vec = inputControllerWfesSweep.ui_h_vec
        for(var i = 0; i < 2; i++) {
            componentsSectionTabView.getTab(i).active = true
            componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
            componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
            componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
            componentsSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText = h_vec[i]
        }
        inputWriteQ.checked = inputControllerWfesSweep.ui_output_Q
        inputWriteR.checked = inputControllerWfesSweep.ui_output_R
        inputWriteB.checked = inputControllerWfesSweep.ui_output_B
        inputWriteN.checked = inputControllerWfesSweep.ui_output_N
        inputWriteI.checked = inputControllerWfesSweep.ui_output_I
        inputWriteRes.checked = inputControllerWfesSweep.ui_output_Res

        inputT.textFieldText = inputControllerWfesSweep.ui_t
        inputForce.checked = inputControllerWfesSweep.ui_force

        inputI.textFieldText = inputControllerWfesSweep.ui_initial_distribution

        var library = inputControllerWfesSweep.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfesSweep.ui_solver
        if(solver === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(solver === "BicGStab")
            comboBoxSolver.currentIndex = 1

    }

    function updateBackend() {
        if (radioButtonFixation.checked)
            outputControllerWfesSweep.ui_modelType = "Fixation"

        inputControllerWfesSweep.ui_n = inputN.textFieldText
        inputControllerWfesSweep.ui_a = inputA.textFieldText
        inputControllerWfesSweep.ui_l = inputL.textFieldText
        inputControllerWfesSweep.ui_c = inputC.textFieldText
        inputControllerWfesSweep.ui_p = inputP.textFieldText
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < 2; i++) {
            componentsSectionTabView.getTab(i).active = true
            var u = componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
            var v = componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
            var s = componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
            var h = componentsSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerWfesSweep.ui_u_vec = u_vec
        inputControllerWfesSweep.ui_v_vec = v_vec
        inputControllerWfesSweep.ui_s_vec = s_vec
        inputControllerWfesSweep.ui_h_vec = h_vec

        inputControllerWfesSweep.ui_output_Q = inputWriteQ.checked
        inputControllerWfesSweep.ui_output_R = inputWriteR.checked
        inputControllerWfesSweep.ui_output_B = inputWriteB.checked
        inputControllerWfesSweep.ui_output_N = inputWriteN.checked
        inputControllerWfesSweep.ui_output_I = inputWriteI.checked
        inputControllerWfesSweep.ui_output_Res = inputWriteRes.checked

        inputControllerWfesSweep.ui_t = inputT.textFieldText
        inputControllerWfesSweep.ui_library = comboBoxLibrary.currentText;
        inputControllerWfesSweep.ui_solver = comboBoxSolver.currentText;
        inputControllerWfesSweep.ui_force = inputForce.checked

        inputControllerWfesSweep.ui_initial_distribution = inputI.textFieldText

    }

}
