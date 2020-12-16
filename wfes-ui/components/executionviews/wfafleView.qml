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
    id: rootWfafle
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFAF-D)")

    color: Universal.chromeLowColor

    visible: false

    width: 890
    minimumWidth: 890
    maximumWidth: 890
    height: 445
    minimumHeight: 445
    maximumHeight: 445

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = "Some input parameters are incorrect. The configuration will be available in this session, but cannot be saved for future sessions until you fix those values. Do you want to exit anyway?"
            messageDialogOnClose.open()
        } else {
            rootWfafle.hide();
            root.visible = true;
            rootWfafle.updateBackend()
            outputControllerWfafle.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: "Warning"
        text: ""
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfafle.hide();
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
                            urlComponent: "qrc:/components/executionviews/tabcomponents/tabWfafleComponent.qml"
                            onAdd: function(){
                                var num_comps = inputControllerWfafle.ui_num_comp
                                inputControllerWfafle.ui_num_comp = parseInt(num_comps) + 1

                                var vector = inputControllerWfafle.ui_N_vec
                                vector[num_comps] = inputControllerWfafle.ui_N_vec[num_comps-1]
                                inputControllerWfafle.ui_N_vec = vector

                                vector = inputControllerWfafle.ui_G_vec
                                vector[num_comps] = inputControllerWfafle.ui_G_vec[num_comps-1]
                                inputControllerWfafle.ui_G_vec = vector

                                vector = inputControllerWfafle.ui_s_vec
                                vector[num_comps] = inputControllerWfafle.ui_s_vec[num_comps-1]
                                inputControllerWfafle.ui_s_vec = vector

                                vector = inputControllerWfafle.ui_h_vec
                                vector[num_comps] = inputControllerWfafle.ui_h_vec[num_comps-1]
                                inputControllerWfafle.ui_h_vec = vector

                                vector = inputControllerWfafle.ui_u_vec
                                vector[num_comps] = inputControllerWfafle.ui_u_vec[num_comps-1]
                                inputControllerWfafle.ui_u_vec = vector

                                vector = inputControllerWfafle.ui_v_vec
                                vector[num_comps] = inputControllerWfafle.ui_v_vec[num_comps-1]
                                inputControllerWfafle.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfafle.ui_num_comp
                                inputControllerWfafle.ui_num_comp = parseInt(num_comps) - 1
                            }
                            onLoaded: function() {
                                var dummyString = outputControllerWfafle.ui_load_config
                                rootWfafle.updateGUI()
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
                                textFieldText: inputControllerWfafle.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerWfafle.ui_a = inputA.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputP
                                text: "p: "
                                toolTipText: "Initial allele count."
                                validator: IntValidator {bottom: 0; top: 2;}
                                textFieldText: inputControllerWfafle.ui_p
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputP.textFieldText)) && parseInt(inputP.textFieldText) >= 0 && parseInt(inputP.textFieldText) <= 2) {
                                        inputControllerWfafle.ui_p = inputP.textFieldText
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
                    height: parent.height
                    Layout.alignment: Qt.AlignTop
                    Layout.margins: 10

                    ColumnLayout {
                        Layout.alignment: Qt.AlignTop

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

                                Label {
                                    // Empty, so Res is always at right.
                                }

                                LabeledCheckBox {
                                    id: inputWriteDist
                                    text: "Dist: "
                                    enabledCheckBox: false
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
                                        checked: inputControllerWfafle.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        labelPreferredWidth: 10
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputControllerWfafle.ui_t
                                        textFieldTextEdited: function(){
                                            if(!Number.isNaN(Number(inputT.textFieldText)) && parseInt(inputT.textFieldText) >= 1) {
                                                inputControllerWfafle.ui_t = inputT.textFieldText
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

                                    LabeledTextField {
                                        id: inputI
                                        text: "I. Dist.: "
                                        toolTipText: "Path to initial probability distribution CSV file."
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputControllerWfafle.ui_initial_distribution
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
                                value: !outputControllerWfafle.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerWfafle.ui_stop
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
                                if(outputControllerWfafle.ui_get_not_exec)
                                    imageOutputController.image_changed()
                                console.log(outputControllerWfafle.ui_get_error_message)
                                if(outputControllerWfafle.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerWfafle.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerWfafle.ui_reset_error
                                }
                                upperMenu.updateDistWfafle()

                                if(enabled)
                                    upperMenu.chartVisible = true
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerWfafle.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()


                                if(error === "") {
                                    updateBackend()
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerWfafle.ui_execute
                                } else {
                                    messageDialog.text = error
                                    messageDialog.open()
                                }
                                outputControllerWfafle.ui_reset_error
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
                                model: outputControllerWfafle.ui_probs
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

                    Button {
                        text: "Copy to Clipboard"

                        Layout.alignment: Qt.AlignHCenter

                        onClicked: {
                            outputControllerWfafle.coppyToClipboard()
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
            value: !outputControllerWfafle.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfafle.ui_progress

            executionTime: {
                outputControllerWfafle.ui_get_time == "" ? "" : outputControllerWfafle.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }


    }

    function updateGUI() {
        inputA.textFieldText = inputControllerWfafle.ui_a
        inputP.textFieldText = inputControllerWfafle.ui_p
        var N_vec = inputControllerWfafle.ui_N_vec
        var G_vec = inputControllerWfafle.ui_G_vec
        var u_vec = inputControllerWfafle.ui_u_vec
        var v_vec = inputControllerWfafle.ui_v_vec
        var s_vec = inputControllerWfafle.ui_s_vec
        var h_vec = inputControllerWfafle.ui_h_vec

        // Minus 2 because we don't have to count the add and delete tabs.
        // If the number of current tabs is less than the number of components to load,
        // add a tab.
        if(componentsSectionTabView.children[0].count - 2 < inputControllerWfafle.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 < inputControllerWfafle.ui_num_comp) {
                // Create new tab.
                componentsSectionTabView.children[0].addTab()
                // Don't update ui_num_comp
                inputControllerWfafle.ui_num_comp = inputControllerWfafle.ui_num_comp - 1
            }
        // If the number of current tabs is greater than the number of components to load,
        // remove a tab.
        } else if(componentsSectionTabView.children[0].count - 2 > inputControllerWfafle.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 > inputControllerWfafle.ui_num_comp) {
                // Delete a tab.
                componentsSectionTabView.children[0].deleteTab()
                // Don't update ui_num_comp
                inputControllerWfafle.ui_num_comp = parseInt(inputControllerWfafle.ui_num_comp) + 1
            }
        }

        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText = N_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText = G_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText = h_vec[i]
        }

        inputWriteDist.checked = inputControllerWfafle.ui_output_Dist
        inputT.textFieldText = inputControllerWfafle.ui_t
        inputForce.checked = inputControllerWfafle.ui_force

        inputI.textFieldText = inputControllerWfafle.ui_initial_distribution

        var library = inputControllerWfafle.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfafle.ui_solver
        if(library === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(library === "BicGStab")
            comboBoxSolver.currentIndex = 1
    }

    function updateBackend() {
        inputControllerWfafle.ui_a = inputA.textFieldText
        inputControllerWfafle.ui_p = inputP.textFieldText
        var N_vec = []
        var G_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            G_vec.push(G)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerWfafle.ui_N_vec = N_vec
        inputControllerWfafle.ui_G_vec = G_vec
        inputControllerWfafle.ui_u_vec = u_vec
        inputControllerWfafle.ui_v_vec = v_vec
        inputControllerWfafle.ui_s_vec = s_vec
        inputControllerWfafle.ui_h_vec = h_vec

        inputControllerWfafle.ui_output_Dist = inputWriteDist.checked
        inputControllerWfafle.ui_t = inputT.textFieldText
        inputControllerWfafle.ui_force = inputForce.checked

        inputControllerWfafle.ui_initial_distribution = inputI.textFieldText

        inputControllerWfafle.ui_library = comboBoxLibrary.currentText;
        inputControllerWfafle.ui_solver = comboBoxSolver.currentText;
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

        if(inputP.textFieldText == "")
            error += " - Initial Allele Count (p) is empty. \n \n"
        if(Number.isNaN(Number(inputP.textFieldText)))
            error += " - Initial Allele Count (p) is not a valid number. \n \n"
        if(parseInt(inputP.textFieldText) < 0)
            error += " - Initial Allele Count (p) is quite small. It must be at least 0. \n \n"
        if(!inputForce.checked && parseInt(inputP.textFieldText) > 2)
            error += " - Initial Allele Count (p) value is quite high. The maximum value allowed is 2. \n \n"

        var N_vec = []
        var G_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            var G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
            var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
            var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
            var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
            N_vec.push(N)
            G_vec.push(G)
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }

        for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
            N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            if(N === "")
                error += " - Population Size (N" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(N_vec[i])))
                error += " - Population Size (N) is not a valid number. \n \n"
            if(parseInt(N_vec[i]) < 2)
                error += " - Population Size (N" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
            if(!inputForce.checked && parseInt(N_vec[i]) > 50000)
                error +=  " - Population Size (N" + (i + 1) + ") is quite large, the computations will take a long time. Check 'Force' to ignore. \n \n"
        }

        for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
            G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            if(G === "")
                error += " - Generations (G" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(G_vec[i])))
                error += " - Generations (G" + (i + 1) + ") is not a valid number. \n \n"
            if(parseInt(G_vec[i]) < 2)
                error += " - Generations (G" + (i + 1) + ") is quite small, it must be at least 2. \n \n"
        }

        if(globalConfiguration.ui_population_scaled) {
            for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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
            for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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

        for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
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
        for(var i = 0; i < 2; i++) {
            if(typeof(componentsSectionTabView.children[0].getTab(i)) === "undefined") {
                loadedComponents = false
            }

        }
        if(loadedComponents) {
            var u, v, s
            var u_vec, v_vec, s_vec = []
            if(globalConfiguration.ui_population_scaled) {
                u = inputControllerWfafle.ui_u_vec
                v = inputControllerWfafle.ui_v_vec
                s = inputControllerWfafle.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] * (4 * parseInt(inputControllerWfafle.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] * (4 * parseInt(inputControllerWfafle.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] * (2 * parseInt(inputControllerWfafle.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfafle.ui_u_vec = u_vec
                inputControllerWfafle.ui_v_vec = v_vec
                inputControllerWfafle.ui_s_vec = s_vec


            } else if(updateNonChecked){
                u = inputControllerWfafle.ui_u_vec
                v = inputControllerWfafle.ui_v_vec
                s = inputControllerWfafle.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] / (4 * parseInt(inputControllerWfafle.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] / (4 * parseInt(inputControllerWfafle.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] / (2 * parseInt(inputControllerWfafle.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfafle.ui_u_vec = u_vec
                inputControllerWfafle.ui_v_vec = v_vec
                inputControllerWfafle.ui_s_vec = s_vec

            }
        }
    }
}
