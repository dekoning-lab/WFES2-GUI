import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.2

Item{
    id: item
    property alias text: button.text
    property string view: ""
    Layout.alignment: Qt.AlignHCenter
    Layout.preferredHeight: parent.height
    height: childrenRect.height
    width: 160
    Layout.preferredWidth: 160

    Button {
        id: button
        width: 160
        Layout.preferredWidth: 160
        text: ""
        onClicked: messageDialog.open()
    }

    MessageDialog {
        id: messageDialog
        title: "Warning"
        text: view
    }
}
