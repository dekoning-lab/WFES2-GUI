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
                text: "phase_type_dist"
                onClicked: console.warn("WARNING: phase_type_dist clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
            Button {
                text: "phase_type_moment"
                onClicked: console.warn("WARNING: phase_type_moment clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
        }
    }
}
