import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

Rectangle {
    id: upperMenu
    width:parent.width
    height: childrenRect.height
    color: "lightgrey"
    
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
                        //Check for active view and save config.
                        if(typeof(rootWfesSingle) != "undefined") {
                            rootWfesSingle.updateBackend()
                            outputControllerWfesSingle.ui_save_config
                        } else if(typeof(rootWfesSequential) != "undefined") {
                            rootWfesSequential.updateBackend()
                            outputControllerWfesSequential.ui_save_config
                        } else if(typeof(rootWfesSweep) != "undefined") {
                            rootWfesSweep.updateBackend()
                            outputControllerWfesSweep.ui_save_config
                        } else if(typeof(rootWfesSwitching) != "undefined") {
                            rootWfesSwitching.updateBackend()
                            outputControllerWfesSwitching.ui_save_config
                        } else if(typeof(rootWfas) != "undefined") {
                            rootWfas.updateBackend()
                            outputControllerWfas.ui_save_config
                        } else if(typeof(rootWfafle) != "undefined") {
                            rootWfafle.updateBackend()
                            outputControllerWfafle.ui_save_config
                        } else if(typeof(rootTimeDist) != "undefined") {
                            rootTimeDist.updateBackend()
                            outputControllerTimeDist.ui_save_config
                        } else if(typeof(rootPhaseType) != "undefined") {
                            rootPhaseType.updateBackend()
                            outputControllerPhaseType.ui_save_config
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
                        } else if(typeof(rootWfas) != "undefined") {
                            outputControllerWfas.ui_load_config
                            rootWfas.updateGUI()
                        } else if(typeof(rootWfafle) != "undefined") {
                            outputControllerWfafle.ui_load_config
                            rootWfafle.updateGUI()
                        } else if(typeof(rootTimeDist) != "undefined") {
                            outputControllerTimeDist.ui_load_config
                            rootTimeDist.updateGUI()
                        } else if(typeof(rootPhaseType) != "undefined") {
                            outputControllerPhaseType.ui_load_config
                            rootPhaseType.updateGUI()
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
                    CheckBox {
                        anchors.fill: parent
                        text: "Generate Images"
                        checked: globalConfiguration.ui_generate_images
                        onCheckedChanged: {
                            globalConfiguration.ui_generate_images = this.checked
                        }
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

    function updateDistWfas() {
        chartVisualization.updateDistWfas()
    }

    function updateDistWfafle() {
        chartVisualization.updateDistWfafle()
    }

    function updateProbTimeDist(name) {
        chartVisualization.updateProbTimeDist(name)
    }

    function updatePhaseTypeDistChart() {
        chartVisualization.updatePhaseTypeDistChart()
    }
}
