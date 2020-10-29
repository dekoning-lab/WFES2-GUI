import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3

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
                        console.warn("WARNING: Settings->Save Config... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Load Config..."
                    onClicked: {
                        console.warn("WARNING: Help->Load Config... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Global Settings"
                    onClicked: {
                        console.warn("WARNING: Settings->Global Settings clicked - Not implemented yet.")
                    }
                }
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
                        console.warn("WARNING: Settings->New... clicked - Not implemented yet.")
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
                        var h = Qt.createComponent("qrc:/views/mainview/help/helpView.qml")
                        if( h.status !== Component.Ready )
                        {
                            if( h.status === Component.Error )
                                console.debug("Error:"+ h.errorString() );
                            return;
                        }
                        var windowh = h.createObject(upperMenu.parent.parent, {})
                        windowh.visible
                    }
                }
            }
        }
    }
    
}
