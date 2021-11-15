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
    property alias matrixVisible: matrixVisualization.visible
    id: upperMenu
    width:parent.width
    height: childrenRect.height
    color: "lightgrey"

    MessageDialog {
        id: messageDialogOnCloseUpperMenu
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok
    }


    RowLayout {
        height: childrenRect.height
        spacing: 0

        Button {
            id: settingsButton
            text: Strings.upperMenuSettingsButton
            onClicked: menu2.open()
            Menu {
                id: menu2
                y: settingsButton.height
                
                MenuItem {
                    text: Strings.upperMenuSaveConfigButton
                    onClicked: {
                        var text;
                        //Check for active view and save config.
                        if(typeof(rootWfesSingle) != "undefined") {
                            text = rootWfesSingle.checkIntegrity()
                            if(text === "") {
                                rootWfesSingle.updateBackend()
                                outputControllerWfesSingle.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfesSequential) != "undefined") {
                            text = rootWfesSequential.checkIntegrity()
                            if(text === "") {
                                rootWfesSequential.updateBackend()
                                outputControllerWfesSequential.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfesSweep) != "undefined") {
                            text = rootWfesSweep.checkIntegrity()
                            if(text === "") {
                                rootWfesSweep.updateBackend()
                                outputControllerWfesSweep.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfesSwitching) != "undefined") {
                            text = rootWfesSwitching.checkIntegrity()
                            if(text === "") {
                                rootWfesSwitching.updateBackend()
                                outputControllerWfesSwitching.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfafs) != "undefined") {
                            text = rootWfafs.checkIntegrity()
                            if(text === "") {
                                rootWfafs.updateBackend()
                                outputControllerWfafs.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootWfafd) != "undefined") {
                            text = rootWfafd.checkIntegrity()
                            if(text === "") {
                                rootWfafd.updateBackend()
                                outputControllerWfafd.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootTimeDist) != "undefined") {
                            text = rootTimeDist.checkIntegrity()
                            if(text === "") {
                                rootTimeDist.updateBackend()
                                outputControllerTimeDist.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        } else if(typeof(rootPhaseType) != "undefined") {
                            text = rootPhaseType.checkIntegrity()
                            if(text === "") {
                                rootPhaseType.updateBackend()
                                outputControllerPhaseType.ui_save_config
                            } else {
                                messageDialogOnCloseUpperMenu.text = Strings.upperMenuIncorrectInputParameters
                                messageDialogOnCloseUpperMenu.open()
                            }
                        }
                    }
                }
                MenuItem {
                    text: Strings.upperMenuLoadConfigButton
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
                        text: Strings.upperMenuGenerateImagesCheckBox
                        checked: globalConfiguration.ui_generate_images

                        ToolTip.visible: hovered
                        ToolTip.delay: Style.tooltipDelay
                        ToolTip.timeout: Style.tooltipTimeout
                        ToolTip.text: Strings.upperMenuGenerateImagesCheckBoxTooltip

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
                        text: Strings.upperMenuPopulationScaledCheckBox
                        checked: globalConfiguration.ui_population_scaled

                        ToolTip.visible: hovered
                        ToolTip.delay: Style.tooltipDelay
                        ToolTip.timeout: Style.tooltipTimeout
                        ToolTip.text: Strings.upperMenuPopulationScaledCheckBoxTooltip

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
            text: Strings.upperMenuViewButton
            onClicked: menu3.open()

            Menu {
                id: menu3
                y: settingsButton.height

                MenuItem {
                    text: Strings.upperMenuMatrixVisualizationButton
                    onClicked: {
                        matrixVisualization.visible = true
                    }
                }

                MenuItem {
                    text: Strings.upperMenuChartVisualizationButton
                    onClicked: {
                        chartVisualization.visible = true
                    }
                }


            }
        }
        


        Button {
            id: switchButton
            text: Strings.upperMenuWindowsButton
            onClicked: menu5.open()

            Menu {
                id: menu5
                y: helpButton.height


                MenuItem {
                    text: Strings.mainWindow
                    visible: typeof(root) != "undefined" && root.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        root.raise()
                        root.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.wfesSingle
                    visible: typeof(wfesSingleView) != "undefined" && wfesSingleView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSingleView.raise()
                        wfesSingleView.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.wfesSequential
                    visible: typeof(wfesSequential) != "undefined" && wfesSequential.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSequential.raise()
                        wfesSequential.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.wfesSweep
                    visible: typeof(wfesSweep) != "undefined" && wfesSweep.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSweep.raise()
                        wfesSweep.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.wfesSwitching
                    visible: typeof(wfesSwitching) != "undefined" && wfesSwitching.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfesSwitching.raise()
                        wfesSwitching.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.wfafS
                    visible: typeof(wfafsView) != "undefined" && wfafsView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfafsView.raise()
                        wfafsView.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.wfafD
                    visible: typeof(wfafdView) != "undefined" && wfafdView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        wfafdView.raise()
                        wfafdView.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.timeDist
                    visible: typeof(timeDistView) != "undefined" && timeDistView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        timeDistView.raise()
                        timeDistView.requestActivate()
                    }
                }
                MenuItem {
                    text: Strings.phaseType
                    visible: typeof(phaseTypeView) != "undefined" && phaseTypeView.visible
                    height: visible ? implicitHeight : 0
                    onClicked: {
                        phaseTypeView.raise()
                        phaseTypeView.requestActivate()
                    }
                }
            }
        }


        Button {
            id: helpButton
            text: Strings.upperMenuHelpButton
            onClicked: menu4.open()

            Menu {
                id: menu4
                y: helpButton.height


                MenuItem {
                    text: Strings.upperMenuManualButton
                    onClicked: {
                        Qt.openUrlExternally(Strings.gitHubWikiURL);
                    }
                }
                MenuItem {
                    text: Strings.upperMenuAboutButton
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

    function updateWfesSingleEquilibrium() {
        chartVisualization.updateWfesSingleEquilibrium()
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
