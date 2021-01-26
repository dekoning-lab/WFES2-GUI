import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import assets 1.0
import components 1.0

ApplicationWindow {
    property alias visibleWindow: rootHelp.visible

    id: rootHelp
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.help + ")";

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

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootHelp.close()
    }

    onClosing: {
        rootHelp.hide();
    }

    Component.onCompleted: {
        // Center window in screen.
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    /**
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
    **/

    // Everything is located in this Rectangle.
    ColumnLayout {
        anchors.fill: parent

        Label {
            topPadding: 20
            Layout.alignment: Qt.AlignHCenter
            text: Strings.wfes + Strings.hyphen + Strings.wfesComplete
            font.bold: true
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: Strings.builtOn
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: Strings.copyrightNote
        }

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: Strings.licenseNote



            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            property string link: Strings.gitHubURL
            Layout.alignment: Qt.AlignHCenter
            text: "<a href='"+link+"'>" + Strings.gitHubWebPageText + "</a>";
            onLinkActivated: Qt.openUrlExternally(link)
            MouseArea
            {
                id: mouseArea
                anchors.fill: parent
                onPressed:  mouse.accepted = false
                cursorShape: Qt.PointingHandCursor
            }

        }

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: Strings.contactText

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            property string link: Strings.labURL
            Layout.alignment: Qt.AlignHCenter
            text: "<a href='"+link+"'>" + Strings.labWebPageText + "</a>";
            onLinkActivated: Qt.openUrlExternally(link)
            MouseArea
            {
                id: mouseArea3
                anchors.fill: parent
                onPressed:  mouse.accepted = false
                cursorShape: Qt.PointingHandCursor
            }

            bottomPadding: 20
        }


    }
}
