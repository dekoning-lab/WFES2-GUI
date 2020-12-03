import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import assets 1.0
import QtQuick.Controls.Universal 2.3


Item {
    property alias onCLick: backButton.onClicked
    visible: false
    width: childrenRect.width
    height: childrenRect.height
    anchors{
        top: parent.top
        left: parent.left
        margins: 20
    }

    Button {
        id: backButton
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
            wfesButtons.visible = false;
            mainButtons.visible = true;
        }
        Layout.alignment: Qt.AlignHCenter
    }

}
