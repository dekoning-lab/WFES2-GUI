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
                text: "time_dist"
                view: "WARNING: time_dist clicked - Not implemented yet."
            }
            LaunchViewButton {
                text: "time_dist_dual"
                view: "WARNING: time_dist_dual clicked - Not implemented yet."
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
                text: "time_dist_sgv"
                view: "WARNING: time_dist_sgv clicked - Not implemented yet."
            }
            LaunchViewButton {
                text: "time_dist_skip"
                view: "WARNING: time_dist_skip clicked - Not implemented yet."
            }
        }

    }

}
