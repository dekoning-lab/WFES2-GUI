import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0


Rectangle {
    property alias text: label.text
    property alias checked: checkBox.checked

    property var fun: function(){}

    color: "transparent"
    width: childrenRect.width
    height: childrenRect.height

    RowLayout {
        Label {
            id: label
            Layout.preferredWidth: 20
            text: "v:"
        }
        CheckBox {
            Layout.preferredWidth: 100
            id: checkBox
            checked: true
            onCheckedChanged: fun()
        }
    }

}
