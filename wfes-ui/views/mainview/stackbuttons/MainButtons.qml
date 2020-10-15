import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

import components 1.0

Item {

    Rectangle {
        width: parent.width
        height: childrenRect.height
        color: "transparent"

        RowLayout {
            id: row1
            height: childrenRect.height
            width: parent.width
            ChangeStackViewButton {
                text: "WFES"
                view: "qrc:/views/mainview/stackbuttons/wfesButtons.qml"
            }
            LaunchViewButton {
                text: "WFAS"
                view: "wfas has not been implemented yet."
            }
            LaunchViewButton {
                text: "WFAFLE"
                view: "wfafle has not been implemented yet."
            }

        }

        RowLayout {
            id: row2
            width: parent.width
            height: childrenRect.height
            anchors {
                top: row1.bottom
                topMargin: 30
            }
            Button {
                text: "Time Dist."
                onClicked: {
                    var componentTimeDist = Qt.createComponent("qrc:/views/executionviews/timeDistView.qml")
                    if( componentTimeDist.status !== Component.Ready )
                    {
                        if( componentTimeDist.status === Component.Error )
                            console.debug("Error:"+ componentTimeDist.errorString() );
                        return; // or maybe throw
                    }
                    var windowTimeDist    = componentTimeDist.createObject(root, {})
                    //windowTimeDist.show()
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            ChangeStackViewButton {
                text: "Phase Type"
                view: "qrc:/views/mainview/stackbuttons/phaseTypeButtons.qml"
            }
        }

    }

}
