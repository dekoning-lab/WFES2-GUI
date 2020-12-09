import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0

Component{
    id:viewComp
    GridLayout {
        property var number: 0
        id: tabGrid
        columns: 1
        anchors {
            top: parent.top
            left: parent.left
        }

        Rectangle {
            id: populationSection
            width: parent.width
            height: childrenRect.height

            color: "transparent"


            Label {
                id: labelPopulation
                text: "Population:"
                anchors {
                    left: parent.left
                    margins: {
                        left: 5
                    }
                }
            }

            GridLayout {
                id: populationSectionGrid
                columns: 2
                anchors {
                    top: labelPopulation.bottom
                    left: parent.left
                    margins: 10
                }

                LabeledTextField {
                    id: inputN
                    text: "N<sub>" + number + "</sub>: "
                    toolTipText: "Size of the population in the Wright Fisher Model."
                    validator: IntValidator {bottom: 2; top: 500000;}
                    textFieldText: {
                        if(number != 0) {
                            var n_vec = inputControllerWfafle.ui_N_vec
                            return n_vec[number - 1]
                        } else {
                            return "";
                        }
                    }
                }

                LabeledTextField {
                    id: inputG
                    text: "G<sub>" + number + "</sub>: "
                    toolTipText: "Number of generations for each epoch."
                    validator: IntValidator {bottom: 0; top: 500000;}
                    textFieldText: {
                        if(number != 0) {
                            var g_vec = inputControllerWfafle.ui_G_vec
                            return g_vec[number - 1]
                        } else {
                            return "";
                        }
                    }
                }
            }
        }

        Rectangle {
            id: mutationSection
            width: parent.width
            height: childrenRect.height

            color: "transparent"


            Label {
                id: labelMutation
                text: "Mutation:"
                anchors {
                    left: parent.left
                    margins: {
                        left: 5
                    }
                }
            }

            GridLayout {
                id: mutationSectionGrid
                columns: 4
                anchors {
                    top: labelMutation.bottom
                    left: parent.left
                    margins: 10
                }

                LabeledTextField {
                    id: inputU
                    text: "u<sub>" + number + "</sub>: "
                    toolTipText: "Backward mutation rate."
                    validator: DoubleValidator {bottom: 0;}
                    textFieldText: {
                        if(number != 0) {
                            var u_vec = inputControllerWfafle.ui_u_vec
                            return u_vec[number - 1]
                        } else {
                            return "";
                        }
                    }
                }

                LabeledTextField {
                    id: inputV
                    text: "v<sub>" + number + "</sub>: "
                    toolTipText: "Forward mutation rate."
                    validator: DoubleValidator {bottom: 0;}
                    textFieldText: {
                        if(number != 0) {
                            var v_vec = inputControllerWfafle.ui_v_vec
                            return v_vec[number - 1]
                        } else {
                            return "";
                        }
                    }
                }


            }
        }


        Rectangle {
            id: selectionSection
            width: parent.width
            height: childrenRect.height

            color: "transparent"


            Label {
                id: labelSelection
                text: "Selection:"
                anchors {
                    left: parent.left
                    margins: {
                        left: 5
                    }
                }
            }

            GridLayout {
                id: selectionSectionGrid
                columns: 4
                anchors {
                    top: labelSelection.bottom
                    left: parent.left
                    margins: 10
                }

                LabeledTextField {
                    id: inputS
                    text: {
                        if(globalConfiguration.ui_population_scaled)
                            return "2Ns<sub>" + number + "</sub>: "
                        else
                            return "s<sub>" + number + "</sub>: "
                    }
                    toolTipText: "Selection coefficient."
                    validator: DoubleValidator {bottom: -1; top: 1;}
                    textFieldText: {
                        if(number != 0) {
                            var s_vec = inputControllerWfafle.ui_s_vec
                            return s_vec[number - 1]
                        } else {
                            return "";
                        }
                    }
                }

                LabeledTextField {
                    id: inputH
                    text: "h<sub>" + number + "</sub>: "
                    toolTipText: "Dominance coefficient."
                    validator: DoubleValidator {bottom: 0; top: 1;}
                    textFieldText: {
                        if(number != 0) {
                            var h_vec = inputControllerWfafle.ui_h_vec
                            return h_vec[number - 1]
                        } else {
                            return "";
                        }
                    }
                }


            }
        }

    }
}
