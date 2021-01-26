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

        Button {
            text: Strings.upperMenuManualButton
            onClicked: {
                Qt.openUrlExternally("https://github.com/dekoning-lab/wfes-gui/wiki");
            }
        }
        Button {
            text: Strings.upperMenuAboutButton
            onClicked: {
                helpView.visible = true
            }
        }
    }

    HelpView {
        id:helpView
        visibleWindow: false
    }
}
