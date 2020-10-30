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

    DisplayImage {
        id: displayI
        visible: false
        source: imageOutputController.ui_image_I
    }

    DisplayImage {
        id: displayQ
        visible: false
        source: imageOutputController.ui_image_Q
    }

    DisplayImage {
        id: displayR
        visible: false
        source: imageOutputController.ui_image_R
    }

    DisplayImage {
        id: displayB
        visible: false
        source: imageOutputController.ui_image_B
    }

    DisplayImage {
        id: displayN
        visible: false
        source: imageOutputController.ui_image_N
    }

    DisplayImage {
        id: displayNext
        visible: false
        source: imageOutputController.ui_image_N_ext
    }

    DisplayImage {
        id: displayNfix
        visible: false
        source: imageOutputController.ui_image_N_fix
    }

    DisplayImage {
        id: displayV
        visible: false
        source: imageOutputController.ui_image_V
    }

    DisplayImage {
        id: displayE
        visible: false
        source: imageOutputController.ui_image_E
    }

    Button {
        text: "Reset Zoom"
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        onClicked: {
            displayI.scale = 1
            displayI.x = 0
            displayI.y = 0
            displayQ.scale = 1
            displayQ.x = 0
            displayQ.y = 0
            displayR.scale = 1
            displayR.x = 0
            displayR.y = 0
            displayB.scale = 1
            displayB.x = 0
            displayB.y = 0
            displayN.scale = 1
            displayN.x = 0
            displayN.y = 0
            displayNExt.scale = 1
            displayNExt.x = 0
            displayNExt.y = 0
            displayNfix.scale = 1
            displayNfix.x = 0
            displayNfix.y = 0
            displayV.scale = 1
            displayV.x = 0
            displayV.y = 0
            displayE.scale = 1
            displayE.x = 0
            displayE.y = 0
        }

    }

    Button {
        id: buttonI
        visible: {
            return displayI.source != "image://visualizationimageprovider/null"
        }
        width: 100

        enabled: true
        text: "I Matrix"
        anchors {
            top: parent.top
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = false
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = true
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = false
        }
    }

    Button {
        id: buttonQ
        enabled: true
        visible: {
            return displayQ.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "Q Matrix"
        anchors {
            top: buttonI.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = false
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = true
            displayR.visible = false
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = false
        }
    }

    Button {
        id: buttonR
        enabled: true
        visible: {
            return displayR.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "R Matrix"
        anchors {
            top: buttonQ.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = false
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = true
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = false
        }
    }


    Button {
        id: buttonB
        enabled: true
        visible: {
            return displayB.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "B Matrix"
        anchors {
            top: buttonR.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = false
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = true
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = false
        }
    }

    Button {
        id: buttonN
        enabled: true
        visible: {
            return displayN.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "N Matrix"
        anchors {
            top: buttonB.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = false
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = false
            displayN.visible = true
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = false
        }
    }

    Button {
        id: buttonNext
        enabled: true
        visible: {
            return displayNext.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "N ext Matrix"
        anchors {
            top: buttonN.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = false
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = true
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = false
        }
    }

    Button {
        id: buttonNfix
        enabled: true
        visible: {
            return displayNfix.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "N fix Matrix"
        anchors {
            top: buttonNext.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = false
            buttonV.enabled = true
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = true
            displayV.visible = false
            displayE.visible = false
        }
    }
    Button {
        id: buttonV
        enabled: true
        visible: {
            return displayV.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "V Matrix"
        anchors {
            top: buttonNfix.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = false
            buttonE.enabled = true

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = true
            displayE.visible = false
        }
    }
    Button {
        id: buttonE
        enabled: true
        visible: {
            return displayE.source != "image://visualizationimageprovider/null"
        }
        width: 100

        text: "E Matrix"
        anchors {
            top: buttonV.bottom
            right: parent.right
        }
        onClicked: {
            buttonI.enabled = true
            buttonQ.enabled = true
            buttonR.enabled = true
            buttonB.enabled = true
            buttonN.enabled = true
            buttonNext.enabled = true
            buttonNfix.enabled = true
            buttonV.enabled = true
            buttonE.enabled = false

            displayI.visible = false
            displayQ.visible = false
            displayR.visible = false
            displayB.visible = false
            displayN.visible = false
            displayNext.visible = false
            displayNfix.visible = false
            displayV.visible = false
            displayE.visible = true
        }
    }
}
