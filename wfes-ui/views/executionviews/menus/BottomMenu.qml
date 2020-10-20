import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
Item {
    property alias visibleProgressBar: progressBar.visible
    property alias executionProgress: status.text
    property alias executionTime: time.text
    width: parent.width
    Rectangle {
        width: parent.width
        height: 30
        color: "transparent"

        RowLayout {
            width: parent.width
            height: parent.height

            Rectangle {
                width: parent.width/3
                height: parent.height
                Layout.alignment: Qt.AlignCenter
                ProgressBar {
                    id: progressBar
                    height: parent.height
                    indeterminate: true
                    visible: false
                }
            }
            Rectangle {
                width: parent.width/3
                height: parent.height
                color: "red"
                Layout.alignment: Qt.AlignCenter
                Layout.margins: 1

                RowLayout {
                    width: parent.width
                    height: parent.height

                    Text {
                        id: labelStatus
                        text: qsTr("Status: ")
                    }

                    Text {
                        id: status
                        text: qsTr("1/5 - Building Matrices.")
                    }
                }
            }

            Rectangle {
                width: parent.width/3
                height: parent.height
                color: "transparent"
                Layout.alignment: Qt.AlignCenter
                Layout.margins: 1

                RowLayout {
                    width: parent.width
                    height: parent.height

                    Text {
                        id: labelTime
                        text: qsTr("Execution Time: ")
                    }

                    Text {
                        id: time
                        text: qsTr("10.5s")
                    }
                }
            }
        }



    }
}
