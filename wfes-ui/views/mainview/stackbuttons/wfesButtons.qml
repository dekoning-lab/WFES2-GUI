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
            width: parent.width
            Button {
                text: "WFES Single"
                onClicked: {
                    var component = Qt.createComponent("qrc:/views/executionviews/wfesSingleView.qml")
                    var window    = component.createObject()
                    window.show()
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFES Sweep"
                onClicked: {
                    var component = Qt.createComponent("qrc:/views/executionviews/wfesSweepView.qml")
                    var window    = component.createObject()
                    window.show()
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
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
            LaunchViewButton {
                text: "WFES Sequential"
                view: "WFES Sequential has not been implemented yet."
            }
            LaunchViewButton {
                text: "WFES Switching"
                view: "WFES Switching has not been implemented yet."
            }
        }

    }

}
