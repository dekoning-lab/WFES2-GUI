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
                    textFieldTextEdited: function(){
                        var n_vec = []
                        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                            if(i+1 == number)
                                n_vec[i] = inputN.textFieldText
                            else
                                n_vec[i] = inputControllerWfafle.ui_N_vec[i]
                        }
                        if(!Number.isNaN(Number(inputN.textFieldText)) && parseInt(inputN.textFieldText) > 1) {
                            inputControllerWfafle.ui_N_vec = n_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
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
                    textFieldTextEdited: function(){
                        var g_vec = []
                        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                            if(i+1 == number)
                                g_vec[i] = inputG.textFieldText
                            else
                                g_vec[i] = inputControllerWfafle.ui_G_vec[i]
                        }
                        if(!Number.isNaN(Number(inputG.textFieldText)) && parseInt(inputG.textFieldText) > 1) {
                            inputControllerWfafle.ui_G_vec = g_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
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
                    text: {
                        if(globalConfiguration.ui_population_scaled)
                            return "4Nu<sub>" + number + "</sub>: "
                        else
                            return "u<sub>" + number + "</sub>: "
                    }
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
                    textFieldTextEdited: function(){
                        var u_vec = []
                        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                            if(i+1 == number)
                                u_vec[i] = inputU.textFieldText
                            else
                                u_vec[i] = inputControllerWfafle.ui_u_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1) {
                                inputControllerWfafle.ui_u_vec = u_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfafle.ui_u_vec = u_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        }
                    }
                }

                LabeledTextField {
                    id: inputV
                    text: {
                        if(globalConfiguration.ui_population_scaled)
                            return "4Nv<sub>" + number + "</sub>: "
                        else
                            return "v<sub>" + number + "</sub>: "
                    }
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
                    textFieldTextEdited: function(){
                        var v_vec = []
                        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                            if(i+1 == number)
                                v_vec[i] = inputV.textFieldText
                            else
                                v_vec[i] = inputControllerWfafle.ui_v_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1) {
                                inputControllerWfafle.ui_v_vec = v_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfafle.ui_v_vec = v_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
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
                    textFieldTextEdited: function(){
                        var s_vec = []
                        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                            if(i+1 == number)
                                s_vec[i] = inputS.textFieldText
                            else
                                s_vec[i] = inputControllerWfafle.ui_s_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                inputControllerWfafle.ui_s_vec = s_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 && parseFloat(inputS.textFieldText) <= 1) {
                                inputControllerWfafle.ui_s_vec = s_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
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
                    textFieldTextEdited: function(){
                        var h_vec = []
                        for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                            if(i+1 == number)
                                h_vec[i] = inputH.textFieldText
                            else
                                h_vec[i] = inputControllerWfafle.ui_h_vec[i]
                        }
                        if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= 0 && parseFloat(inputH.textFieldText) <= 1) {
                            inputControllerWfafle.ui_h_vec = h_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
                        }
                    }
                }


            }
        }

    }
}
