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
    id: rootWfafd
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.wfafD + ")"

    color: Universal.chromeLowColor

    visible: false

    width: column1.width + column2.width + column3.width + (Style.marginSmall * 5)
    minimumWidth: column1.width + column2.width + column3.width + (Style.marginSmall * 5)
    maximumWidth: column1.width + column2.width + column3.width + (Style.marginSmall * 5)
    height: upperMenu.height + Math.max(column1.height, column2.height, column3.height) + bottomMenu.height
    minimumHeight: upperMenu.height + Math.max(column1.height, column2.height, column3.height) + bottomMenu.height
    maximumHeight: upperMenu.height + Math.max(column1.height, column2.height, column3.height) + bottomMenu.height

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootWfafd.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
            messageDialogOnClose.open()
        } else {
            rootWfafd.hide();
            root.visible = true;
            rootWfafd.updateBackend()
            outputControllerWfafd.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfafd.hide();
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
                            urlComponent: "qrc:/components/executionviews/tabcomponents/tabWfafdComponent.qml"
                            onAdd: function(){
                                var num_comps = inputControllerWfafd.ui_num_comp
                                inputControllerWfafd.ui_num_comp = parseInt(num_comps) + 1

                                var vector = inputControllerWfafd.ui_N_vec
                                vector[num_comps] = inputControllerWfafd.ui_N_vec[num_comps-1]
                                inputControllerWfafd.ui_N_vec = vector

                                vector = inputControllerWfafd.ui_G_vec
                                vector[num_comps] = inputControllerWfafd.ui_G_vec[num_comps-1]
                                inputControllerWfafd.ui_G_vec = vector

                                vector = inputControllerWfafd.ui_s_vec
                                vector[num_comps] = inputControllerWfafd.ui_s_vec[num_comps-1]
                                inputControllerWfafd.ui_s_vec = vector

                                vector = inputControllerWfafd.ui_h_vec
                                vector[num_comps] = inputControllerWfafd.ui_h_vec[num_comps-1]
                                inputControllerWfafd.ui_h_vec = vector

                                vector = inputControllerWfafd.ui_u_vec
                                vector[num_comps] = inputControllerWfafd.ui_u_vec[num_comps-1]
                                inputControllerWfafd.ui_u_vec = vector

                                vector = inputControllerWfafd.ui_v_vec
                                vector[num_comps] = inputControllerWfafd.ui_v_vec[num_comps-1]
                                inputControllerWfafd.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfafd.ui_num_comp
                                inputControllerWfafd.ui_num_comp = parseInt(num_comps) - 1
                            }
                            onLoaded: function() {
                                var dummyString = outputControllerWfafd.ui_load_config
                                rootWfafd.updateGUI()
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
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfafd.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerWfafd.ui_a = inputA.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputP
                                text: Strings.p + Strings.colon
                                toolTipText: Strings.pTooltip
                                validator: IntValidator {bottom: 0; top: 2;}
                                textFieldText: inputControllerWfafd.ui_p
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputP.textFieldText)) && parseInt(inputP.textFieldText) >= 0 && parseInt(inputP.textFieldText) <= 2) {
                                        inputControllerWfafd.ui_p = inputP.textFieldText
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

                                Label {
                                    // Empty, so Res is always at right.
                                }

                                LabeledCheckBox {
                                    id: inputWriteDist
                                    text: Strings.outputDist + Strings.colon
                                    enabledCheckBox: false
                                    toolTipText: Strings.outputDistTooltip
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
                                        checked: inputControllerWfafd.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: Strings.t + Strings.colon
                                        labelPreferredWidth: Style.marginSmall
                                        toolTipText: Strings.tTooltip
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputControllerWfafd.ui_t
                                        textFieldTextEdited: function(){
                                            if(!Number.isNaN(Number(inputT.textFieldText)) && parseInt(inputT.textFieldText) >= 1) {
                                                inputControllerWfafd.ui_t = inputT.textFieldText
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

                                    LabeledTextField {
                                        id: inputI
                                        text: Strings.iDist + Strings.colon
                                        toolTipText: Strings.iDistTooltip
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputControllerWfafd.ui_initial_distribution
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
                        Layout.preferredWidth: parent.width

                        Button {
                            id: stopButton
                            Layout.margins: Style.marginSmall
                            Layout.alignment: Qt.AlignRight
                            text: Strings.stopButton

                            Binding {
                                target: stopButton
                                property: "enabled"
                                value: !outputControllerWfafd.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerWfafd.ui_stop
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
                                if(outputControllerWfafd.ui_get_not_exec)
                                    imageOutputController.image_changed()
                                console.log(outputControllerWfafd.ui_get_error_message)
                                if(outputControllerWfafd.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerWfafd.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerWfafd.ui_reset_error
                                }
                                upperMenu.updateDistWfafd()

                                if(enabled)
                                    upperMenu.chartVisible = true
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerWfafd.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()


                                if(error === "") {
                                    updateBackend()
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerWfafd.ui_execute
                                } else {
                                    messageDialog.text = error
                                    messageDialog.open()
                                }
                                outputControllerWfafd.ui_reset_error
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
                        id: labelMoments
                        text: Strings.output + Strings.colon
                        font.bold: true
                    }

                    Label {
                        id: labelMoments2
                        text: Strings.alleleFreqDist + Strings.colon
                    }

                    Rectangle {
                        width: labelMoments.width * 4
                        height: childrenRect.height + 1
                        color: "transparent"
                        border.width: 1

                        Layout.alignment: Qt.AlignTop
                        Layout.margins: Style.marginSmall

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
                                model: outputControllerWfafd.ui_probs
                                delegate: ItemDelegate {
                                  width: labelMoments.width * 4
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
                        text: Strings.copyToClipboard

                        Layout.alignment: Qt.AlignHCenter

                        onClicked: {
                            outputControllerWfafd.coppyToClipboard()
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
            value: !outputControllerWfafd.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfafd.ui_progress

            executionTime: {
                outputControllerWfafd.ui_get_time == "" ? "" : outputControllerWfafd.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }


    }

    function updateGUI() {
        inputA.textFieldText = inputControllerWfafd.ui_a
        inputP.textFieldText = inputControllerWfafd.ui_p
        var N_vec = inputControllerWfafd.ui_N_vec
        var G_vec = inputControllerWfafd.ui_G_vec
        var u_vec = inputControllerWfafd.ui_u_vec
        var v_vec = inputControllerWfafd.ui_v_vec
        var s_vec = inputControllerWfafd.ui_s_vec
        var h_vec = inputControllerWfafd.ui_h_vec

        // Minus 2 because we don't have to count the add and delete tabs.
        // If the number of current tabs is less than the number of components to load,
        // add a tab.
        if(componentsSectionTabView.children[0].count - 2 < inputControllerWfafd.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 < inputControllerWfafd.ui_num_comp) {
                // Create new tab.
                componentsSectionTabView.children[0].addTab()
                // Don't update ui_num_comp
                inputControllerWfafd.ui_num_comp = inputControllerWfafd.ui_num_comp - 1
            }
        // If the number of current tabs is greater than the number of components to load,
        // remove a tab.
        } else if(componentsSectionTabView.children[0].count - 2 > inputControllerWfafd.ui_num_comp) {

            while(componentsSectionTabView.children[0].count - 2 > inputControllerWfafd.ui_num_comp) {
                // Delete a tab.
                componentsSectionTabView.children[0].deleteTab()
                // Don't update ui_num_comp
                inputControllerWfafd.ui_num_comp = parseInt(inputControllerWfafd.ui_num_comp) + 1
            }
        }

        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).active = true
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText = N_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText = G_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText = h_vec[i]
        }

        inputWriteDist.checked = inputControllerWfafd.ui_output_Dist
        inputT.textFieldText = inputControllerWfafd.ui_t
        inputForce.checked = inputControllerWfafd.ui_force

        inputI.textFieldText = inputControllerWfafd.ui_initial_distribution

        var library = inputControllerWfafd.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        var solver = inputControllerWfafd.ui_solver
        if(library === "GMRes")
            comboBoxSolver.currentIndex = 0
        else if(library === "BicGStab")
            comboBoxSolver.currentIndex = 1

        // Update boxes.
        for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldTextEdited()
        }
        inputA.textFieldTextEdited()
        inputP.textFieldTextEdited()
        inputT.textFieldTextEdited()

    }

    function updateBackend() {
        inputControllerWfafd.ui_a = inputA.textFieldText
        inputControllerWfafd.ui_p = inputP.textFieldText
        var N_vec = []
        var G_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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
        inputControllerWfafd.ui_N_vec = N_vec
        inputControllerWfafd.ui_G_vec = G_vec
        inputControllerWfafd.ui_u_vec = u_vec
        inputControllerWfafd.ui_v_vec = v_vec
        inputControllerWfafd.ui_s_vec = s_vec
        inputControllerWfafd.ui_h_vec = h_vec

        inputControllerWfafd.ui_output_Dist = inputWriteDist.checked
        inputControllerWfafd.ui_t = inputT.textFieldText
        inputControllerWfafd.ui_force = inputForce.checked

        inputControllerWfafd.ui_initial_distribution = inputI.textFieldText

        inputControllerWfafd.ui_library = comboBoxLibrary.currentText;
        inputControllerWfafd.ui_solver = comboBoxSolver.currentText;
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


        if(inputP.textFieldText == "")
            error += Strings.hyphen + Strings.pIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputP.textFieldText)))
            error += Strings.hyphen + Strings.pIsNotValid + Strings.endOfError
        if(parseInt(inputP.textFieldText) < 0)
            error += Strings.hyphen + Strings.pIsSmall + Strings.endOfError
        if(!inputForce.checked && parseInt(inputP.textFieldText) > 2)
            error += Strings.hyphen + Strings.pIsLarge + Strings.endOfError

        var N_vec = []
        var G_vec = []
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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

        for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
            N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
            if(N === "")
                error += Strings.hyphen + Strings.nMulIsEmpty.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(N_vec[i])))
                error += Strings.hyphen + Strings.nMulIsNotValid.arg(i + 1) + Strings.endOfError
            if(parseInt(N_vec[i]) < 2)
                error += Strings.hyphen + Strings.nMulIsSmall.arg(i + 1) + Strings.endOfError
            if(!inputForce.checked && parseInt(N_vec[i]) > 50000)
                error +=  Strings.hyphen + Strings.nMulIsLarge.arg(i + 1) + Strings.endOfError
        }

        for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
            G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
            if(G === "")
                error += Strings.hyphen + Strings.gMulIsEmpty.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(G_vec[i])))
                error += Strings.hyphen + Strings.gMulIsNotValid.arg(i + 1) + Strings.endOfError
            if(parseInt(G_vec[i]) < 1)
                error += Strings.hyphen + Strings.gMulIsSmall.arg(i + 1) + Strings.endOfError
        }

        if(globalConfiguration.ui_population_scaled) {
            for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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
            for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
                if(u === "")
                    error += Strings.hyphen + Strings.uMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(u_vec[i].textFieldText) <= 0)
                    error += Strings.hyphen + Strings.uMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(u_vec[i]) > 1 / (4 * parseInt(N_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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

            for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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

        for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
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
        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
            if(typeof(componentsSectionTabView.children[0].getTab(i)) === "undefined") {
                loadedComponents = false
            }

        }
        if(loadedComponents) {
            var u, v, s
            var u_vec, v_vec, s_vec = []
            if(globalConfiguration.ui_population_scaled) {
                u = inputControllerWfafd.ui_u_vec
                v = inputControllerWfafd.ui_v_vec
                s = inputControllerWfafd.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] * (4 * parseInt(inputControllerWfafd.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] * (4 * parseInt(inputControllerWfafd.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] * (2 * parseInt(inputControllerWfafd.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfafd.ui_u_vec = u_vec
                inputControllerWfafd.ui_v_vec = v_vec
                inputControllerWfafd.ui_s_vec = s_vec


            } else if(updateNonChecked){
                u = inputControllerWfafd.ui_u_vec
                v = inputControllerWfafd.ui_v_vec
                s = inputControllerWfafd.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                    componentsSectionTabView.children[0].getTab(i).active = true
                    u_vec.push((u[i] / (4 * parseInt(inputControllerWfafd.ui_N_vec[i]))).toString())
                    v_vec.push((v[i] / (4 * parseInt(inputControllerWfafd.ui_N_vec[i]))).toString())
                    s_vec.push((s[i] / (2 * parseInt(inputControllerWfafd.ui_N_vec[i]))).toString())
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfafd.ui_u_vec = u_vec
                inputControllerWfafd.ui_v_vec = v_vec
                inputControllerWfafd.ui_s_vec = s_vec

            }
        }
    }
}
