import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import assets 1.0
import QtQuick.Controls.Universal 2.3


ApplicationWindow {
    visible: true
    width: 480
    minimumWidth: 480
    minimumHeight: 480
    height: 480

    Universal.theme: Universal.Light

    title: qsTr("WFES - Wright-Fisher Exact Solver")

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }


    Rectangle {
        anchors.fill: parent
        color: "transparent"
        Rectangle {
            id: back
            visible: false
            width: childrenRect.width
            height: childrenRect.height
            anchors{
                top: parent.top
                left: parent.left
                margins: 20
            }
            RowLayout {
                id: row4
                width: childrenRect.width
                height: childrenRect.height
                Button {
                    background: Rectangle {
                                color: "transparent"
                            }
                    font {
                        family: Style.fontAwesome
                        pixelSize: 30
                    }
                    text: "\uf060"
                    onClicked: {
                        back.visible = false;
                        menu.pop()
                    }
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }

        Image {
            id: logo
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                topMargin: 60
            }
            width: 225;
            height: 140;
            fillMode: Image.PreserveAspectFit
            source: "qrc:/assets/images/wfes_logo_225x140.png"
            horizontalAlignment: Image.AlignHCenter;

        }

        StackView {
            id: menu
            width: parent.width
            height: childrenRect.height
            anchors {
                top: logo.bottom
                topMargin: 50
            }
            initialItem: 'qrc:/views/MainButtons.qml'
        }

        Rectangle {
            id: options
            width: childrenRect.width
            height: childrenRect.height
            anchors{
                bottom: parent.bottom
                right: parent.right
                margins: 20
            }
            color: "transparent"
            RowLayout {
                id: row3
                width: childrenRect.width
                height: childrenRect.height
                Button {
                    text: "options"
                    onClicked: console.warn("WARNING: options clicked - Not implemented yet.")
                    Layout.alignment: Qt.AlignHCenter
                }
                Button {
                    text: "help"
                    onClicked: console.warn("WARNING: help clicked - Not implemented yet.")
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }


}
