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

    ColumnLayout {
        Flickable {
            width: 200; height: 200
            contentWidth: imageQ.width; contentHeight: imageQ.height

            Image {
                id: imageQ
                sourceSize.width: 200
                sourceSize.height: 200
                source: "image://visualizationImageProvider/Q"
                asynchronous: true
            }
        }
        Flickable {
            width: 200; height: 200
            contentWidth: imageN.width; contentHeight: imageN.height

            Image {
                id: imageN
                sourceSize.width: 200
                sourceSize.height: 200
                source: "image://visualizationImageProvider/N"
                asynchronous: true
            }
        }
    }
}
