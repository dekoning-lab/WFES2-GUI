import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import assets 1.0

Item {
    property alias visibleProgressBar: progressBar.visible
    property alias executionProgress: status.text
    property alias executionTime: time.text

    width: parent.width
    height: Style.bottomMenuHeight

    Rectangle {
        width: parent.width
        height: Style.bottomMenuHeight
        color: "transparent"

        RowLayout {
            width: parent.width
            height: parent.height

            Rectangle {
                Layout.preferredWidth: parent.width/3
                Layout.preferredHeight: parent.height
                Layout.alignment: Qt.AlignCenter
                color: "transparent"
                ProgressBar {
                    id: progressBar
                    anchors.centerIn: parent
                    height: parent.height
                    indeterminate: true
                    visible: false
                }
            }
            Rectangle {
                Layout.preferredWidth: parent.width/3
                Layout.preferredHeight: parent.height
                color: "transparent"
                Layout.alignment: Qt.AlignCenter
                Layout.margins: 1

                RowLayout {
                    anchors.centerIn: parent
                    height: parent.height

                    Text {
                        id: labelStatus
                        text: Strings.bottomBarStatus + Strings.colon
                    }

                    Text {
                        id: status
                        text: Strings.bottomBarNotExecuting
                    }
                }
            }

            Rectangle {
                Layout.preferredWidth: parent.width/3
                Layout.preferredHeight: parent.height
                color: "transparent"
                Layout.alignment: Qt.AlignCenter
                Layout.margins: 1

                RowLayout {
                    anchors.centerIn: parent
                    height: parent.height

                    Text {
                        id: labelTime
                        text: Strings.bottomBarExecutionTime + Strings.colon
                    }

                    Text {
                        id: time
                        text: Strings.bottomBarZeroTime
                    }
                }
            }
        }



    }
}
