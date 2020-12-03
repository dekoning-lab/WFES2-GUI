import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

Item {
    property alias text: button.text
    property string view
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
        onClicked: {
            menu.push(view, {}, StackView.Immediate);
            back.visible = true;
        }
    }

}
