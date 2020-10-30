import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import assets 1.0
import components 1.0


ApplicationWindow {
    id: rootHelp
    title: qsTr("WFES - Wright-Fisher Exact Solver")

    visible: true


    width: 500
    minimumWidth: 500
    maximumWidth: 500
    height: 500
    minimumHeight: 500
    maximumHeight: 500

    // Select theme for the application.
    Universal.theme: Universal.Light

    color: Universal.chromeLowColor

    onClosing: {
        rootHelp.hide();
    }

    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }


      Rectangle{
         id:displayQ
         width:parent.width
         height:parent.height
         color: "transparent"
        Image {
            id: imageQ
            sourceSize.width: parent.width
            sourceSize.height: parent.width
            source: "image://visualizationImageProvider/Q"
            asynchronous: true

            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }

        MouseArea{
           width: parent.width
           height: parent.height

           drag.target: displayQ

           anchors.centerIn: displayQ
           onWheel: {
               if (wheel.modifiers & Qt.ControlModifier) {
                   displayQ.rotation += wheel.angleDelta.y / 120 * 5;
                   if (Math.abs(displayQ.rotation) < 4)
                       parent.rotation = 0;
               } else {
                   displayQ.rotation += wheel.angleDelta.x / 120;
                   if (Math.abs(displayQ.rotation) < 0.6)
                       displayQ.rotation = 0;
                   var scaleBefore = parent.scale;
                   var incrementScale = displayQ.scale * wheel.angleDelta.y / 120 / 10
                   if(displayQ.scale + incrementScale < 2.5 && displayQ.scale + incrementScale > 0.8)
                        displayQ.scale += displayQ.scale * wheel.angleDelta.y / 120 / 10
               }
           }
        }
    }

      Rectangle{
         id:displayN
         width:parent.width
         height:parent.height
         color: "transparent"
         visible: false
        Image {
            id: imageN
            sourceSize.width: parent.width
            sourceSize.height: parent.width
            source: "image://visualizationImageProvider/N"
            asynchronous: true

            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }

        MouseArea{
           width: parent.width
           height: parent.height

           drag.target: displayN

           anchors.centerIn: displayN
           onWheel: {
               if (wheel.modifiers & Qt.ControlModifier) {
                   displayN.rotation += wheel.angleDelta.y / 120 * 5;
                   if (Math.abs(displayN.rotation) < 4)
                       parent.rotation = 0;
               } else {
                   displayN.rotation += wheel.angleDelta.x / 120;
                   if (Math.abs(displayN.rotation) < 0.6)
                       displayN.rotation = 0;
                   var scaleBefore = parent.scale;
                   var incrementScale = displayN.scale * wheel.angleDelta.y / 120 / 10
                   if(displayN.scale + incrementScale < 2.5 && displayN.scale + incrementScale > 0.8)
                        displayN.scale += displayN.scale * wheel.angleDelta.y / 120 / 10
               }
           }
        }
    }

        Button {
            text: "Reset Zoom"
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }

            onClicked: {
                displayQ.scale = 1
                displayQ.x = 0
                displayQ.y = 0
                displayN.scale = 1
                displayN.x = 0
                displayN.y = 0
            }

        }

        Button {
            text: "N Matrix"
            anchors {
                top: parent.top
                right: parent.right
            }

            onClicked: {
                if(displayQ.visible == true) {
                    displayQ.visible = false
                    displayN.visible = true
                    text = "Q Matrix"
                } else {
                    displayQ.visible = true
                    displayN.visible = false
                    text = "N Matrix"
                }

            }

        }
}
