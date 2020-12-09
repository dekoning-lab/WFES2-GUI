import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0


Rectangle {
    property alias text: label.text
    property alias validator: textField.validator
    property int labelPreferredWidth: 35
    property alias textFieldText: textField.text
    property int textFieldPreferredWidth: 95
    property alias readOnly: textField.readOnly
    property string toolTipText: "This is a tooltip"
    property var fun: function(){}

    color: "transparent"
    width: childrenRect.width
    height: childrenRect.height

    RowLayout {
        Label {
            id: label
            Layout.preferredWidth: labelPreferredWidth
            text: "v:"
            textFormat: Text.RichText

            ToolTip.visible: toolTipText ? ma.containsMouse : false
            ToolTip.delay: Style.tooltipDelay
            ToolTip.timeout: Style.tooltipTimeout
            ToolTip.text: qsTr(toolTipText)
            MouseArea {
                id: ma
                anchors.fill: parent
                hoverEnabled: true
            }

        }
        TextField {
            id: textField
            text: ""
            Layout.preferredWidth: textFieldPreferredWidth
            focus: false
            leftPadding: 5
            selectByMouse: true
            onTextChanged: fun()
        }
    }
}
