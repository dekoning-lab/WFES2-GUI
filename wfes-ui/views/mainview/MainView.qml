import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import assets 1.0
import components 1.0

ApplicationWindow {
    title: qsTr("WFES - Wright-Fisher Exact Solver")
    visible: true

    width: 600
    minimumWidth: 600
    height: 480
    minimumHeight: 480

    // Select theme for the application.
    Universal.theme: Universal.Light


    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    // Everything is located in this Rectangle.
    Rectangle {
        anchors.fill: parent
        color: "transparent"

        BackButton {
            id: back
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
            initialItem: 'qrc:/views/mainview/stackbuttons/MainButtons.qml'
        }

        BottomMenu {
            id: bottomMenu
        }
    }


}
