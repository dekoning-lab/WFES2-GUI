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
            width: parent.width
            Button {
                text: "WFES Single"
                onClicked: {
                    var componentWfesSingle = Qt.createComponent("qrc:/views/executionviews/wfesSingleView.qml")
                    if( componentWfesSingle.status !== Component.Ready )
                    {
                        if( componentWfesSingle.status === Component.Error )
                            console.debug("Error:"+ componentWfesSingle.errorString() );
                        return; // or maybe throw
                    }
                    var windowWfesSingle    = componentWfesSingle.createObject(root, {})
                    //windowWfesSingle.show()
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFES Sweep"
                onClicked: {
                    var componentWfesSweep = Qt.createComponent("qrc:/views/executionviews/wfesSweepView.qml")
                    if( componentWfesSweep.status !== Component.Ready )
                    {
                        if( componentWfesSweep.status === Component.Error )
                            console.debug("Error:"+ componentWfesSweep.errorString() );
                        return; // or maybe throw
                    }
                    var windowWfesSweep    = componentWfesSweep.createObject(root, {})
                    //windowWfesSweep.show()
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
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
            LaunchViewButton {
                text: "WFES Sequential"
                view: "WFES Sequential has not been implemented yet."
            }
            LaunchViewButton {
                text: "WFES Switching"
                view: "WFES Switching has not been implemented yet."
            }
        }

    }

}
