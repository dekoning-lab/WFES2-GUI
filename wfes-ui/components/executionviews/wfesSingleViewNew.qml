import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0

ApplicationWindow {
    property var firstLoad: true

    id: rootWfesSingle
    title: Strings.wfes + Strings.hyphen + Strings.wfesComplete + " (" + Strings.wfesSingle + ")"

    color: Universal.chromeLowColor

    visible: false

    width: 945
    minimumWidth: 945
    maximumWidth: 945
    height: 560
    minimumHeight: 560
    maximumHeight: 560

    // Select theme for the application.
    Universal.theme: Universal.Light

    Shortcut {
        sequence: "CTRL+W"
        onActivated: rootWfesSingle.close()
    }

    onClosing: {
        close.accepted = false

        if(checkIntegrity() !== "") {
            messageDialogOnClose.text = Strings.onCloseConfirmationMessage
            messageDialogOnClose.open()

        } else {
            rootWfesSingle.hide();
            root.visible = true;
            rootWfesSingle.updateBackend()
            outputControllerWfesSingle.ui_save_config
        }
    }

    MessageDialog {
        id: messageDialogOnClose
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            rootWfesSingle.hide();
            root.visible = true;
        }
    }



    Component.onCompleted: {
        // Center window in screen.
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
        outputControllerWfesSingle.ui_load_config
        rootWfesSingle.updateGUI()
    }

    MessageDialog {
        id: messageDialog
        title: Strings.dialogWarning
        text: Strings.empty
        icon: StandardIcon.Warning
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        UpperMenu {
            id: upperMenu
        }

    }



}
