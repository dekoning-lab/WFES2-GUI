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
                text: "wfes"
                onClicked: {
                    menu.push("qrc:/views/wfesButtons.qml");
                    back.visible = true;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 100
            }
            Button {
                text: "wfas"
                onClicked: console.warn("WARNING: wfas clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 100
            }
            Button {
                text: "wfafle"
                onClicked: console.warn("WARNING: wfafle clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 100
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
                text: "time_dist"
                onClicked: {
                    menu.push("qrc:/views/timeDistButtons.qml");
                    back.visible = true;
                }
                Layout.leftMargin: 30
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 100
            }
            Button {
                text: "phase_type"
                onClicked: {
                    menu.push("qrc:/views/phaseTypeButtons.qml");
                    back.visible = true;
                }
                Layout.rightMargin: 30
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 100
            }
        }
    }
}
