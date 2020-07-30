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
                text: "phase_type_dist"
                view: "WARNING: phase_type_dist clicked - Not implemented yet."
            }
            LaunchViewButton {
                text: "phase_type_moment"
                view: "WARNING: phase_type_moment clicked - Not implemented yet."
            }
        }

    }

}
