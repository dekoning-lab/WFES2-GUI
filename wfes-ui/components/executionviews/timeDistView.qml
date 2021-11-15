import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0

ApplicationWindow {
    property var firstLoad: true

    id: rootTimeDist
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.timeDist + ")"

    color: Universal.chromeLowColor

    visible: false

    width: column1.width + column2.width +  (Style.marginSmall * 5)
    minimumWidth: column1.width + column2.width + (Style.marginSmall * 5)
    maximumWidth: column1.width + column2.width + (Style.marginSmall * 5)
    height: upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
    minimumHeight: upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
    maximumHeight: upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootTimeDist.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
            messageDialogOnClose.open()
        } else {
            rootTimeDist.hide();
            root.visible = true;
            rootTimeDist.updateBackend()
            outputControllerTimeDist.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootTimeDist.hide();
            root.visible = true;
        }
    }

    Component.onCompleted: {
        // Center window in screen.
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
        // Activate time dist sgv, so it is loaded and it loads the configuration.
        radioButtonTimeDistSGV.checked = true
        // Load configuration done in DynamicView.
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"

        UpperMenu {
            id: upperMenu
        }

        Rectangle {
            id: content
            height: childrenRect.height
            width: childrenRect.width
            color: "transparent"

            anchors {
                top: upperMenu.bottom
                left: parent.left
            }

            RowLayout {
                id: mainGrid

                Rectangle {
                    id: column1
                    width: childrenRect.width
                    height: childrenRect.height
                    Layout.margins: Style.marginSmall
                    color: "transparent"

                    ColumnLayout {

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
                                id: radioButtonTimeDist
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist."
                                text: Strings.timeDistMode

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.timeDistModeTooltip

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = !checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = checked

                                    labelComponents.visible = !checked
                                    timeDistSGVSection.visible = !checked
                                    timeDistSGVCommonSection.visible = !checked
                                    populationSection.visible = checked
                                    mutationSection.visible = checked
                                    selectionSection.visible = checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = checked

                                    rootTimeDist.width = column1.width + column2.width +  (Style.marginSmall * 5)
                                    rootTimeDist.minimumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.maximumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.height = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.minimumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.maximumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                }
                            }
                            RadioButton {
                                id: radioButtonTimeDistSGV
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. SGV"
                                text: Strings.timeDistSGV

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.timeDistSGVTooltip

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = checked

                                    labelComponents.visible = checked
                                    timeDistSGVSection.visible = checked
                                    timeDistSGVCommonSection.visible = checked
                                    populationSection.visible = !checked
                                    mutationSection.visible = !checked
                                    selectionSection.visible = !checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = !checked


                                    rootTimeDist.width = column1.width + column2.width +  (Style.marginSmall * 5)
                                    rootTimeDist.minimumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.maximumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.height = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.minimumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.maximumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                }
                            }

                            RadioButton {
                                id: radioButtonTimeDistSkip
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. Skip"
                                text: Strings.timeDistSkip

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.timeDistSkipTooltip

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = !checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = checked

                                    labelComponents.visible = !checked
                                    timeDistSGVSection.visible = !checked
                                    timeDistSGVCommonSection.visible = !checked
                                    populationSection.visible = checked
                                    mutationSection.visible = checked
                                    selectionSection.visible = checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = checked

                                    rootTimeDist.width = column1.width + column2.width +  (Style.marginSmall * 5)
                                    rootTimeDist.minimumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.maximumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.height = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.minimumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.maximumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                }
                            }

                            RadioButton {
                                id: radioButtonTimeDistDual
                                checked: inputControllerTimeDist.ui_modelType == "Time Dist. Dual"
                                text: Strings.timeDistDual

                                ToolTip.visible: hovered
                                ToolTip.delay: Style.tooltipDelay
                                ToolTip.timeout: Style.tooltipTimeout
                                ToolTip.text: Strings.timeDistDualTooltip

                                onCheckedChanged: {
                                    inputN.enabled = checked;
                                    inputA.enabled = checked;
                                    inputL.enabled = !checked;
                                    inputC.enabled = checked;
                                    inputM.enabled = checked;

                                    inputU.enabled = checked;
                                    inputV.enabled = checked;
                                    inputR.enabled = checked;

                                    inputS.enabled = checked;
                                    inputH.enabled = checked;

                                    inputWriteQ.enabled = checked;
                                    inputWriteR.enabled = checked;
                                    inputWriteP.enabled = checked;

                                    inputForce.enabled = checked

                                    labelComponents.visible = !checked
                                    timeDistSGVSection.visible = !checked
                                    timeDistSGVCommonSection.visible = !checked
                                    populationSection.visible = checked
                                    mutationSection.visible = checked
                                    selectionSection.visible = checked

                                    separator1column1.visible = checked
                                    separator2column1.visible = checked
                                    separator3column1.visible = checked

                                    rootTimeDist.width = column1.width + column2.width +  (Style.marginSmall * 5)
                                    rootTimeDist.minimumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.maximumWidth = column1.width + column2.width + (Style.marginSmall * 5)
                                    rootTimeDist.height = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.minimumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                    rootTimeDist.maximumHeight = upperMenu.height + Math.max(column1.height, column2.height) + bottomMenu.height +  (Style.marginSmall * 2)
                                }
                            }

                        }

                    }

                    Rectangle {
                        id: separator1column1
                        height: 1
                        width: modeSectionGrid.width + Style.marginSmall
                        color: Universal.baseHighColor
                    }

                    Label {
                        id: labelComponents
                        text: Strings.components + Strings.colon
                        visible: (inputControllerTimeDist.ui_modelType === "Time Dist. SGV")
                        font.bold: true
                    }

                    Rectangle {
                        id: timeDistSGVSection
                        width: modeSection.width + Style.marginSmall
                        height: childrenRect.height

                        color: "transparent"

                        visible: (inputControllerTimeDist.ui_modelType === "Time Dist. SGV")

                        Layout.alignment: Qt.AlignTop

                        TabView {
                            id: timeDistSGVSectionTabView
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
                                            columns: 2
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
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var u_vec = inputControllerTimeDist.ui_u_vec
                                                    return u_vec[0]
                                                }
                                                textFieldTextEdited: function(){
                                                    var u_vec = []
                                                    u_vec[0] = inputControllerTimeDist.ui_u_vec[0]
                                                    u_vec[1] = inputU1.textFieldText
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputU1.textFieldText)) && parseFloat(inputU1.textFieldText) >= 0 && parseFloat(inputU1.textFieldText) <= 1) {
                                                            inputControllerTimeDist.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputU1.textFieldText)) && parseFloat(inputU1.textFieldText) >= 0 && parseFloat(inputU1.textFieldText) <= 1 / (4 * parseInt(inputN1.textFieldText))) {
                                                            inputControllerTimeDist.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
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
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var v_vec = inputControllerTimeDist.ui_v_vec
                                                    return v_vec[0]
                                                }
                                                textFieldTextEdited: function(){
                                                    var v_vec = []
                                                    v_vec[0] = inputControllerTimeDist.ui_v_vec[0]
                                                    v_vec[1] = inputV1.textFieldText
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputV1.textFieldText)) && parseFloat(inputV1.textFieldText) >= 0 && parseFloat(inputV1.textFieldText) <= 1) {
                                                            inputControllerTimeDist.ui_v_vec = v_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputV1.textFieldText)) && parseFloat(inputV1.textFieldText) >= 0 && parseFloat(inputV1.textFieldText) <= 1 / (4 * parseInt(inputN1.textFieldText))) {
                                                            inputControllerTimeDist.ui_v_vec = v_vec
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
                                                validator: DoubleValidator {bottom: -1; top: 1;}
                                                textFieldText: {
                                                    var s_vec = inputControllerTimeDist.ui_s_vec
                                                    return s_vec[0]
                                                }
                                                textFieldTextEdited: function(){
                                                    var s_vec = []
                                                    s_vec[0] = inputControllerTimeDist.ui_s_vec[0]
                                                    s_vec[1] = inputS1.textFieldText
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputS1.textFieldText)) && parseFloat(inputS1.textFieldText) >= -1 * (2 * parseInt(inputN1.textFieldText)) && parseFloat(inputS1.textFieldText) <= 1 * (2 * parseInt(inputN1.textFieldText))) {
                                                            inputControllerTimeDist.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(parseFloat(!Number.isNaN(Number(inputS1.textFieldText)) && inputS1.textFieldText) >= -1 && parseFloat(inputS1.textFieldText) <= 1) {
                                                            inputControllerTimeDist.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH1
                                                text: Strings.hSub.arg(1) + Strings.colon
                                                toolTipText: Strings.hTooltip
                                                validator: DoubleValidator {bottom: 0; top: 1;}
                                                textFieldText: {
                                                    var h_vec = inputControllerTimeDist.ui_h_vec
                                                    return h_vec[0]
                                                }
                                                textFieldTextEdited: function(){
                                                    var h_vec = []
                                                    h_vec[0] = inputControllerTimeDist.ui_h_vec[0]
                                                    h_vec[1] = inputH1.textFieldText
                                                    if(!Number.isNaN(Number(inputH1.textFieldText)) && parseFloat(inputH1.textFieldText) >= 0 && parseFloat(inputH1.textFieldText) <= 1) {
                                                        inputControllerTimeDist.ui_h_vec = h_vec
                                                        borderColor = "#555555"
                                                    } else {
                                                        borderColor = "#ff0000"
                                                    }
                                                }
                                            }

                                        }
                                    }

                                }
                                onLoaded: function() {
                                    // Load configuration on open here. Wait until everything loaded.
                                    var dummyString = outputControllerTimeDist.ui_load_config
                                    rootTimeDist.updateGUI()
                                    updateScaledParameters(false)
                                    firstLoad = false
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
                                            columns: 2
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
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var u_vec = inputControllerTimeDist.ui_u_vec
                                                    return u_vec[1]
                                                }
                                                textFieldTextEdited: function(){
                                                    var u_vec = []
                                                    u_vec[0] = inputU2.textFieldText
                                                    u_vec[1] = inputControllerTimeDist.ui_u_vec[1]
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputU2.textFieldText)) && parseFloat(inputU2.textFieldText) >= 0 && parseFloat(inputU2.textFieldText) <= 1) {
                                                            inputControllerTimeDist.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputU2.textFieldText)) && parseFloat(inputU2.textFieldText) >= 0 && parseFloat(inputU2.textFieldText) <= 1 / (4 * parseInt(inputN1.textFieldText))) {
                                                            inputControllerTimeDist.ui_u_vec = u_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
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
                                                validator: DoubleValidator {bottom: 0;}
                                                textFieldText: {
                                                    var v_vec = inputControllerTimeDist.ui_v_vec
                                                    return v_vec[1]
                                                }
                                                textFieldTextEdited: function(){
                                                    var v_vec = []
                                                    v_vec[0] = inputV2.textFieldText
                                                    v_vec[1] = inputControllerTimeDist.ui_v_vec[1]
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputV2.textFieldText)) && parseFloat(inputV2.textFieldText) >= 0 && parseFloat(inputV2.textFieldText) <= 1) {
                                                            inputControllerTimeDist.ui_v_vec = v_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputV2.textFieldText)) && parseFloat(inputV2.textFieldText) >= 0 && parseFloat(inputV2.textFieldText) <= 1 / (4 * parseInt(inputN1.textFieldText))) {
                                                            inputControllerTimeDist.ui_v_vec = v_vec
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
                                                validator: DoubleValidator {bottom: -1; top: 1;}
                                                textFieldText: {
                                                    var s_vec = inputControllerTimeDist.ui_s_vec
                                                    return s_vec[1]
                                                }
                                                textFieldTextEdited: function(){
                                                    var s_vec = []
                                                    s_vec[0] = inputS2.textFieldText
                                                    s_vec[1] = inputControllerTimeDist.ui_s_vec[1]
                                                    if(globalConfiguration.ui_population_scaled) {
                                                        if(!Number.isNaN(Number(inputS2.textFieldText)) && parseFloat(inputS2.textFieldText) >= -1 * (2 * parseInt(inputN1.textFieldText)) && parseFloat(inputS2.textFieldText) <= 1 * (2 * parseInt(inputN1.textFieldText))) {
                                                            inputControllerTimeDist.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    } else {
                                                        if(!Number.isNaN(Number(inputS2.textFieldText)) && parseFloat(inputS2.textFieldText) >= -1 && parseFloat(inputS2.textFieldText) <= 1) {
                                                            inputControllerTimeDist.ui_s_vec = s_vec
                                                            borderColor = "#555555"
                                                        } else {
                                                            borderColor = "#ff0000"
                                                        }
                                                    }
                                                }
                                            }

                                            LabeledTextField {
                                                id: inputH2
                                                text: Strings.hSub.arg(2) + Strings.colon
                                                toolTipText: Strings.hTooltip
                                                validator: DoubleValidator {bottom: 0; top: 1;}
                                                textFieldText: {
                                                    var h_vec = inputControllerTimeDist.ui_h_vec
                                                    return h_vec[1]
                                                }
                                                textFieldTextEdited: function(){
                                                    var h_vec = []
                                                    h_vec[0] = inputH2.textFieldText
                                                    h_vec[1] = inputControllerTimeDist.ui_h_vec[1]
                                                    if(!Number.isNaN(Number(inputH2.textFieldText)) && parseFloat(inputH2.textFieldText) >= 0 && parseFloat(inputH2.textFieldText) <= 1) {
                                                        inputControllerTimeDist.ui_h_vec = h_vec
                                                        borderColor = "#555555"
                                                    } else {
                                                        borderColor = "#ff0000"
                                                    }
                                                }
                                            }

                                        }
                                    }

                                }

                            }
                        }

                    }

                    Rectangle {
                        id: populationSection
                        width: modeSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType != "Time Dist. SGV")
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
                                margins: Style.marginSmall
                            }

                            LabeledTextField {
                                id: inputN
                                text: Strings.n + Strings.colon
                                toolTipText: Strings.nTooltip
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerTimeDist.ui_n
                                textFieldTextEdited: function(){
                                    if(parseInt(inputN.textFieldText) > 1) {
                                        inputControllerTimeDist.ui_n = inputN.textFieldText
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
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerTimeDist.ui_a
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA.textFieldText)) && parseFloat(inputA.textFieldText) >= 0) {
                                        inputControllerTimeDist.ui_a = inputA.textFieldText
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
                                textFieldText: inputControllerTimeDist.ui_c
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputC.textFieldText)) && parseFloat(inputC.textFieldText) >= 0) {
                                        inputControllerTimeDist.ui_c = inputC.textFieldText
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
                                textFieldText: inputControllerTimeDist.ui_m
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputM.textFieldText)) && parseFloat(inputM.textFieldText) >= 1) {
                                        inputControllerTimeDist.ui_m = inputM.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                        }

                    }

                    Rectangle {
                        id: separator2column1
                        height: 1
                        width: modeSectionGrid.width + Style.marginSmall
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: timeDistSGVCommonSection
                        width: timeDistSGVSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType == "Time Dist. SGV")
                        color: "transparent"

                        Label {
                            id: labelCommonParameters
                            text: Strings.commonParameters + Strings.colon
                            font.bold: true
                        }

                        GridLayout {
                            id: timeDistSGVCommonSectionGrid
                            columns: 2
                            anchors {
                                top: labelCommonParameters.bottom
                                left: parent.left
                                margins: Style.marginSmall
                            }

                            LabeledTextField {
                                id: inputN1
                                text: Strings.n + Strings.colon
                                toolTipText: Strings.nTooltip
                                validator: IntValidator {bottom: 2; top: 500000;}
                                textFieldText: inputControllerTimeDist.ui_n_sgv
                                textFieldTextEdited: function(){
                                    if(parseInt(inputN1.textFieldText) > 1) {
                                        inputControllerTimeDist.ui_n_sgv = inputN1.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                    for(var i = 0; i < 2; i++) {
                                        // Notify u
                                        timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldTextEdited()
                                        // Notify v
                                        timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldTextEdited()
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputA1
                                text: Strings.a + Strings.colon
                                toolTipText: Strings.aTooltip
                                validator: DoubleValidator {bottom: 0;}
                                textFieldText: inputControllerTimeDist.ui_a_sgv
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputA1.textFieldText)) && parseFloat(inputA1.textFieldText) >= 0) {
                                        inputControllerWfesSweep.ui_a_sgv = inputA1.textFieldText
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
                                textFieldText: inputControllerTimeDist.ui_l
                                enabled: (inputControllerTimeDist.ui_modelType == "Time Dist. SGV")
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputL.textFieldText)) && parseFloat(inputL.textFieldText) >= 1e-20 && parseFloat(inputL.textFieldText) <= 1) {
                                        inputControllerTimeDist.ui_l = inputL.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputC1
                                text: Strings.c + Strings.colon
                                toolTipText: Strings.cTooltip
                                validator: DoubleValidator {bottom: 0; top: 1;}
                                textFieldText: inputControllerTimeDist.ui_c_sgv
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputC1.textFieldText)) && parseFloat(inputC1.textFieldText) >= 0) {
                                        inputControllerTimeDist.ui_c_sgv = inputC1.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledTextField {
                                id: inputM1
                                text: Strings.m + Strings.colon
                                toolTipText: Strings.mTooltip
                                validator: DoubleValidator {bottom: 1;}
                                textFieldText: inputControllerTimeDist.ui_m_sgv
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputM1.textFieldText)) && parseFloat(inputM1.textFieldText) >= 1) {
                                        inputControllerTimeDist.ui_m_sgv = inputM1.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
                                }
                            }

                            LabeledCheckBox {
                                id: inputR1
                                text: Strings.rMut + Strings.colon
                                toolTipText: Strings.rMutTooltip
                                checked: inputControllerTimeDist.ui_r_sgv
                            }
                        }
                    }

                    Rectangle {
                        id: mutationSection
                        width: populationSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType != "Time Dist. SGV")
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
                                margins: Style.marginSmall
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
                                textFieldText: inputControllerTimeDist.ui_u
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1) {
                                            inputControllerTimeDist.ui_u = inputU.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                            inputControllerTimeDist.ui_u = inputU.textFieldText
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
                                textFieldText: inputControllerTimeDist.ui_v
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1) {
                                            inputControllerTimeDist.ui_v = inputV.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                            inputControllerTimeDist.ui_v = inputV.textFieldText
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
                                checked: inputControllerTimeDist.ui_r
                            }
                        }
                    }

                    Rectangle {
                        id: separator3column1
                        height: 1
                        width: modeSectionGrid.width + Style.marginSmall
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: selectionSection
                        width: mutationSection.width
                        height: childrenRect.height

                        visible: (inputControllerTimeDist.ui_modelType != "Time Dist. SGV")
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
                                margins: Style.marginSmall
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
                                textFieldText: inputControllerTimeDist.ui_s
                                textFieldTextEdited: function(){
                                    if(globalConfiguration.ui_population_scaled) {
                                        if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                            inputControllerTimeDist.ui_s = inputS.textFieldText
                                            borderColor = "#555555"
                                        } else {
                                            borderColor = "#ff0000"
                                        }
                                    } else {
                                        if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 && parseFloat(inputS.textFieldText) <= 1) {
                                            inputControllerTimeDist.ui_s = inputS.textFieldText
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
                                textFieldText: inputControllerTimeDist.ui_h
                                textFieldTextEdited: function(){
                                    if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= 0 && parseFloat(inputH.textFieldText) <= 1) {
                                        inputControllerTimeDist.ui_h = inputH.textFieldText
                                        borderColor = "#555555"
                                    } else {
                                        borderColor = "#ff0000"
                                    }
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
                    Layout.alignment: Qt.AlignTop

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
                                    checked: inputControllerTimeDist.ui_output_Q
                                }

                                LabeledCheckBox {
                                    id: inputWriteR
                                    text: Strings.outputR + Strings.colon
                                    toolTipText: Strings.outputRTooltip
                                    checked: inputControllerTimeDist.ui_output_R
                                }

                                LabeledCheckBox {
                                    id: inputWriteP
                                    text: Strings.outputP + Strings.colon
                                    toolTipText: Strings.outputPTooltip
                                    checked: true
                                    enabledCheckBox: false
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
                                        checked: inputControllerTimeDist.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: Strings.t + Strings.colon
                                        toolTipText: Strings.tTooltip
                                        textFieldPreferredWidth: 100
                                        validator: DoubleValidator {bottom: 1;}
                                        textFieldText: inputControllerTimeDist.ui_t
                                        textFieldTextEdited: function(){
                                            if(parseInt(inputT.textFieldText) >= 1) {
                                                inputControllerTimeDist.ui_t = inputT.textFieldText
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
                            Layout.margins: Style.marginSmall
                            Layout.alignment: Qt.AlignRight
                            text: Strings.stopButton

                            Binding {
                                target: stopButton
                                property: "enabled"
                                value: !outputControllerTimeDist.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerTimeDist.ui_stop
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
                                if(outputControllerTimeDist.ui_get_not_exec)
                                    imageOutputController.image_changed()
                                console.log(outputControllerTimeDist.ui_get_error_message)
                                if(outputControllerTimeDist.ui_get_error_message !== "") {
                                    messageDialog.text = outputControllerTimeDist.ui_get_error_message
                                    messageDialog.open()
                                    outputControllerTimeDist.ui_reset_error
                                }
                                upperMenu.updateProbTimeDist(inputControllerTimeDist.ui_modelType)
                                if(enabled)
                                    upperMenu.chartVisible = true
                            }

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerTimeDist.ui_get_not_exec
                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                var error = checkIntegrity()


                                if(error === "") {
                                    updateBackend()
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    bottomMenu.visibleProgressBar = true
                                    outputControllerTimeDist.ui_execute
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
                    text: ""
                    icon: StandardIcon.Warning
                }

            }

        }


        Rectangle {
            height: 1
            width: parent.width
            color: Universal.baseHighColor
            anchors {
                top: bottomMenu.top
                left: parent.left
            }
        }

        Binding {
            target: bottomMenu
            property: "visibleProgressBar"
            value: !outputControllerTimeDist.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            height: 35
            executionProgress: outputControllerTimeDist.ui_progress

            anchors {
                bottom: parent.bottom
                left: parent.left
            }

            executionTime: {
                outputControllerTimeDist.ui_get_time == "" ? "" : outputControllerTimeDist.ui_get_time + "s"
            }
        }
    }

    function updateGUI() {
        //First, let's fill the SGV parameters.
        radioButtonTimeDistSGV.checked = true
        radioButtonTimeDist.checked = false
        radioButtonTimeDistDual.checked = false
        radioButtonTimeDistSkip.checked = false

        inputN1.textFieldText = inputControllerTimeDist.ui_n_sgv
        inputA1.textFieldText = inputControllerTimeDist.ui_a_sgv
        inputL.textFieldText = inputControllerTimeDist.ui_l
        inputC1.textFieldText = inputControllerTimeDist.ui_c_sgv
        inputM1.textFieldText = inputControllerTimeDist.ui_m_sgv
        inputR1.checked = inputControllerTimeDist.ui_r_sgv
        var u_vec = inputControllerTimeDist.ui_u_vec
        var v_vec = inputControllerTimeDist.ui_v_vec
        var s_vec = inputControllerTimeDist.ui_s_vec
        var h_vec = inputControllerTimeDist.ui_h_vec
        for(var i = 0; i < 2; i++) {
            timeDistSGVSectionTabView.getTab(i).active = true
            timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
            timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
            timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
            timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText = h_vec[i]
        }

        //And second, the rest of parameters.
        radioButtonTimeDist.checked = true
        radioButtonTimeDistDual.checked = false
        radioButtonTimeDistSkip.checked = false
        radioButtonTimeDistSGV.checked = false
        inputN.textFieldText = inputControllerTimeDist.ui_n
        inputA.textFieldText = inputControllerTimeDist.ui_a
        inputC.textFieldText = inputControllerTimeDist.ui_c
        inputM.textFieldText = inputControllerTimeDist.ui_m
        inputU.textFieldText = inputControllerTimeDist.ui_u
        inputV.textFieldText = inputControllerTimeDist.ui_v
        inputR.checked = inputControllerTimeDist.ui_r
        inputS.textFieldText = inputControllerTimeDist.ui_s
        inputH.textFieldText = inputControllerTimeDist.ui_h

        inputWriteQ.checked = inputControllerTimeDist.ui_output_Q
        inputWriteR.checked = inputControllerTimeDist.ui_output_R
        inputWriteP.checked = inputControllerTimeDist.ui_output_P

        inputForce.checked = inputControllerTimeDist.ui_force

        inputT.textFieldText = inputControllerTimeDist.ui_t
        var library = inputControllerTimeDist.ui_library
        if(library === "Pardiso")
            comboBoxLibrary.currentIndex = 0
        else if(library === "ViennaCL")
            comboBoxLibrary.currentIndex = 1

        radioButtonTimeDist.checked = inputControllerTimeDist.ui_modelType == "Time Dist."
        radioButtonTimeDistDual.checked = inputControllerTimeDist.ui_modelType == "Time Dist. Dual"
        radioButtonTimeDistSGV.checked = inputControllerTimeDist.ui_modelType == "Time Dist. SGV"
        radioButtonTimeDistSkip.checked = inputControllerTimeDist.ui_modelType == "Time Dist. Skip"

        // Update boxes.
        for(i = 0; i < 2; i++) {
            timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldTextEdited()
            timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldTextEdited()
            timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldTextEdited()
            timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldTextEdited()
        }
        inputN1.textFieldTextEdited()
        inputA1.textFieldTextEdited()
        inputL.textFieldTextEdited()
        inputC1.textFieldTextEdited()
        inputM1.textFieldTextEdited()

        inputN.textFieldTextEdited()
        inputA.textFieldTextEdited()
        inputC.textFieldTextEdited()
        inputM.textFieldTextEdited()
        inputU.textFieldTextEdited()
        inputV.textFieldTextEdited()
        inputS.textFieldTextEdited()
        inputH.textFieldTextEdited()
        inputT.textFieldTextEdited()


    }

    function updateBackend() {
        if(radioButtonTimeDist.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist."
        if(radioButtonTimeDistSGV.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist. SGV"
        if(radioButtonTimeDistSkip.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist. Skip"
        if(radioButtonTimeDistDual.checked)
            inputControllerTimeDist.ui_modelType = "Time Dist. Dual"

        inputControllerTimeDist.ui_n = inputN.textFieldText
        inputControllerTimeDist.ui_a = inputA.textFieldText
        inputControllerTimeDist.ui_c = inputC.textFieldText
        inputControllerTimeDist.ui_m = inputM.textFieldText
        inputControllerTimeDist.ui_u = inputU.textFieldText
        inputControllerTimeDist.ui_v = inputV.textFieldText
        inputControllerTimeDist.ui_r = inputR.checked
        inputControllerTimeDist.ui_s = inputS.textFieldText
        inputControllerTimeDist.ui_h = inputH.textFieldText

        inputControllerTimeDist.ui_n_sgv = inputN1.textFieldText
        inputControllerTimeDist.ui_a_sgv = inputA1.textFieldText
        inputControllerTimeDist.ui_l = inputL.textFieldText
        inputControllerTimeDist.ui_c_sgv = inputC1.textFieldText
        inputControllerTimeDist.ui_m_sgv = inputM1.textFieldText
        inputControllerTimeDist.ui_r_sgv = inputR1.checked
        var u_vec = []
        var v_vec = []
        var s_vec = []
        var h_vec = []
        for(var i = 0; i < 2; i++) {
            timeDistSGVSectionTabView.getTab(i).active = true
            var u = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
            var v = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
            var s = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
            var h = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
            u_vec.push(u)
            v_vec.push(v)
            s_vec.push(s)
            h_vec.push(h)
        }
        inputControllerTimeDist.ui_u_vec = u_vec
        inputControllerTimeDist.ui_v_vec = v_vec
        inputControllerTimeDist.ui_s_vec = s_vec
        inputControllerTimeDist.ui_h_vec = h_vec


        inputControllerTimeDist.ui_output_P = inputWriteP.checked
        inputControllerTimeDist.ui_output_Q = inputWriteQ.checked
        inputControllerTimeDist.ui_output_R = inputWriteR.checked

        inputControllerTimeDist.ui_t = inputT.textFieldText

        inputControllerTimeDist.ui_library = comboBoxLibrary.currentText;

        inputControllerTimeDist.ui_force = inputForce.checked

    }

    function checkIntegrity() {
        var error = ""

        if(!radioButtonTimeDistSGV.checked) {
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
            if(!inputForce.checked && parseFloat(inputM.textFieldText) > 50000)
                error += Strings.hyphen + Strings.mIsLarge + Strings.endOfError

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
        } else {
            if(inputN1.textFieldText == "")
                error += Strings.hyphen + Strings.nSGVIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputN1.textFieldText)))
                error += Strings.hyphen + Strings.nSGVIsNotValid + Strings.endOfError
            if(parseInt(inputN1.textFieldText) < 2)
                error += Strings.hyphen + Strings.nSGVIsSmall + Strings.endOfError
            if(!inputForce.checked && parseInt(inputN1.textFieldText) > 50000)
                error += Strings.hyphen + Strings.nSGVIsLarge + Strings.endOfError

            if(inputL.textFieldText == "")
                error += Strings.hyphen + Strings.lSGVIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputL.textFieldText)))
                error += Strings.hyphen + Strings.lSGVIsNotValid + Strings.endOfError
            if(parseFloat(inputL.textFieldText) < 1e-20)
                error += Strings.hyphen + Strings.lSGVIsSmall + Strings.endOfError
            if(parseFloat(inputL.textFieldText) > 1)
                error += Strings.hyphen + Strings.lSGVIsLarge + Strings.endOfError

            if(inputA1.textFieldText == "")
                error += Strings.hyphen + Strings.aSGVIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputA1.textFieldText)))
                error += Strings.hyphen + Strings.aSGVIsNotValid + Strings.endOfError
            if(parseFloat(inputA1.textFieldText) < 0)
                error += Strings.hyphen + Strings.aSGVIsSmall + Strings.endOfError
            if(!inputForce.checked && parseFloat(inputA1.textFieldText) > 1e-5)
                error += Strings.hyphen + Strings.aSGVIsLarge + Strings.endOfError

            if(inputC1.textFieldText == "")
                error += Strings.hyphen + Strings.cSGVIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputC1.textFieldText)))
                error += Strings.hyphen + Strings.cSGVIsNotValid + Strings.endOfError
            if(parseFloat(inputC1.textFieldText) <= 0)
                error += Strings.hyphen + Strings.cSGVIsSmall + Strings.endOfError
            if(parseFloat(inputC1.textFieldText) > 1)
                error += Strings.hyphen + Strings.cSGVIsLarge + Strings.endOfError

            if(inputM1.textFieldText == "")
                error += Strings.hyphen + Strings.mSGVIsEmpty + Strings.endOfError
            if(Number.isNaN(Number(inputM1.textFieldText)))
                error += Strings.hyphen + Strings.mSGVIsNotValid + Strings.endOfError
            if(parseFloat(inputM1.textFieldText) < 1)
                error += Strings.hyphen + Strings.mSGVIsSmall + Strings.endOfError
            if(!inputForce.checked && parseFloat(inputM1.textFieldText) > 50000)
                error += Strings.hyphen + Strings.mSGVIsLarge + Strings.endOfError

            var u_vec = []
            var v_vec = []
            var s_vec = []
            var h_vec = []
            for(var i = 0; i < 2; i++) {
                timeDistSGVSectionTabView.getTab(i).active = true
                var u = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                var v = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                var s = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                var h = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
                u_vec.push(u)
                v_vec.push(v)
                s_vec.push(s)
                h_vec.push(h)
            }

            if(globalConfiguration.ui_population_scaled) {
                for(i = 0; i < 2; i++) {
                    u = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                    if(u === "")
                        error += Strings.hyphen + Strings.uSGVisEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(u_vec[i])))
                        error += Strings.hyphen + Strings.uSGVisNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(u_vec[i]) <= 0)
                        error += Strings.hyphen + Strings.uSGVisSmall.arg(i + 1) + Strings.endOfError
                    if(!inputForce.checked && parseFloat(u_vec[i]) > 1)
                        error += Strings.hyphen + Strings.uSGVisLargeScaled.arg(i + 1) + Strings.endOfError
                }

                for(i = 0; i < 2; i++) {
                    v = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                    if(v === "")
                        error += Strings.hyphen + Strings.vSGVisEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(v_vec[i])))
                        error += Strings.hyphen + Strings.vSGVisNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(v_vec[i]) <= 0)
                        error += Strings.hyphen + Strings.vSGVisSmall.arg(i + 1) + Strings.endOfError
                    if(!inputForce.checked && parseFloat(v_vec[i]) > 1)
                        error += Strings.hyphen + Strings.vSGVisLargeScaled.arg(i + 1) + Strings.endOfError
                }

                for(i = 0; i < 2; i++) {
                    s = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                    if(s === "")
                        error += Strings.hyphen + Strings.sSGVisEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(s_vec[i])))
                        error += Strings.hyphen + Strings.sSGVisNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(s_vec[i]) < -1 * (2 * parseInt(inputN.textFieldText)))
                        error += Strings.hyphen + Strings.sSGVisSmall.arg(i + 1) + Strings.endOfError
                    if(parseFloat(s_vec[i]) > 1 * (2 * parseInt(inputN.textFieldText)))
                        error += Strings.hyphen + Strings.sSGVisLargeScaled.arg(i + 1) + Strings.endOfError
                }
            } else {
                for(i = 0; i < 2; i++) {
                    u = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText
                    if(u === "")
                        error += Strings.hyphen + Strings.uSGVisEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(u_vec[i])))
                        error += Strings.hyphen + Strings.uSGVisNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(u_vec[i]) <= 0)
                        error += Strings.hyphen + Strings.uSGVisSmall.arg(i + 1) + Strings.endOfError
                    if(!inputForce.checked && parseFloat(u_vec[i]) > 1 / (4 * parseInt(inputN.textFieldText)))
                        error += Strings.hyphen + Strings.uSGVisLarge.arg(i + 1) + Strings.endOfError
                }

                for(i = 0; i < 2; i++) {
                    v = timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText
                    if(v === "")
                        error += Strings.hyphen + Strings.vSGVisEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(v_vec[i])))
                        error += Strings.hyphen + Strings.vSGVisNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(v_vec[i]) <= 0)
                        error += Strings.hyphen + Strings.vSGVisSmall.arg(i + 1) + Strings.endOfError
                    if(!inputForce.checked && parseFloat(v_vec[i]) > 1 / (4 * parseInt(inputN.textFieldText)))
                        error += Strings.hyphen + Strings.vSGVisLarge.arg(i + 1) + Strings.endOfError
                }

                for(i = 0; i < 2; i++) {
                    s = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText
                    if(s === "")
                        error += Strings.hyphen + Strings.sSGVisEmpty.arg(i + 1) + Strings.endOfError
                    if(Number.isNaN(Number(s_vec[i])))
                        error += Strings.hyphen + Strings.sSGVisNotValid.arg(i + 1) + Strings.endOfError
                    if(parseFloat(s_vec[i]) < -1)
                        error += Strings.hyphen + Strings.sSGVisSmall.arg(i + 1) + Strings.endOfError
                    if(parseFloat(s_vec[i]) > 1 )
                        error += Strings.hyphen + Strings.vSGVisLarge.arg(i + 1) + Strings.endOfError
                }
            }

            for(i = 0; i < 2; i++) {
                h = timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[1].textFieldText
                if(h === "")
                    error += Strings.hyphen + Strings.hSGVisEmpty.arg(i + 1) + Strings.endOfError
                if(Number.isNaN(Number(h_vec[i])))
                    error += Strings.hyphen + Strings.hSGVisNotValid.arg(i + 1) + Strings.endOfError
                if(parseFloat(h_vec[i]) < 0)
                    error += Strings.hyphen + Strings.hSGVisSmall.arg(i + 1) + Strings.endOfError
                if(parseFloat(h_vec[i]) > 1)
                    error += Strings.hyphen + Strings.hSGVisLarge.arg(i + 1) + Strings.endOfError
            }


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
        for(var i = 0; i < 2; i++) {
            if(typeof(timeDistSGVSectionTabView.getTab(i)) === "undefined") {
                loadedComponents = false
            }

        }
        if(loadedComponents) {
            var u, v, s
            var u_vec, v_vec, s_vec = []
            if(globalConfiguration.ui_population_scaled) {
                inputControllerTimeDist.ui_s = parseFloat(inputControllerTimeDist.ui_s) * (2 * parseInt(inputControllerTimeDist.ui_n))
                inputS.textFieldText = inputControllerTimeDist.ui_s
                inputControllerTimeDist.ui_u = parseFloat(inputControllerTimeDist.ui_u) * (4 * parseInt(inputControllerTimeDist.ui_n))
                inputU.textFieldText = inputControllerTimeDist.ui_u
                inputControllerTimeDist.ui_v = parseFloat(inputControllerTimeDist.ui_v) * (4 * parseInt(inputControllerTimeDist.ui_n))
                inputV.textFieldText = inputControllerTimeDist.ui_v

                u = inputControllerTimeDist.ui_u_vec
                v = inputControllerTimeDist.ui_v_vec
                s = inputControllerTimeDist.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < 2; i++) {
                    timeDistSGVSectionTabView.getTab(i).active = true
                    u_vec.push((u[i] * (4 * parseInt(inputControllerTimeDist.ui_n_sgv))).toString())
                    v_vec.push((v[i] * (4 * parseInt(inputControllerTimeDist.ui_n_sgv))).toString())
                    s_vec.push((s[i] * (2 * parseInt(inputControllerTimeDist.ui_n_sgv))).toString())
                    timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
                    timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
                    timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerTimeDist.ui_u_vec = u_vec
                inputControllerTimeDist.ui_v_vec = v_vec
                inputControllerTimeDist.ui_s_vec = s_vec


            } else if(updateNonChecked){
                inputControllerTimeDist.ui_s = parseFloat(inputControllerTimeDist.ui_s) / (2 * parseInt(inputControllerTimeDist.ui_n))
                inputS.textFieldText = inputControllerTimeDist.ui_s
                inputControllerTimeDist.ui_u = parseFloat(inputControllerTimeDist.ui_u) / (4 * parseInt(inputControllerTimeDist.ui_n))
                inputU.textFieldText = inputControllerTimeDist.ui_u
                inputControllerTimeDist.ui_v = parseFloat(inputControllerTimeDist.ui_v) / (4 * parseInt(inputControllerTimeDist.ui_n))
                inputV.textFieldText = inputControllerTimeDist.ui_v


                u = inputControllerTimeDist.ui_u_vec
                v = inputControllerTimeDist.ui_v_vec
                s = inputControllerTimeDist.ui_s_vec
                u_vec = []
                v_vec = []
                s_vec = []
                for(i = 0; i < 2; i++) {
                    timeDistSGVSectionTabView.getTab(i).active = true
                    u_vec.push((u[i] / (4 * parseInt(inputControllerTimeDist.ui_n_sgv))).toString())
                    v_vec.push((v[i] / (4 * parseInt(inputControllerTimeDist.ui_n_sgv))).toString())
                    s_vec.push((s[i] / (2 * parseInt(inputControllerTimeDist.ui_n_sgv))).toString())
                    timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[0].textFieldText = u_vec[i]
                    timeDistSGVSectionTabView.getTab(i).item.children[0].children[1].children[1].textFieldText = v_vec[i]
                    timeDistSGVSectionTabView.getTab(i).item.children[1].children[1].children[0].textFieldText = s_vec[i]
                }
                inputControllerTimeDist.ui_u_vec = u_vec
                inputControllerTimeDist.ui_v_vec = v_vec
                inputControllerTimeDist.ui_s_vec = s_vec

            }
        }
    }
}
