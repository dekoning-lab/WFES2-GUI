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
                text: "time_dist"
                onClicked: console.warn("WARNING: time_dist clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
            Button {
                text: "time_dist_dual"
                onClicked: console.warn("WARNING: time_dist_dual clicked - Not implemented yet.")
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
                text: "time_dist_sgv"
                onClicked: console.warn("WARNING: time_dist_sgv clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
            Button {
                text: "time_dist_skip"
                onClicked: console.warn("WARNING: time_dist_skip clicked - Not implemented yet.")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }
        }
    }
}
