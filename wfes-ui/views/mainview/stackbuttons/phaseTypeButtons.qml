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
                text: "Phase Type Dist."
                view: "Phase Type Dist. has not been implemented yet."
            }
            LaunchViewButton {
                text: "Phase Type Moment"
                view: "Phase Type Moment has not been implemented yet."
            }
        }

    }

}
