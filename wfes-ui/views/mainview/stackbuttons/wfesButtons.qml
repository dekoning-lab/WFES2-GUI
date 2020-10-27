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
                        return;
                    }
                    var windowWfesSingle    = componentWfesSingle.createObject(root, {})
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
                        return;
                    }
                    var windowWfesSweep    = componentWfesSweep.createObject(root, {})
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

            Button {
                text: "WFES Sequential"
                onClicked: {
                    var componentWfesSequential = Qt.createComponent("qrc:/views/executionviews/wfesSequentialView.qml")
                    if( componentWfesSequential.status !== Component.Ready )
                    {
                        if( componentWfesSequential.status === Component.Error )
                            console.debug("Error:"+ componentWfesSequential.errorString() );
                        return;
                    }
                    var windowWfesSequential    = componentWfesSequential.createObject(root, {})
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFES Switching"
                onClicked: {
                    var componentWfesSwithcing = Qt.createComponent("qrc:/views/executionviews/wfesSwitchingView.qml")
                    if( componentWfesSwithcing.status !== Component.Ready )
                    {
                        if( componentWfesSwithcing.status === Component.Error )
                            console.debug("Error:"+ componentWfesSwithcing.errorString() );
                        return;
                    }
                    var windowWfesSwithcing    = componentWfesSwithcing.createObject(root, {})
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
        }

    }

}
