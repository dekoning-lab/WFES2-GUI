import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import components 1.0

Item {

    Rectangle {
        width: parent.width
        height: childrenRect.height
        color: "transparent"

        RowLayout {
            id: row1
            height: childrenRect.height
            width: parent.width
            ChangeStackViewButton {
                text: "wfes"
                view: "qrc:/views/mainview/stackbuttons/wfesButtons.qml"
            }
            LaunchViewButton {
                text: "wfas"
                view: "WARNING: wfas clicked - Not implemented yet."
            }
            LaunchViewButton {
                text: "wfafle"
                view: "WARNING: wfafle clicked - Not implemented yet."
            }
        }

        RowLayout {
            id: row2
            width: parent.width
            height: childrenRect.height
            anchors {
                top: row1.bottom
                topMargin: 30
            }
            ChangeStackViewButton {
                text: "time_dist"
                view: "qrc:/views/mainview/stackbuttons/timeDistButtons.qml"
            }
            ChangeStackViewButton {
                text: "phase_type"
                view: "qrc:/views/mainview/stackbuttons/phaseTypeButtons.qml"
            }
        }

    }

}
