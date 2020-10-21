import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

//TODO Implement value validators and return exceptions.

Component{
    id:viewComp
    GridLayout {
        property var number: 0
        id: tabGrid1
        columns: 1
        anchors {
            top: parent.top
            left: parent.left
        }

        Rectangle {
            id: mutationSection1
            width: parent.width
            height: childrenRect.height

            color: "transparent"


            Label {
                id: labelMutation1
                text: "Mutation:"
                anchors {
                    left: parent.left
                    margins: {
                        left: 5
                    }
                }
            }

            GridLayout {
                id: mutationSectionGrid1
                columns: 4
                anchors {
                    top: labelMutation1.bottom
                    left: parent.left
                    margins: 10
                }

                LabeledTextField {
                    id: inputU1
                    text: "u" + number + ": "
                    toolTipText: "Backward mutation rate."
                    validator: DoubleValidator {bottom: 2; top: 50000;}
                    textFieldText: {
                        var u_vec = inputControllerWfesSweep.ui_u_vec
                        return u_vec[0]
                    }
                }

                LabeledTextField {
                    id: inputV1
                    text: "v" + number + ": "
                    toolTipText: "Forward mutation rate."
                    validator: DoubleValidator {bottom: 0; top: 2e-10;}
                    textFieldText: {
                        var v_vec = inputControllerWfesSweep.ui_v_vec
                        return v_vec[0]
                    }
                }


            }
        }


        Rectangle {
            id: selectionSection1
            width: parent.width
            height: childrenRect.height

            color: "transparent"


            Label {
                id: labelSelection1
                text: "Selection:"
                anchors {
                    left: parent.left
                    margins: {
                        left: 5
                    }
                }
            }

            GridLayout {
                id: selectionSectionGrid1
                columns: 4
                anchors {
                    top: labelSelection1.bottom
                    left: parent.left
                    margins: 10
                }

                LabeledTextField {
                    id: inputS1
                    text: "s" + number + ": "
                    toolTipText: "Selection coefficient."
                    validator: DoubleValidator {bottom: 2; top: 50000;}
                    textFieldText: {
                        var s_vec = inputControllerWfesSweep.ui_s_vec
                        return s_vec[0]
                    }
                }

                LabeledTextField {
                    id: inputH1
                    text: "h" + number + ": "
                    toolTipText: "Dominance coefficient."
                    validator: DoubleValidator {bottom: 0; top: 2e-10;}
                    textFieldText: {
                        var h_vec = inputControllerWfesSweep.ui_h_vec
                        return h_vec[0]
                    }
                }


            }
        }

    }
}
