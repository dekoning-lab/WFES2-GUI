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
    id: rootWfesSweep
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFES Sweep)")

    color: Universal.chromeLowColor

    visible: false

    width: 955
    minimumWidth: 955
    maximumWidth: 955
    height: 485
    minimumHeight: 485
    maximumHeight: 485

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootWfesSweep.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = "Some input parameters are incorrect. The configuration will be available in this session, but cannot be saved for future sessions until you fix those values. Do you want to exit anyway?"
            messageDialogOnClose.open()

        } else {
            rootWfesSweep.hide();
            root.visible = true;
            rootWfesSweep.updateBackend()
            outputControllerWfesSweep.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: "Warning"
        text: ""
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfesSweep.hide();
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
                                id: radioButtonFixation
                                checked: true
                                text: qsTr("Fixation")

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
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

                        TabView {
                            id: componentsSectionTabView
                            width: parent.width
                            height: 170
                            style: TabViewStyle {

                            }
                            Tab {
                                id: comp1
                                title: "Comp. 1"
                                height: parent.height
                                width: implicitWidth
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
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return "4Nu<sub>1</sub>: "
                                                    else
                                                        return "u<sub>1</sub>: "
                                                }
                                                toolTipText: "Backward mutation rate."
                                                textFieldTextEdited: function(){
                                                    var u_vec = []
                                                    u_vec[0] = inputU1.textFieldText
                                                    u_vec[1] = inputControllerWfesSweep.ui_u_vec[1]
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputU1.textFieldText)) && parseFloat(inputU1.textFieldText) >= 0 && parseFloat(inputU1.textFieldText) <= 1) {
                                                            inputControllerWfesSweep.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputU1.textFieldText)) && parseFloat(inputU1.textFieldText) >= 0 && parseFloat(inputU1.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                                            inputControllerWfesSweep.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var u_vec = inputControllerWfesSweep.ui_u_vec
                                                    return u_vec[0]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputV1
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return "4Nv<sub>1</sub>: "
                                                    else
                                                        return "v<sub>1</sub>: "
                                                }
                                                toolTipText: "Forward mutation rate."
                                                textFieldTextEdited: function(){
                                                    var v_vec = []
                                                    v_vec[0] = inputV1.textFieldText
                                                    v_vec[1] = inputControllerWfesSweep.ui_v_vec[1]
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputV1.textFieldText)) && parseFloat(inputV1.textFieldText) >= 0 && parseFloat(inputV1.textFieldText) <= 1) {
                                                            inputControllerWfesSweep.ui_v_vec = v_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputV1.textFieldText)) && parseFloat(inputV1.textFieldText) >= 0 && parseFloat(inputV1.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                                            inputControllerWfesSweep.ui_v_vec = v_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                                validator: DoubleValidator {bottom: 0;}
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
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return "2Ns<sub>1</sub>: "
                                                    else
                                                        return "s<sub>1</sub>: "
                                                }
                                                toolTipText: "Selection coefficient."
                                                textFieldTextEdited: function(){
                                                    var s_vec = []
                                                    s_vec[0] = inputS1.textFieldText
                                                    s_vec[1] = inputControllerWfesSweep.ui_s_vec[1]
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputS1.textFieldText)) && parseFloat(inputS1.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS1.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                                            inputControllerWfesSweep.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(parseFloat(!Number.isNaN(Number(inputS1.textFieldText)) && inputS1.textFieldText) >= -1 && parseFloat(inputS1.textFieldText) <= 1) {
                                                            inputControllerWfesSweep.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                                // Validator has no sense here, since any range from -2N to 2N is allowed.
                                                textFieldText: {
                                                    var s_vec = inputControllerWfesSweep.ui_s_vec
                                                    return s_vec[0]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH1
                                                text: "h<sub>1</sub>: "
                                                toolTipText: "Dominance coefficient."
                                                validator: DoubleValidator {bottom: 0; top: 1;}
                                                textFieldTextEdited: function(){
                                                    var h_vec = []
                                                    h_vec[0] = inputH1.textFieldText
                                                    h_vec[1] = inputControllerWfesSweep.ui_h_vec[1]
                                                    if(!Number.isNaN(Number(inputH1.textFieldText)) && parseFloat(inputH1.textFieldText) >= 0 && parseFloat(inputH1.textFieldText) <= 1) {
                                                        inputControllerWfesSweep.ui_h_vec = h_vec
                                                        borderColor = "#555555"
                                                    } else {
                                                        borderColor = "#ff0000"
                                                    }
                                                }
                                                textFieldText: {
                                                    var h_vec = inputControllerWfesSweep.ui_h_vec
                                                    return h_vec[0]
                                                }
                                            }


                                        }
                                    }
                                }

                                onLoaded: function() {
                                    var dummyString = outputControllerWfesSweep.ui_load_config
                                    rootWfesSweep.updateGUI()
                                    updateScaledParameters(false)
                                }
                            }

                            Tab {
                                id: comp2
                                title: "Comp. 2"
                                height: parent.height
                                width: implicitWidth
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
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return "4Nu<sub>2</sub>: "
                                                    else
                                                        return "u<sub>2</sub>: "
                                                }
                                                toolTipText: "Backward mutation rate."
                                                textFieldTextEdited: function(){
                                                    var u_vec = []
                                                    u_vec[0] = inputControllerWfesSweep.ui_u_vec[0]
                                                    u_vec[1] = inputU2.textFieldText
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputU2.textFieldText)) && parseFloat(inputU2.textFieldText) >= 0 && parseFloat(inputU2.textFieldText) <= 1) {
                                                            inputControllerWfesSweep.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputU2.textFieldText)) && parseFloat(inputU2.textFieldText) >= 0 && parseFloat(inputU2.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                                            inputControllerWfesSweep.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var u_vec = inputControllerWfesSweep.ui_u_vec
                                                    return u_vec[1]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputV2
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return "4Nv<sub>2</sub>: "
                                                    else
                                                        return "v<sub>2</sub>: "
                                                }
                                                toolTipText: "Forward mutation rate."
                                                textFieldTextEdited: function(){
                                                    var v_vec = []
                                                    v_vec[0] = inputControllerWfesSweep.ui_u_vec[0]
                                                    v_vec[1] = inputV2.textFieldText
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputV2.textFieldText)) && parseFloat(inputV2.textFieldText) >= 0 && parseFloat(inputV2.textFieldText) <= 1) {
                                                            inputControllerWfesSweep.ui_v_vec = v_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputV2.textFieldText)) && parseFloat(inputV2.textFieldText) >= 0 && parseFloat(inputV2.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                                            inputControllerWfesSweep.ui_v_vec = v_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                                validator: DoubleValidator {bottom: 0;}
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
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return "2Ns<sub>2</sub>: "
                                                    else
                                                        return "s<sub>2</sub>: "
                                                }
                                                toolTipText: "Selection coefficient."
                                                textFieldTextEdited: function(){
                                                    var s_vec = []
                                                    s_vec[0] = inputControllerWfesSweep.ui_s_vec[0]
                                                    s_vec[1] = inputS2.textFieldText
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputS2.textFieldText)) && parseFloat(inputS2.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS2.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                                            inputControllerWfesSweep.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputS2.textFieldText)) && parseFloat(inputS2.textFieldText) >= -1 && parseFloat(inputS2.textFieldText) <= 1) {
                                                            inputControllerWfesSweep.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                                // Validator has no sense here, since any range from -2N to 2N is allowed.
                                                textFieldText: {
                                                    var s_vec = inputControllerWfesSweep.ui_s_vec
                                                    return s_vec[1]
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH2
                                                text: "h<sub>2</sub>: "
                                                toolTipText: "Dominance coefficient."
                                                validator: DoubleValidator {bottom: 0; top: 1;}
                                                textFieldTextEdited: function(){
                                                    var h_vec = []
                                                    h_vec[0] = inputControllerWfesSweep.ui_h_vec[0]
                                                    h_vec[1] = inputH2.textFieldText
                                                    if(!Number.isNaN(Number(inputH2.textFieldText)) && parseFloat(inputH2.textFieldText) >= 0 && parseFloat(inputH2.textFieldText) <= 1) {
                                                        inputControllerWfesSweep.ui_h_vec = h_vec
                                                        borderColor = "#555555"
                                                    } else {
                                                        borderColor = "#ff0000"
                                                    }
                                                }
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
                        width: componentsSection.width
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
                                id: inputN
                                text: "N: "
                                toolTipText: "Size of the population in the Wright Fisher Model."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerWfesSweep.ui_n
                                textFieldTextEdited: function(){
                                    if(parseInt(inputN.textFieldText) > 1) {
                                        inputControllerWfesSweep.ui_n = inputN.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                    for(var i = 0; i < 2; i++) {
                                        // Notify u
                                        componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldTextEdited()
                                        // Notify v
                                        componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldTextEdited()
                                    }
                                    inputP.textFieldTextEdited()
                                }
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSweep.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerWfesSweep.ui_a = inputA.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputL
                                text: "l: "
                                toolTipText: "Transition probability."
                                validator: DoubleValidator {bottom: 1e-20; top: 1;}
                                textFieldText: inputControllerWfesSweep.ui_l
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputL.textFieldText)) && parseFloat(inputL.textFieldText) >= 1e-20 && parseFloat(inputL.textFieldText) <= 1) {
                                        inputControllerWfesSweep.ui_l = inputL.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputC
                                text: "c: "
                                toolTipText: "TODO."
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerWfesSweep.ui_c
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputC.textFieldText)) && parseFloat(inputC.textFieldText) >= 0) {
                                        inputControllerWfesSweep.ui_c = inputC.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputP
                                text: "p: "
                                toolTipText: "Starting number of copies integration cutoff."
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerWfesSweep.ui_p
                                textFieldTextEdited: function(){
                                    if(parseInt(inputP.textFieldText) >= 0 && parseInt(inputP.textFieldText) <= parseInt(inputN.textFieldText)) {
                                        inputControllerWfesSingle.ui_p = inputP.textFieldText
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
                                        checked: inputControllerWfesSweep.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        labelPreferredWidth: 10
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 1;}
                                        textFieldText: inputControllerWfesSweep.ui_t
                                        textFieldTextEdited: function(){
                                            if(parseInt(inputT.textFieldText) >= 1) {
                                                inputControllerWfesSingle.ui_t = inputT.textFieldText
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
/*
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
                                    }*/

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
                                bottomMenu.visibleProgressBar = false
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
                                console.log(outputControllerWfesSweep.ui_get_error_message)
                                if(outputControllerWfesSweep.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerWfesSweep.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerWfesSweep.ui_reset_error
                                }
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerWfesSweep.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()


                                if(error === "") {
                                    updateBackend()
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerWfesSweep.ui_execute
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
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "T<sub>fix</sub>: "
                                toolTipText: "Expected number of generations between two fixation events."
                                textFieldText: outputControllerWfesSweep.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: "Rate: "
                                toolTipText: "Rate of substitution."
                                textFieldText: outputControllerWfesSweep.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }


                            Button {
                                text: "Copy to Clipboard"

                                Layout.alignment: Qt.AlignHCenter

                                onClicked: {
                                    outputControllerWfesSweep.coppyToClipboard()
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
                topMargin: 0
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

        //inputI.textFieldText = inputControllerWfesSweep.ui_initial_distribution

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

        //inputControllerWfesSweep.ui_initial_distribution = inputI.textFieldText

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

        if(inputL.textFieldText == "")
            error += " - Rate of Switching (l) is empty. \n \n"
        if(Number.isNaN(Number(inputL.textFieldText)))
            error += " - Rate of Switching (l) is not a valid number. \n \n"
        if(parseFloat(inputL.textFieldText) < 1e-20)
            error += " - Rate of Switching (l) is quite small. It must be at least 0. \n \n"
        if(parseFloat(inputL.textFieldText) > 1)
            error += " - Rate of Switching (l) value is quite high. The maximum value allowed is 1. \n \n"

        if(inputC.textFieldText == "")
            error += " - Integration Cutoff (c) is empty. \n \n"
        if(Number.isNaN(Number(inputC.textFieldText)))
            error += " - Integration Cutoff (c) is not a valid number. \n \n"
        if(parseFloat(inputC.textFieldText) < 0)
            error += " - Integration Cutoff (c) is quite small. It must be at least 0. \n \n"
        if(parseFloat(inputC.textFieldText) > 10e-3)
            error += " - Integration Cutoff (c) is quite large. The maximum value allowed is 10e-3. \n \n"

        if(inputP.textFieldText == "")
            error += " - Starting copies (p) is empty. \n \n"
        if(Number.isNaN(Number(inputP.textFieldText)))
            error += " - Starting copies (p) is not a valid number. \n \n"
        if(parseInt(inputP.textFieldText) < 0)
            error += " - Starting copies (p) is quite small, if you want to disable it just use 0. \n \n"
        if(parseInt(inputP.textFieldText) > parseInt(inputN.textFieldText))
            error += " - Starting Copies (p) is quite large. The maximum value allowed is N. \n \n"

        //Extract vectors to check checkIntegrity
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        var i = 0
        for(i = 0; i < 2; i++) {
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

        if(globalConfiguration.ui_population_scaled) {
            for(i = 0; i < 2; i++) {
                u = componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                if(u === "")
                    error += " - Backward Mutation (u" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(u_vec[i])))
                    error += " - Backward Mutation (u" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(u_vec[i]) <= 0)
                    error += " - Backward Mutation (u" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && parseFloat(u_vec[i]) > 1)
                    error += " - Backward Mutation (u" + (i + 1) + ") of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < 2; i++) {
                v = componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                if(v === "")
                    error += " - Forward Mutation (v" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(v_vec[i])))
                    error += " - Forward Mutation (v" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(v_vec[i]) <= 0)
                    error += " - Forward Mutation (v" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(!inputForce.checked && parseFloat(v_vec[i]) > 1)
                    error += " - Forward Mutation (v" + (i + 1) + ") of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < 2; i++) {
                s = componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                if(s === "")
                    error += " - Selection Coefficient (s" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(s_vec[i])))
                    error += " - Selection Coefficient (s" + (i + 1) + ") is not a valid number. \n \n"
                if(parseFloat(s_vec[i]) < -1 * (2 * parseInt(inputN.textFieldText)))
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite negative. It must be at least -2N \n \n"
                if(parseFloat(s_vec[i]) > 1 * (2 * parseInt(inputN.textFieldText)))
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite large. The maximum value allowed is 2N. \n \n"
            }
        } else {
            for(i = 0; i < 2; i++) {
                u = componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                if(u === "")
                    error += " - Backward Mutation (u" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(u_vec[i])))
                    error += " - Backward Mutation (u" + (i + 1) + ") is not a valid number. \n \n"
                if(Number.isNaN(Number(u_vec[i])) && parseFloat(u_vec[i]) <= 0)
                    error += " - Backward Mutation (u" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(Number.isNaN(Number(u_vec[i])) && !inputForce.checked && parseFloat(u_vec[i]) > 1 / (4 * parseInt(inputN.textFieldText)))
                    error += " - Backward Mutation (u" + (i + 1) + ") of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < 2; i++) {
                v = componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                if(v === "")
                    error += " - Forward Mutation (v" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(v_vec[i])))
                    error += " - Forward Mutation (v" + (i + 1) + ") is not a valid number. \n \n"
                if(Number.isNaN(Number(v_vec[i])) && parseFloat(v_vec[i]) <= 0)
                    error += " - Forward Mutation (v" + (i + 1) + ") of SGV is quite small. It must be at least 0. \n \n"
                if(Number.isNaN(Number(v_vec[i])) && !inputForce.checked && parseFloat(v_vec[i]) > 1 / (4 * parseInt(inputN.textFieldText)))
                    error += " - Forward Mutation (v" + (i + 1) + ") of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore. \n \n"
            }

            for(i = 0; i < 2; i++) {
                s = componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                if(s === "")
                    error += " - Selection Coefficient (s" + (i + 1) + ") is empty. \n \n"
                if(Number.isNaN(Number(s_vec[i])))
                    error += " - Selection Coefficient (s" + (i + 1) + ") is not a valid number. \n \n"
                if(Number.isNaN(Number(s_vec[i])) && parseFloat(s_vec[i]) < -1)
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite negative. It must be at least -2N \n \n"
                if(Number.isNaN(Number(s_vec[i])) && parseFloat(s_vec[i]) > 1 )
                    error += " - Selection Coefficient (s" + (i + 1) + ") of SGV is quite large. The maximum value allowed is 2N. \n \n"
            }
        }
        for(i = 0; i < 2; i++) {
            h = componentsSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
            if(h === "")
                error += " - Dominance Coefficient (h" + (i + 1) + ") is empty. \n \n"
            if(Number.isNaN(Number(h_vec[i])))
                error += " - Dominance Coefficient (h" + (i + 1) + ") is not a valid number. \n \n"
            if(Number.isNaN(Number(h_vec[i])) && parseFloat(h_vec[i]) < 0)
                error += " - Dominance Coefficient (h" + (i + 1) + ") is quite small. It must be at least 0. \n \n"
            if(Number.isNaN(Number(h_vec[i])) && parseFloat(h_vec[i]) > 1)
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
            if(typeof(componentsSectionTabView.getTab(i)) === "undefined") {
                loadedComponents = false
            }

        }
        if(loadedComponents) {
            var u, v, s
            var u_vec, v_vec, s_vec = []
            if(globalConfiguration.ui_population_scaled) {
                u = inputControllerWfesSweep.ui_u_vec
                v = inputControllerWfesSweep.ui_v_vec
                s = inputControllerWfesSweep.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < 2; i++) {
                    componentsSectionTabView.getTab(i).active = true
                    u_vec.push((u[i] * (4 * parseInt(inputControllerWfesSweep.ui_n))).toString())
                    v_vec.push((v[i] * (4 * parseInt(inputControllerWfesSweep.ui_n))).toString())
                    s_vec.push((s[i] * (2 * parseInt(inputControllerWfesSweep.ui_n))).toString())
                    componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfesSweep.ui_u_vec = u_vec
                inputControllerWfesSweep.ui_v_vec = v_vec
                inputControllerWfesSweep.ui_s_vec = s_vec


            } else if(updateNonChecked){
                u = inputControllerWfesSweep.ui_u_vec
                v = inputControllerWfesSweep.ui_v_vec
                s = inputControllerWfesSweep.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < 2; i++) {
                    componentsSectionTabView.getTab(i).active = true
                    u_vec.push((u[i] / (4 * parseInt(inputControllerWfesSweep.ui_n))).toString())
                    v_vec.push((v[i] / (4 * parseInt(inputControllerWfesSweep.ui_n))).toString())
                    s_vec.push((s[i] / (2 * parseInt(inputControllerWfesSweep.ui_n))).toString())
                    componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
                    componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
                    componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerWfesSweep.ui_u_vec = u_vec
                inputControllerWfesSweep.ui_v_vec = v_vec
                inputControllerWfesSweep.ui_s_vec = s_vec

            }
        }
    }
}
