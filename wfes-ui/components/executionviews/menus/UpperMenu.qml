import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0

Rectangle {
    property alias chartVisible: chartVisualization.visible
    id: upperMenu
    width:parent.width
    height: childrenRect.height
    color: "lightgrey"

    MessageDialog {
        id: messageDialogOnCloseUpperMenu
        title: "Warning"
        text: ""
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok
    }


    RowLayout {
        height: childrenRect.height
        spacing: 0

        Button {
            id: settingsButton
            text: "Settings"
            onClicked: menu2.open()
            
            Menu {
                id: menu2
                y: settingsButton.height
                
                MenuItem {
                    text: "Save Config..."
                    onClicked: {
                        var text;
                        //Check for active view and save config.
                        if(typeof(rootWfesSingle) != "undefined") {
                            text = rootWfesSingle.checkIntegrity()
                            if(text === "") {
                                rootWfesSingle.updateBackend()
                                outputControllerWfesSingle.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfesSequential) != "undefined") {
                            text = rootWfesSequential.checkIntegrity()
                            if(text === "") {
                                rootWfesSequential.updateBackend()
                                outputControllerWfesSequential.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfesSweep) != "undefined") {
                            text = rootWfesSweep.checkIntegrity()
                            if(text === "") {
                                rootWfesSweep.updateBackend()
                                outputControllerWfesSweep.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfesSwitching) != "undefined") {
                            text = rootWfesSwitching.checkIntegrity()
                            if(text === "") {
                                rootWfesSwitching.updateBackend()
                                outputControllerWfesSwitching.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfafs) != "undefined") {
                            text = rootWfafs.checkIntegrity()
                            if(text === "") {
                                rootWfafs.updateBackend()
                                outputControllerWfafs.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfafd) != "undefined") {
                            text = rootWfafd.checkIntegrity()
                            if(text === "") {
                                rootWfafd.updateBackend()
                                outputControllerWfafd.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootTimeDist) != "undefined") {
                            text = rootTimeDist.checkIntegrity()
                            if(text === "") {
                                rootTimeDist.updateBackend()
                                outputControllerTimeDist.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootPhaseType) != "undefined") {
                            text = rootPhaseType.checkIntegrity()
                            if(text === "") {
                                rootPhaseType.updateBackend()
                                outputControllerPhaseType.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = "Some input parameters are incorrect. The configuration cannot be saved until you fix those values."
                                messageDialogOnCloseUpperMenu.open()
                            }
                        }
                    }
                }
                MenuItem {
                    text: "Load Config..."
                    onClicked: {
                        //Check for active view and load config.
                        if(typeof(rootWfesSingle) != "undefined") {
                            outputControllerWfesSingle.ui_load_config
                            rootWfesSingle.updateGUI()
                        } else if(typeof(rootWfesSequential) != "undefined") {
                            outputControllerWfesSequential.ui_load_config
                            rootWfesSequential.updateGUI()
                        } else if(typeof(rootWfesSweep) != "undefined") {
                            outputControllerWfesSweep.ui_load_config
                            rootWfesSweep.updateGUI()
                        } else if(typeof(rootWfesSwitching) != "undefined") {
                            outputControllerWfesSwitching.ui_load_config
                            rootWfesSwitching.updateGUI()
                        } else if(typeof(rootWfafs) != "undefined") {
                            outputControllerWfafs.ui_load_config
                            rootWfafs.updateGUI()
                        } else if(typeof(rootWfafd) != "undefined") {
                            outputControllerWfafd.ui_load_config
                            rootWfafd.updateGUI()
                        } else if(typeof(rootTimeDist) != "undefined") {
                            outputControllerTimeDist.ui_load_config
                            rootTimeDist.updateGUI()
                        } else if(typeof(rootPhaseType) != "undefined") {
                            outputControllerPhaseType.ui_load_config
                            rootPhaseType.updateGUI()
                        }
                    }
                }


                MenuItem {
                    CheckBox {
                        anchors.fill: parent
                        text: "Generate Images"
                        checked: globalConfiguration.ui_generate_images

                        ToolTip.visible: hovered
                        ToolTip.delay: Style.tooltipDelay
                        ToolTip.timeout: Style.tooltipTimeout
                        ToolTip.text: qsTr("Generate matrix/vector images.")

                        onCheckedChanged: {
                            if(globalConfiguration.ui_generate_images !== this.checked) {
                                globalConfiguration.ui_generate_images = this.checked
                                globalConfiguration.generateImagesChanged()
                            }
                            menu2.dismiss()
                        }
                    }
                }

                MenuItem {
                    CheckBox {
                        anchors.fill: parent
                        text: "Population-Scaled"
                        checked: globalConfiguration.ui_population_scaled

                        ToolTip.visible: hovered
                        ToolTip.delay: Style.tooltipDelay
                        ToolTip.timeout: Style.tooltipTimeout
                        ToolTip.text: qsTr("Use population-scaled parameters.")

                        onCheckedChanged: {
                            // Update other windows.
                            if(globalConfiguration.ui_population_scaled !== this.checked) {
                                globalConfiguration.ui_population_scaled = this.checked
                                globalConfiguration.populationScaledChanged()
                            }

                            // Update scaled parameters.
                            if(typeof(rootPhaseType) != "undefined") {
                                if(rootPhaseType.firstLoad) {
                                    rootPhaseType.updateScaledParameters(false)
                                    rootPhaseType.firstLoad = false
                                } else {
                                    rootPhaseType.updateScaledParameters(true)
                                }
                            }
                            if(typeof(rootTimeDist) != "undefined") {
                                if(!rootTimeDist.firstLoad) {
                                    rootTimeDist.updateScaledParameters(true)
                                }
                            }
                            if(typeof(rootWfafs) != "undefined") {
                                rootWfafs.updateScaledParameters(true)
                            }
                            if(typeof(rootWfafd) != "undefined") {
                                rootWfafd.updateScaledParameters(true)
                            }
                            if(typeof(rootWfesSingle) != "undefined") {
                                if(rootWfesSingle.firstLoad) {
                                    rootWfesSingle.updateScaledParameters(false)
                                    rootWfesSingle.firstLoad = false
                                } else {
                                    rootWfesSingle.updateScaledParameters(true)
                                }
                            }
                            if(typeof(rootWfesSequential) != "undefined") {
                                rootWfesSequential.updateScaledParameters(true)
                            }
                            if(typeof(rootWfesSwitching) != "undefined") {
                                rootWfesSwitching.updateScaledParameters(true)
                            }
                            if(typeof(rootWfesSweep) != "undefined") {
                                rootWfesSweep.updateScaledParameters(true)
                            }
                            menu2.dismiss()
                        }
                    }
                }

//                MenuItem {
//                    text: "Global Settings"
//                    onClicked: {
//                        console.warn("WARNING: Settings->Global Settings clicked - Not implemented yet.")
//                    }
//                }
            }
        }

        Button {
            id: viewButton
            text: "View"
            onClicked: menu3.open()

            Menu {
                id: menu3
                y: settingsButton.height

                MenuItem {
                    text: "Matrix Visualization"
                    onClicked: {
                        matrixVisualization.visible = true
                    }
                }

                MenuItem {
                    text: "Chart Visualization"
                    onClicked: {
                        chartVisualization.visible = true
                    }
                }


            }
        }
        


        Button {
            id: switchButton
            text: "Windows"
            onClicked: menu5.open()

            Menu {
                id: menu5
                y: helpButton.height


                MenuItem {
                    text: "Main Window"
                    visible: typeof(root) != "undefined" && root.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        root.raise()
                        // Center window in screen.
                        root.setX(Screen.width / 2 - root.width / 2);
                        root.setY(Screen.height / 2 - root.height / 2);
                    }
                }
                MenuItem {
                    text: "WFES Single"
                    visible: typeof(wfesSingleView) != "undefined" && wfesSingleView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSingleView.raise()
                        // Center window in screen.
                        wfesSingleView.setX(Screen.width / 2 - wfesSingleView.width / 2);
                        wfesSingleView.setY(Screen.height / 2 - wfesSingleView.height / 2);
                    }
                }
                MenuItem {
                    text: "WFES Sequential"
                    visible: typeof(wfesSequential) != "undefined" && wfesSequential.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSequential.raise()
                        // Center window in screen.
                        wfesSequential.setX(Screen.width / 2 - wfesSequential.width / 2);
                        wfesSequential.setY(Screen.height / 2 - wfesSequential.height / 2);
                    }
                }
                MenuItem {
                    text: "WFES Sweep"
                    visible: typeof(wfesSweep) != "undefined" && wfesSweep.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSweep.raise()
                        // Center window in screen.
                        wfesSweep.setX(Screen.width / 2 - wfesSweep.width / 2);
                        wfesSweep.setY(Screen.height / 2 - wfesSweep.height / 2);
                    }
                }
                MenuItem {
                    text: "WFES Switching"
                    visible: typeof(wfesSwitching) != "undefined" && wfesSwitching.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSwitching.raise()
                        // Center window in screen.
                        wfesSwitching.setX(Screen.width / 2 - wfesSwitching.width / 2);
                        wfesSwitching.setY(Screen.height / 2 - wfesSwitching.height / 2);
                    }
                }
                MenuItem {
                    text: "WFAF-S"
                    visible: typeof(wfafsView) != "undefined" && wfafsView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfafsView.raise()
                        // Center window in screen.
                        wfafsView.setX(Screen.width / 2 - wfafsView.width / 2);
                        wfafsView.setY(Screen.height / 2 - wfafsView.height / 2);
                    }
                }
                MenuItem {
                    text: "WFAF-D"
                    visible: typeof(wfafdView) != "undefined" && wfafdView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfafdView.raise()
                        // Center window in screen.
                        wfafdView.setX(Screen.width / 2 - wfafdView.width / 2);
                        wfafdView.setY(Screen.height / 2 - wfafdView.height / 2);
                    }
                }
                MenuItem {
                    text: "Time Dist."
                    visible: typeof(timeDistView) != "undefined" && timeDistView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        timeDistView.raise()
                        // Center window in screen.
                        timeDistView.setX(Screen.width / 2 - timeDistView.width / 2);
                        timeDistView.setY(Screen.height / 2 - timeDistView.height / 2);
                    }
                }
                MenuItem {
                    text: "Phase Type"
                    visible: typeof(phaseTypeView) != "undefined" && phaseTypeView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        phaseTypeView.raise()
                        // Center window in screen.
                        phaseTypeView.setX(Screen.width / 2 - phaseTypeView.width / 2);
                        phaseTypeView.setY(Screen.height / 2 - phaseTypeView.height / 2);
                    }
                }
            }
        }


        Button {
            id: helpButton
            text: "Help"
            onClicked: menu4.open()

            Menu {
                id: menu4
                y: helpButton.height


                MenuItem {
                    text: "Manual"
                    onClicked: {
                        Qt.openUrlExternally("https://github.com/dekoning-lab/wfes-gui/wiki");
                    }
                }
                MenuItem {
                    text: "About"
                    onClicked: {
                        helpView.visible = true
                    }
                }
            }
        }

    }

    ChartVisualization {
        id:chartVisualization
        visibleWindow: false
    }

    MatrixVisualization {
        id:matrixVisualization
        visibleWindow: false
    }

    HelpView {
        id:helpView
        visibleWindow: false
    }

    function updateDistWfafs() {
        chartVisualization.updateDistWfafs()
    }

    function updateDistWfafd() {
        chartVisualization.updateDistWfafd()
    }

    function updateProbTimeDist(name) {
        chartVisualization.updateProbTimeDist(name)
    }

    function updatePhaseTypeDistChart() {
        chartVisualization.updatePhaseTypeDistChart()
    }
}
