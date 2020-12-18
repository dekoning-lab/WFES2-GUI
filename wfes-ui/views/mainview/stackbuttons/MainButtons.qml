import QtQuick 2.0
import QtQuick.Window 2.3
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

    WfafsView {
        id: wfafsView
    }

    WfafdView {
        id: wfafdView
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
                    if(wfafsView.visible) {
                        wfafsView.raise()
                    } else {
                        wfafsView.visible = true;
                    }
                    // Center window in screen.
                    wfafsView.setX(Screen.width / 2 - wfafsView.width / 2);
                    wfafsView.setY(Screen.height / 2 - wfafsView.height / 2);
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
                    if(wfafdView.visible) {
                        wfafdView.raise()
                    } else {
                        wfafdView.visible = true;
                    }
                    // Center window in screen.
                    wfafdView.setX(Screen.width / 2 - wfafdView.width / 2);
                    wfafdView.setY(Screen.height / 2 - wfafdView.height / 2);
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
                    if(timeDistView.visible) {
                        timeDistView.raise()
                    } else {
                        timeDistView.visible = true;
                    }
                    // Center window in screen.
                    timeDistView.setX(Screen.width / 2 - timeDistView.width / 2);
                    timeDistView.setY(Screen.height / 2 - timeDistView.height / 2);
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
                    if(phaseTypeView.visible) {
                        phaseTypeView.raise()
                    } else {
                        phaseTypeView.visible = true;
                    }
                    // Center window in screen.
                    phaseTypeView.setX(Screen.width / 2 - phaseTypeView.width / 2);
                    phaseTypeView.setY(Screen.height / 2 - phaseTypeView.height / 2);
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
                    if(wfesSingleView.visible) {
                        wfesSingleView.raise()
                    } else {
                        wfesSingleView.visible = true;
                    }
                    // Center window in screen.
                    wfesSingleView.setX(Screen.width / 2 - wfesSingleView.width / 2);
                    wfesSingleView.setY(Screen.height / 2 - wfesSingleView.height / 2);
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
                    if(wfesSweep.visible) {
                        wfesSweep.raise()
                    } else {
                        wfesSweep.visible = true;
                    }
                    // Center window in screen.
                    wfesSweep.setX(Screen.width / 2 - wfesSweep.width / 2);
                    wfesSweep.setY(Screen.height / 2 - wfesSweep.height / 2);
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
                    if(wfesSequential.visible) {
                        wfesSequential.raise()
                    } else {
                        wfesSequential.visible = true;
                    }
                    // Center window in screen.
                    wfesSequential.setX(Screen.width / 2 - wfesSequential.width / 2);
                    wfesSequential.setY(Screen.height / 2 - wfesSequential.height / 2);
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
                    if(wfesSwitching.visible) {
                        wfesSwitching.raise()
                    } else {
                        wfesSwitching.visible = true;
                    }
                    // Center window in screen.
                    wfesSwitching.setX(Screen.width / 2 - wfesSwitching.width / 2);
                    wfesSwitching.setY(Screen.height / 2 - wfesSwitching.height / 2);
                }
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 160
            }
        }

    }
}
