import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

Item {
    Rectangle {
        width: parent.width
        height: childrenRect.height
        color: "transparent"
        RowLayout {
            id: row1
            width: parent.width
            Button {
                text: "wfes_single"
                onClicked: masterController.ui_execute
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
            Button {
                text: "wfes_sweep"
                onClicked: console.warn("WARNING: wfes_single clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
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
            Button {
                text: "wfes_sequential"
                onClicked: console.warn("WARNING: wfes_sequential clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
            Button {
                text: "wfes_switching"
                onClicked: console.warn("WARNING: wfes_switching clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
        }
    }
}
