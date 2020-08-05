import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import components 1.0

Item {

    Rectangle {
        height: childrenRect.height
        width: parent.width
        color: "transparent"

        RowLayout {
            id: row1
            height: childrenRect.height
            width: parent.width
            LaunchViewButton {
                text: "Time Dist."
                view: "Time Dist. has not been implemented yet."
            }
            LaunchViewButton {
                text: "Time Dist. Dual"
                view: "Time Dist. Dual has not been implemented yet."
            }
        }

        RowLayout {
            id: row2
            height: childrenRect.height
            width: parent.width
            anchors {
                top: row1.bottom
                topMargin: 30
            }
            LaunchViewButton {
                text: "Time Dist. SGV"
                view: "Time Dist. SGV has not been implemented yet."
            }
            LaunchViewButton {
                text: "Time Dist. Skip"
                view: "Time Dist. Skip has not been implemented yet."
            }
        }

    }

}
