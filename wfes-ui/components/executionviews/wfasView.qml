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
    id: rootWfas
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFAF-S)")

    color: Universal.chromeLowColor

    visible: false

    width: 895
    minimumWidth: 895
    maximumWidth: 895
    height: 485
    minimumHeight: 485
    maximumHeight: 485

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootWfas.hide();
        root.visible = true;
        rootWfas.updateBackend()
        outputControllerWfas.ui_save_config
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
                            onLoaded: function() {
                                var dummyString = outputControllerWfas.ui_load_config
                                rootWfas.updateGUI()
                            }

                            urlComponent: "qrc:/components/executionviews/tabcomponents/tabWfasComponent.qml"
                            onAdd: function(){
                                var num_comps = inputControllerWfas.ui_num_comp
                                inputControllerWfas.ui_num_comp = parseInt(num_comps) + 1

                                var vector = inputControllerWfas.ui_N_vec
                                vector[num_comps] = inputControllerWfas.ui_N_vec[num_comps-1]
                                inputControllerWfas.ui_N_vec = vector

                                vector = inputControllerWfas.ui_G_vec
                                vector[num_comps] = inputControllerWfas.ui_G_vec[num_comps-1]
                                inputControllerWfas.ui_G_vec = vector

                                vector = inputControllerWfas.ui_f_vec
                                vector[num_comps] = inputControllerWfas.ui_f_vec[num_comps-1]
                                inputControllerWfas.ui_f_vec = vector

                                vector = inputControllerWfas.ui_s_vec
                                vector[num_comps] = inputControllerWfas.ui_s_vec[num_comps-1]
                                inputControllerWfas.ui_s_vec = vector

                                vector = inputControllerWfas.ui_h_vec
                                vector[num_comps] = inputControllerWfas.ui_h_vec[num_comps-1]
                                inputControllerWfas.ui_h_vec = vector

                                vector = inputControllerWfas.ui_u_vec
                                vector[num_comps] = inputControllerWfas.ui_u_vec[num_comps-1]
                                inputControllerWfas.ui_u_vec = vector

                                vector = inputControllerWfas.ui_v_vec
                                vector[num_comps] = inputControllerWfas.ui_v_vec[num_comps-1]
                                inputControllerWfas.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfas.ui_num_comp
                                inputControllerWfas.ui_num_comp = parseInt(num_comps) - 1
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
                                textFieldText: inputControllerWfas.ui_a
                            }

                            LabeledTextField {
                                id: inputP
                                text: "p: "
                                toolTipText: "Initial allele count."
                                validator: IntValidator {bottom: 0; top: 2;}
                                textFieldText: inputControllerWfas.ui_p
                            }

                            LabeledCheckBox {
                                id: inputNoProject
                                text: "No Proj.: "
                                toolTipText: "Do not project the distribution down."
                                checked: inputControllerWfas.ui_no_proj
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
                        Layout.margins: 10
                        Layout.alignment: Qt.AlignTop

                        ColumnLayout {
                            Layout.alignment: Qt.AlignTop
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
                                        checked: inputControllerWfas.ui_output_Q
                                    }
                                    // TODO Not implemented in original code.
                                    /*
                                    LabeledCheckBox {
                                        id: inputWriteR
                                        text: "R: "
                                        toolTipText: "Output R vectors to file."
                                        checked: inputControllerWfas.ui_output_R
                                    }

                                   LabeledCheckBox {
                                        id: inputWriteN
                                        text: "N: "
                                        toolTipText: "Output N matrix to file."
                                        checked: inputControllerWfas.ui_output_N
                                    }*/

                                    LabeledCheckBox {
                                        id: inputWriteB
                                        text: "B: "
                                        toolTipText: "Output B vectors to file."
                                        checked: inputControllerWfas.ui_output_B
                                    }

                                    // TODO Not implemented in original code.
                                    /*LabeledCheckBox {
                                        id: inputWriteNExt
                                        text: "N Ext.: "
                                        toolTipText: "Output extinction-conditional sojourn to file."
                                        checked: inputControllerWfas.ui_output_N_Ext
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteNFix
                                        text: "N Fix.: "
                                        toolTipText: "Output fixation-conditional sojourn to file."
                                        checked: inputControllerWfas.ui_output_N_Fix
                                    }
                                    LabeledCheckBox {
                                        id: inputWriteNTmo
                                        text: "N Tmo.: "
                                        toolTipText: "Output timeout-conditional sojourn to file."
                                        checked: inputControllerWfas.ui_output_N_Tmo
                                    }*/

                                    Label {
                                        // Empty, so Res is always at right.
                                    }

                                    LabeledCheckBox {
                                        id: inputWriteDist
                                        enabled: true
                                        enabledCheckBox: false
                                        text: "Dist: "
                                        toolTipText: "Output Allele freq. dist. as CSV file. (Always enabled)."
                                        checked: true
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
                                            checked: inputControllerWfas.ui_force
                                        }

                                        LabeledTextField {
                                            id: inputT
                                            text: "t: "
                                            labelPreferredWidth: 10
                                            toolTipText: "Number of threads for OpenMP."
                                            validator: DoubleValidator {bottom: 1;}
                                            textFieldText: inputControllerWfas.ui_t
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
                                            textFieldText: inputControllerWfas.ui_initial_distribution
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
                                    value: !outputControllerWfas.ui_get_not_exec

                                }

                                onClicked: {
                                    outputControllerWfas.ui_stop
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
                                    if(outputControllerWfas.ui_get_not_exec)
                                        imageOutputController.image_changed()
                                    console.log(outputControllerWfas.ui_get_error_message)
                                    if(outputControllerWfas.ui_get_error_message !== "") {
                                        messageDialog.text = outputControllerWfas.ui_get_error_message
                                        messageDialog.open()
                                        outputControllerWfas.ui_reset_error
                                    }
                                    upperMenu.updateDistWfas()
                                }

                                Binding {
                                    target: executeButton
                                    property: "enabled"
                                    value: outputControllerWfas.ui_get_not_exec

                                }

                                // All changes made in backend from GUI are done here.
                                onClicked: {
                                    var error = checkIntegrity()

                                    updateBackend()

                                    if(error === "") {
                                        executeButton.enabled = false
                                        stopButton.enabled = true
                                        bottomMenu.visibleProgressBar = true
                                        outputControllerWfas.ui_execute
                                    } else {
                                        messageDialog.text = error
                                        messageDialog.open()
                                    }
                                    outputControllerWfas.ui_reset_error
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
                        id: labelMoments
                        text: "Output:"
                        font.bold: true
                    }

                    Label {
                        id: labelMoments2
                        text: "Allele freq. dist.:"
                    }

                    Rectangle {
                        width: labelMoments.width * 4
                        height: childrenRect.height + 1
                        color: "transparent"
                        border.width: 1

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
                            contentWidth: parent.width
                            ListView {
                                id: listViewMoments
                                model: outputControllerWfas.ui_probs
                                delegate: ItemDelegate {
                                  width: parent.width
                                  height: 25
                                  Text {
                                      text: modelData;
                                      width: parent.width;
                                      height: parent.height;
                                  }
                                }
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
            }
        }

        Binding {
            target: bottomMenu
            property: "visibleProgressBar"
            value: !outputControllerWfas.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfas.ui_progress

            executionTime: {
                outputControllerWfas.ui_get_time == "" ? "" : outputControllerWfas.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }


    }


    function updateGUI() {
        inputA.textFieldText = inputControllerWfas.ui_a
        inputP.textFieldText = inputControllerWfas.ui_p
        inputNoProject.checked = inputControllerWfas.ui_no_proj

        var N_vec = inputControllerWfas.ui_N_vec
        var G_vec = inputControllerWfas.ui_G_vec
        var f_vec = inputControllerWfas.ui_f_vec
        var u_vec = inputControllerWfas.ui_u_vec
        var v_vec = inputControllerWfas.ui_v_vec
        var s_vec = inputControllerWfas.ui_s_vec
        var h_vec = inputControllerWfas.ui_h_vec

        // Minus 2 because we don't have to count the add and delete tabs.
        // If the number of current tabs is less than the number of components to load,
        // add a tab.
        if(componentsSectionTabView.children[0].count - 2 < inputControllerWfas.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 < inputControllerWfas.ui_num_comp) {
                // Create new tab.
                componentsSectionTabView.children[0].addTab()
                // Don't update ui_num_comp
                inputControllerWfas.ui_num_comp = inputControllerWfas.ui_num_comp - 1
            }
        // If the number of current tabs is greater than the number of components to load,
        // remove a tab.
        } else if(componentsSectionTabView.children[0].count - 2 > inputControllerWfas.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 > inputControllerWfas.ui_num_comp) {
                // Delete a tab.
                componentsSectionTabView.children[0].deleteTab()
                // Don't update ui_num_comp
                inputControllerWfas.ui_num_comp = parseInt(inputControllerWfas.ui_num_comp) + 1
            }
        }

        for(var i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText = N_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText = G_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText = f_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText = h_vec[i]
        }
        inputWriteQ.checked = inputControllerWfas.ui_output_Q
        //inputWriteR.checked = inputControllerWfas.ui_output_R
        //inputWriteN.checked = inputControllerWfas.ui_output_N
        inputWriteB.checked = inputControllerWfas.ui_output_B
        //inputControllerWfas.ui_output_N_Ext = inputWriteNExt.checked
        //inputWriteNFix.checked = inputControllerWfas.ui_output_N_Fix
        //inputWriteNTmo.checked = inputControllerWfas.ui_output_N_Tmo
        inputWriteDist.checked = inputControllerWfas.ui_output_Dist
        inputT.textFieldText = inputControllerWfas.ui_t
        inputForce.checked = inputControllerWfas.ui_force

        inputI.textFieldText = inputControllerWfas.ui_initial_distribution

        var library = inputControllerWfas.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfas.ui_solver
        if(library === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(library === "BicGStab")
            comboBoxSolver.currentIndex = 1
    }

    function updateBackend() {
        inputControllerWfas.ui_a = inputA.textFieldText
        inputControllerWfas.ui_p = inputP.textFieldText
        inputControllerWfas.ui_no_proj = inputNoProject.checked
        var N_vec = []
        var G_vec = []
        var f_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var f = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            G_vec.push(G)
            f_vec.push(f)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerWfas.ui_N_vec = N_vec
        inputControllerWfas.ui_G_vec = G_vec
        inputControllerWfas.ui_f_vec = f_vec
        inputControllerWfas.ui_u_vec = u_vec
        inputControllerWfas.ui_v_vec = v_vec
        inputControllerWfas.ui_s_vec = s_vec
        inputControllerWfas.ui_h_vec = h_vec

        inputControllerWfas.ui_output_Q = inputWriteQ.checked
        //inputControllerWfas.ui_output_R = inputWriteR.checked
        //inputControllerWfas.ui_output_N = inputWriteN.checked
        inputControllerWfas.ui_output_B = inputWriteB.checked
        //inputControllerWfas.ui_output_N_Ext = inputWriteNExt.checked
        //inputControllerWfas.ui_output_N_Fix = inputWriteNFix.checked
        //inputControllerWfas.ui_output_N_Tmo = inputWriteNTmo.checked
        inputControllerWfas.ui_output_Dist = inputWriteDist.checked
        inputControllerWfas.ui_t = inputT.textFieldText
        inputControllerWfas.ui_force = inputForce.checked

        inputControllerWfas.ui_initial_distribution = inputI.textFieldText

        inputControllerWfas.ui_library = comboBoxLibrary.currentText;
        inputControllerWfas.ui_solver = comboBoxSolver.currentText;

    }

    function checkIntegrity() {
        var error = ""

        if(parseFloat(inputA.textFieldText) < 0)
            error += " - Tail Truncation Cutoff (a) is quite small. It must be at least 0. \n \n"
        if(!inputForce.checked && parseFloat(inputA.textFieldText) > 1e-5)
            error += " - Tail Truncation Cutoff (a) value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore. \n \n"

        if(parseInt(inputP.textFieldText) < 0)
            error += " - Initial Allele Count (p) is quite small. It must be at least 0. \n \n"
        if(!inputForce.checked && parseInt(inputP.textFieldText) > 2)
            error += " - Initial Allele Count (p) value is quite high. The maximum value allowed is 2. \n \n"

        var N_vec = []
        var G_vec = []
        var f_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var f = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            G_vec.push(G)
            f_vec.push(f)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseInt(N_vec[i]) < 2)
                error += " - Population Size (N" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(N_vec[i]) > 50000)
                error +=  " - Population Size (N" + (i + 1) + ") is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseInt(G_vec[i]) < 0)
                error += " - Generations (G" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseInt(f_vec[i]) < 1)
                error += " - Approximation Factor (f" + (i + 1) + ") is quite small, it must be at least 1. \n \n"
            if(parseInt(f_vec[i]) > N_vec[i])
                error +=  " - Approximation Factor (f" + (i + 1) + ") is quite large. The maximum value allowed is N. \n \n"
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseFloat(u_vec[i]) < 0)
                error += " - Backward Mutation (u" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && (4 * parseInt(N_vec[i]) * parseFloat(u_vec[i])) > 1)
                error += " - Backward Mutation (u" + (i + 1) + ") is quite large and might violate the Wright-Fisher assumptions. Check 'Force' to ignore. \n \n"
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseFloat(v_vec[i]) < 0)
                error += " - Forward Mutation (v" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
            if(!inputForce.checked && (4 * parseInt(N_vec[i]) * parseFloat(v_vec[i])) > 1)
                error += " - Forward Mutation (v" + (i + 1) + ") is quite large and might violate the Wright-Fisher assumptions. Check 'Force' to ignore. \n \n"
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseFloat(s_vec[i]) < -1)
                error += " - Selection Coefficient (s" + (i + 1) + ") is quite negative. Fixations might be impossible. It must be at least -1. \n \n"
            if(parseFloat(s_vec[i]) > 1)
                error += " - Selection Coefficient (s" + (i + 1) + ") is quite large. The maximum value allowed is 1. \n \n"
            if(parseFloat(s_vec[i]) * 2 * parseInt(N_vec[i]) <= -100) {
                error += " - Selection Coefficient (s" + (i + 1) + ") is quite negative. Fixations might be impossible. It must be at least -1. \n \n"
            }
        }

        for(i = 0; i < inputControllerWfas.ui_num_comp; i++) {
            if(parseFloat(h_vec[i]) < 0)
                error += " - Dominance Coefficient (h" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
            if(parseFloat(h_vec[i]) > 1)
                error += " - Dominance Coefficient (h" + (i + 1) + ") is quite large. The maximum value allowed is 1. \n \n"
        }

        // Number of threads (t) does not have upper limites, since it depends on the hardware available.
        if(parseInt(inputT.textFieldText) < 1)
            error += " - Number of Threads (t) is quite small, it must be at least 1. \n \n"

        //TODO Check if Initial Distribution (I) file exists.

        return error.split("\n \n")[0];


    }
}