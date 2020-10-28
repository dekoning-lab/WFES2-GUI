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


    width: 600
    minimumWidth: 600
    maximumWidth: 600
    height: 300
    minimumHeight: 300
    maximumHeight: 300

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

    Image {
        id: logo
        anchors {
            top: parent.top
            left: parent.left
            topMargin: 20
            leftMargin: 30
        }

        width: 125;
        height: 76;
        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/images/wfes_logo_225x140.png"
        horizontalAlignment: Image.AlignHCenter;
    }

}
