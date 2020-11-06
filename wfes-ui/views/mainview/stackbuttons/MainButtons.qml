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
                ToolTip.text: "Wright Fisher Exact Solver"
                ToolTip.delay: 1000
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                text: "WFES"
                view: "qrc:/views/mainview/stackbuttons/wfesButtons.qml"
            }
            Button {
                text: "WFAF-S"
                ToolTip.text: "Wright-Fisher Allele Frequency Stochastic"
                ToolTip.delay: 1000
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                onClicked: {
                    var componentWfas = Qt.createComponent("qrc:/views/executionviews/wfasView.qml")
                    if( componentWfas.status !== Component.Ready )
                    {
                        if( componentWfas.status === Component.Error )
                            console.debug("Error:"+ componentWfas.errorString() );
                        return;
                    }
                    var windowWfas    = componentWfas.createObject(root, {})
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFAF-D"
                ToolTip.text: "Wright-Fisher Allele Frequency Deterministic"
                ToolTip.delay: 1000
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                onClicked: {
                    var componentWfafle = Qt.createComponent("qrc:/views/executionviews/wfafleView.qml")
                    if( componentWfafle.status !== Component.Ready )
                    {
                        if( componentWfafle.status === Component.Error )
                            console.debug("Error:"+ componentWfafle.errorString() );
                        return;
                    }
                    var windowWfafle    = componentWfafle.createObject(root, {})
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
                text: "Time Dist."
                ToolTip.text: "Distribution of Time to Fixation/Extinction"
                ToolTip.delay: 1000
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                onClicked: {
                    var componentTimeDist = Qt.createComponent("qrc:/views/executionviews/timeDistView.qml")
                    if( componentTimeDist.status !== Component.Ready )
                    {
                        if( componentTimeDist.status === Component.Error )
                            console.debug("Error:"+ componentTimeDist.errorString() );
                        return;
                    }
                    var windowTimeDist    = componentTimeDist.createObject(root, {})
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "Phase Type"
                ToolTip.text: "Calculate Moments and Distributions of Absorption Times for a Fixation-only Model"
                ToolTip.delay: 1000
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                onClicked: {
                    var componentPhaseType = Qt.createComponent("qrc:/views/executionviews/phaseTypeView.qml")
                    if( componentPhaseType.status !== Component.Ready )
                    {
                        if( componentPhaseType.status === Component.Error )
                            console.debug("Error:"+ componentPhaseType.errorString() );
                        return;
                    }
                    var windowPhaseType    = componentPhaseType.createObject(root, {})
                    root.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
        }

    }

}
