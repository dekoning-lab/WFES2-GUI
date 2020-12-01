import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import components 1.0
import assets 1.0


Item {

    WfesSingleView {
        id: wfesSingleView
    }

    WfesSweepView {
        id: wfesSweep
    }

    WfesSequentialView {
        id: wfesSequential
    }

    WfesSwitchingView {
        id: wfesSwitching
    }

    Rectangle {
        width: parent.width
        height: childrenRect.height
        color: "transparent"

        RowLayout {
            id: row1
            width: parent.width
            Button {
                text: "WFES Single"
                ToolTip.text: "Calculations for the Standard Wright-Fisher Model."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered

                onClicked: {
                    wfesSingleView.visible = true
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFES Sweep"
                ToolTip.text: "Model of Positive Selection with Standing Genetic Variation."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered

                onClicked: {
                    wfesSweep.visible = true
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
                ToolTip.text: "Implements calculations for a set of standard Wright-Fisher models sequentially."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                onClicked: {
                    wfesSequential.visible = true
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFES Switching"
                ToolTip.text: "Time-heterogeneous Extension to the Wright-Fisher Model"
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered

                onClicked: {
                    wfesSwitching.visible = true
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
        }

    }

}
