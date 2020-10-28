import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import assets 1.0
import components 1.0

Rectangle {
    id: options
    width: childrenRect.width
    height: childrenRect.height
    anchors{
        bottom: parent.bottom
        right: parent.right
        margins: 20
    }
    color: "transparent"
    RowLayout {
        id: row3

        LaunchViewButton {
            text: "Configure"
            view: "WARNING: Configure clicked - Not implemented yet."
        }
        Button {
            text: "Help"
            onClicked: {
                var h = Qt.createComponent("qrc:/views/mainview/help/helpView.qml")
                if( h.status !== Component.Ready )
                {
                    if( h.status === Component.Error )
                        console.debug("Error:"+ h.errorString() );
                    return;
                }
                var windowPhaseType    = h.createObject(root, {})
            }
        }
    }
}
