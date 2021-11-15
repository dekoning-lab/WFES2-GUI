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
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.wfesSweep + ")"

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
        onActivated: rootWfesSweep.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
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
        title: Strings.dialogWarning
        text: Strings.empty
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
                                id: radioButtonFixation
                                checked: true
                                text: Strings.wfesSweepFixation

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.wfesSweepFixationTooltip

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
                        text: Strings.components + Strings.colon
                        font.bold: true
                    }

                    Rectangle {
                        id: componentsSection
                        width: commonSection.width + Style.marginSmall
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
                                title: Strings.comp + 1
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
                                            text: Strings.mutation + Strings.colon
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
                                                margins: Style.marginSmall
                                            }

                                            LabeledTextField {
                                                id: inputU1
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return Strings.uSubScaled.arg(1) + Strings.colon
                                                    else
                                                        return Strings.uSub.arg(1) + Strings.colon
                                                }
                                                toolTipText: Strings.uTooltip
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
                                                        return Strings.vSubScaled.arg(1) + Strings.colon
                                                    else
                                                        return Strings.vSub.arg(1) + Strings.colon
                                                }
                                                toolTipText: Strings.vTooltip
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
                                            text: Strings.selection + Strings.colon
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
                                                margins: Style.marginSmall
                                            }

                                            LabeledTextField {
                                                id: inputS1
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return Strings.sSubScaled.arg(1) + Strings.colon
                                                    else
                                                        return Strings.sSub.arg(1) + Strings.colon
                                                }
                                                toolTipText: Strings.sTooltip
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
                                                text: Strings.hSub.arg(1) + Strings.colon
                                                toolTipText: Strings.hTooltip
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
                                title: Strings.comp + "2"
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
                                            text: Strings.mutation + Strings.colon
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
                                                margins: Style.marginSmall
                                            }

                                            LabeledTextField {
                                                id: inputU2
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return Strings.uSubScaled.arg(2) + Strings.colon
                                                    else
                                                        return Strings.uSub.arg(2) + Strings.colon
                                                }
                                                toolTipText: Strings.uTooltip
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
                                                        return Strings.vSubScaled.arg(2) + Strings.colon
                                                    else
                                                        return Strings.vSub.arg(2) + Strings.colon
                                                }
                                                toolTipText: Strings.vTooltip
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
                                            text: Strings.selection + Strings.colon
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
                                                margins: Style.marginSmall
                                            }

                                            LabeledTextField {
                                                id: inputS2
                                                text: {
                                                    if(globalConfiguration.ui_population_scaled)
                                                        return Strings.sSubScaled.arg(2) + Strings.colon
                                                    else
                                                        return Strings.sSub.arg(2) + Strings.colon
                                                }
                                                toolTipText: Strings.sTooltip
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
                                                text: Strings.hSub.arg(2) + Strings.colon
                                                toolTipText: Strings.hTooltip
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
                                id: inputN
                                text: Strings.n + Strings.colon
                                toolTipText: Strings.nTooltip
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
                                text: Strings.a + Strings.colon
                                toolTipText: Strings.aTooltip
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
                                text: Strings.l + Strings.colon
                                toolTipText: Strings.lTooltip
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
                                text: Strings.c + Strings.colon
                                toolTipText: Strings.cTooltip
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
                                text: Strings.p + Strings.colon
                                toolTipText: Strings.pTooltip
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
                    Layout.topMargin: Style.marginSmall
                    Layout.bottomMargin:Style.marginSmall
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
                                    checked: inputControllerWfesSweep.ui_output_Q

                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: Strings.outputR + Strings.colon
                                    toolTipText: Strings.outputRTooltip
                                    checked: inputControllerWfesSweep.ui_output_R
                                }

                                LabeledCheckBox {
                                    id: inputWriteB
                                    text: Strings.outputB + Strings.colon
                                    toolTipText: Strings.outputBTooltip
                                    checked: inputControllerWfesSweep.ui_output_B
                                }

                                LabeledCheckBox {
                                    id: inputWriteN
                                    text: Strings.outputN + Strings.colon
                                    toolTipText: Strings.outputNTooltip
                                    checked: inputControllerWfesSweep.ui_output_N
                                }

                                LabeledCheckBox {
                                    id: inputWriteI
                                    text: Strings.outputI + Strings.colon
                                    toolTipText: Strings.outputITooltip
                                    checked: inputControllerWfesSweep.ui_output_I
                                }

                                LabeledCheckBox {
                                    id: inputWriteRes
                                    text: Strings.outputRes + Strings.colon
                                    toolTipText: Strings.outputResTooltip
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
                                        checked: inputControllerWfesSweep.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: Strings.t + Strings.colon
                                        toolTipText: Strings.tTooltip
                                        labelPreferredWidth: 15
                                        textFieldPreferredWidth: 105
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
/*
                                    LabeledTextField {
                                        id: inputI
                                        text: Strings.iDist + Strings.colon
                                        toolTipText: Strings.iDistTooltip
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputControllerWfesSweep.ui_initial_distribution
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
                        Layout.preferredHeight: childrenRect.height
                        Layout.preferredWidth: parent.width

                        Button {
                            id: stopButton
                            Layout.margins: Style.marginSmall
                            Layout.alignment: Qt.AlignRight
                            text: Strings.stopButton

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
                            Layout.margins: Style.marginSmall
                            Layout.alignment: Qt.AlignRight
                            text: Strings.executeButton

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
                                margins: Style.marginSmall
                            }

                            LabeledTextField {
                                id: outputTFix
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.tFix + Strings.colon
                                toolTipText: Strings.tFixTooltip
                                textFieldText: outputControllerWfesSweep.ui_get_t_fix
                                readOnly: true
                                visible: radioButtonFixation.checked || radioButtonAbsorption.checked
                            }

                            LabeledTextField {
                                id: outputRate
                                labelPreferredWidth: 100
                                textFieldPreferredWidth: 180
                                text: Strings.rate + Strings.colon
                                toolTipText: Strings.rateTooltip
                                textFieldText: outputControllerWfesSweep.ui_get_rate
                                readOnly: true
                                visible: radioButtonFixation.checked
                            }


                            Button {
                                text: Strings.copyToClipboard

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

        // Update boxes.
        for(i = 0; i < 2; i++) {
            componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldTextEdited()
            componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldTextEdited()
            componentsSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldTextEdited()
        }
        inputN.textFieldTextEdited()
        inputA.textFieldTextEdited()
        inputL.textFieldTextEdited()
        inputC.textFieldTextEdited()
        inputP.textFieldTextEdited()
        inputT.textFieldTextEdited()

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
            error += Strings.hyphen + Strings.nIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputN.textFieldText)))
            error += Strings.hyphen + Strings.nIsNotValid + Strings.endOfError
        if(parseInt(inputN.textFieldText) < LimitValues.nMinLimitWfesSweep)
            error += Strings.hyphen + Strings.nIsSmall + Strings.endOfError
        if(!inputForce.checked && parseInt(inputN.textFieldText) > LimitValues.nMaxLimitWfesSweep)
            error += Strings.hyphen + Strings.nIsLarge + Strings.endOfError

        if(inputA.textFieldText == "")
            error += Strings.hyphen + Strings.aIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputA.textFieldText)))
            error += Strings.hyphen + Strings.aIsNotValid + Strings.endOfError
        if(parseFloat(inputA.textFieldText) < LimitValues.aMinLimitWfesSweep)
            error += Strings.hyphen + Strings.aIsSmall + Strings.endOfError
        if(!inputForce.checked && parseFloat(inputA.textFieldText) > LimitValues.aMaxLimitWfesSweep)
            error += Strings.hyphen + Strings.aIsLarge + Strings.endOfError

        if(inputL.textFieldText == "")
            error += Strings.hyphen + Strings.lIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputL.textFieldText)))
            error += Strings.hyphen + Strings.lIsNotValid + Strings.endOfError
        if(parseFloat(inputL.textFieldText) < LimitValues.lMinLimitWfesSweep)
            error += Strings.hyphen + Strings.lIsSmall + Strings.endOfError
        if(parseFloat(inputL.textFieldText) > LimitValues.lMaxLimitWfesSweep)
            error += Strings.hyphen + Strings.lIsLarge + Strings.endOfError

        if(inputC.textFieldText == "")
            error += Strings.hyphen + Strings.cIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputC.textFieldText)))
            error += Strings.hyphen + Strings.cIsNotValid + Strings.endOfError
        if(parseFloat(inputC.textFieldText) < LimitValues.cMinLimitWfesSweep)
            error += Strings.hyphen + Strings.cIsSmall + Strings.endOfError
        if(parseFloat(inputC.textFieldText) > LimitValues.cMaxLimitWfesSweep)
            error += Strings.hyphen + Strings.cIsLarge + Strings.endOfError

        if(inputP.textFieldText == "")
            error += Strings.hyphen + Strings.pStartIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputP.textFieldText)))
            error += Strings.hyphen + Strings.pStartIsNotValid + Strings.endOfError
        if(parseInt(inputP.textFieldText) < LimitValues.pMinLimitWfesSweep)
            error += Strings.hyphen + Strings.pStartIsSmall + Strings.endOfError
        if(parseInt(inputP.textFieldText) > parseInt(inputN.textFieldText))
            error += Strings.hyphen + Strings.pStartIsLargeFixationSweep + Strings.endOfError

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
                    error += Strings.hyphen + Strings.uMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(u_vec[i]) <= LimitValues.uMinLimitWfesSweep)
                    error += Strings.hyphen + Strings.uMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(u_vec[i]) > LimitValues.uMaxLimitWfesSweep)
                    error += Strings.hyphen + Strings.uMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < 2; i++) {
                v = componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                if(v === "")
                    error += Strings.hyphen + Strings.vMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(v_vec[i])))
                    error += Strings.hyphen + Strings.vMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(v_vec[i]) <= LimitValues.vMinLimitWfesSweep)
                    error += Strings.hyphen + Strings.vMulIsSmall.arg(i + 1) + Strings.endOfError
                if(!inputForce.checked && parseFloat(v_vec[i]) > LimitValues.vMaxLimitWfesSweep)
                    error += Strings.hyphen + Strings.vMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < 2; i++) {
                s = componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                if(s === "")
                    error += Strings.hyphen + Strings.sMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(s_vec[i])))
                    error += Strings.hyphen + Strings.sMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(s_vec[i]) < LimitValues.sMinLimitWfesSweep * (2 * parseInt(inputN.textFieldText)))
                    error += Strings.hyphen + Strings.sMulIsSmall.arg(i + 1) + Strings.endOfError
                if(parseFloat(s_vec[i]) > LimitValues.sMaxLimitWfesSweep * (2 * parseInt(inputN.textFieldText)))
                    error += Strings.hyphen + Strings.sMulIsLargeScaled.arg(i + 1) + Strings.endOfError
            }
        } else {
            for(i = 0; i < 2; i++) {
                u = componentsSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                if(u === "")
                    error += Strings.hyphen + Strings.uMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])))
                    error += Strings.hyphen + Strings.uMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])) && parseFloat(u_vec[i]) <= LimitValues.uMinLimitWfesSweep)
                    error += Strings.hyphen + Strings.uMulIsSmall.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(u_vec[i])) && !inputForce.checked && parseFloat(u_vec[i]) > LimitValues.uMaxLimitWfesSweep / (4 * parseInt(inputN.textFieldText)))
                    error += Strings.hyphen + Strings.uMulIsLarge.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < 2; i++) {
                v = componentsSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                if(v === "")
                    error += Strings.hyphen + Strings.vMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(v_vec[i])))
                    error += Strings.hyphen + Strings.vMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(v_vec[i])) && parseFloat(v_vec[i]) <= LimitValues.vMinLimitWfesSweep)
                    error += Strings.hyphen + Strings.vMulIsSmall.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(v_vec[i])) && !inputForce.checked && parseFloat(v_vec[i]) > LimitValues.vMaxLimitWfesSweep / (4 * parseInt(inputN.textFieldText)))
                    error += Strings.hyphen + Strings.vMulIsLarge.arg(i + 1) + Strings.endOfError
            }

            for(i = 0; i < 2; i++) {
                s = componentsSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                if(s === "")
                    error += Strings.hyphen + Strings.sMulIsEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(s_vec[i])))
                    error += Strings.hyphen + Strings.sMulIsNotValid.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(s_vec[i])) && parseFloat(s_vec[i]) < LimitValues.sMinLimitWfesSweep)
                    error += Strings.hyphen + Strings.sMulIsSmall.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(s_vec[i])) && parseFloat(s_vec[i]) > LimitValues.sMaxLimitWfesSweep )
                    error += Strings.hyphen + Strings.sMulIsLarge.arg(i + 1) + Strings.endOfError
            }
        }
        for(i = 0; i < 2; i++) {
            h = componentsSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
            if(h === "")
                error += Strings.hyphen + Strings.hMulIsEmpty.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(h_vec[i])))
                error += Strings.hyphen + Strings.hMulIsNotValid.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(h_vec[i])) && parseFloat(h_vec[i]) < LimitValues.hMinLimitWfesSweep)
                error += Strings.hyphen + Strings.hMulIsSmall.arg(i + 1) + Strings.endOfError
            if(Number.isNaN(Number(h_vec[i])) && parseFloat(h_vec[i]) > LimitValues.hMinLimitWfesSweep)
                error += Strings.hyphen + Strings.hMulIsLarge.arg(i + 1) + Strings.endOfError
        }

        if(inputT.textFieldText == "")
            error += Strings.hyphen + Strings.tIsEmpty + Strings.endOfError
        if(Number.isNaN(Number(inputT.textFieldText)))
            error += Strings.hyphen + Strings.tIsNotValid + Strings.endOfError
        if(parseInt(inputT.textFieldText) < LimitValues.tMinLimitWfesSweep)
            error += Strings.hyphen + Strings.tIsSmall + Strings.endOfError
        // Number of threads (t) does not have upper limites, since it depends on the hardware available.

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
