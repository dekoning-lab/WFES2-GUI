import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0


Rectangle {
    property alias text: label.text
    property alias validator: textField.validator
    property int labelPreferredWidth: 20
    property alias textFieldText: textField.text
    property int textFieldPreferredWidth: 100

    property var fun: function(){}

    color: "transparent"
    width: childrenRect.width
    height: childrenRect.height

    RowLayout {
        Label {
            id: label
            Layout.preferredWidth: labelPreferredWidth
            text: "v:"
        }
        TextField {
            id: textField
            text: ""
            Layout.preferredWidth: textFieldPreferredWidth
            validator: DoubleValidator {bottom: 0; top: 2e-10;}
            focus: false
            selectByMouse: true
            onTextChanged: fun()
        }
    }
}
