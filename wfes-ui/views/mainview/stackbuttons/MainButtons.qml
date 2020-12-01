import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

import components 1.0
import assets 1.0

Item {

    WfasView {
        id: wfasView
    }

    WfafleView {
        id: wfafleView
    }

    TimeDistView {
        id: timeDistView
    }

    PhaseTypeView {
        id: phaseTypeView
    }

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
                ToolTip.text: "Wright Fisher Exact Solver."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                view: "qrc:/views/mainview/stackbuttons/wfesButtons.qml"
            }
            Button {
                text: "WFAF-S"
                ToolTip.text: "Wright-Fisher Allele Frequency Stochastic."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                onClicked: {
                    wfasView.visible = true;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "WFAF-D"
                ToolTip.text: "Wright-Fisher Allele Frequency Deterministic."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                onClicked: {
                    wfafleView.visible = true
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
                ToolTip.text: "Distribution of Time to Fixation/Extinction."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                onClicked: {
                    timeDistView.visible = true
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
            Button {
                text: "Phase Type"
                ToolTip.text: "Calculate Moments and Distributions of Absorption Times for a Fixation-only Model."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                onClicked: {
                    phaseTypeView.visible = true
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
        }

    }

}
