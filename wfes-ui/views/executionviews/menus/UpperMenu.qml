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
            id: fileButton
            text: "File"
            onClicked: menu.open()
            
            Menu {
                id: menu
                y: fileButton.height
                
                MenuItem {
                    text: "New..."
                    onClicked: {
                        console.warn("WARNING: File->New... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Open..."
                    onClicked: {
                        console.warn("WARNING: File->Open... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Save..."
                    onClicked: {
                        console.warn("WARNING: File->Save... clicked - Not implemented yet.")
                    }
                }
            }
        }
        
        
        Button {
            id: settingsButton
            text: "Settings"
            onClicked: menu2.open()
            
            Menu {
                id: menu2
                y: settingsButton.height
                
                MenuItem {
                    text: "New..."
                    onClicked: {
                        console.warn("WARNING: Settings->New... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Open..."
                    onClicked: {
                        console.warn("WARNING: Help->Open... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Save"
                    onClicked: {
                        console.warn("WARNING: Settings->Save... clicked - Not implemented yet.")
                    }
                }
            }
        }
        
        
        
        Button {
            id: helpButton
            text: "Help"
            onClicked: menu3.open()
            
            Menu {
                id: menu3
                y: helpButton.height
                
                MenuItem {
                    text: "New..."
                    onClicked: {
                        console.warn("WARNING: Help->New... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Open..."
                    onClicked: {
                        console.warn("WARNING: Help->Open... clicked - Not implemented yet.")
                    }
                }
                MenuItem {
                    text: "Save"
                    onClicked: {
                        console.warn("WARNING: Help->Save... clicked - Not implemented yet.")
                    }
                }
            }
        }
    }
    
}
