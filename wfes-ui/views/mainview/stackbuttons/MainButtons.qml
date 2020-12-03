import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

import components 1.0
import assets 1.0

Item {
    property alias visibleMainButtons: mainButtons.visible
    property alias visibleWfesButtons: wfesButtons.visible

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
        id: mainButtons
        width: parent.width
        height: childrenRect.height
        color: "transparent"

        RowLayout {
            id: row1
            height: childrenRect.height
            width: parent.width
            Button {
                text: "WFES"
                ToolTip.text: "Wright Fisher Exact Solver."
                ToolTip.delay: Style.tooltipDelay
                ToolTip.timeout: Style.tooltipTimeout
                ToolTip.visible: hovered
                onClicked: {
                    back.visible = true;
                    wfesButtons.visible = true;
                    mainButtons.visible = false;
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
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

    Rectangle {
        id: wfesButtons
        visible: false
        width: parent.width
        height: childrenRect.height
        color: "transparent"

        RowLayout {
            id: row1wfes
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
            id: row2wfes
            width: parent.width
            height: childrenRect.height
            anchors {
                top: row1wfes.bottom
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
