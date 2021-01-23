import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0
import assets 1.0

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
                text: Strings.population + Strings.colon
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
                    text: Strings.nSub.arg(number) + Strings.colon
                    toolTipText: Strings.nTooltip
                    validator: IntValidator {bottom: 2; top: 500000;}
                    textFieldText: {
                        if(number != 0) {
                            var n_vec = inputControllerWfafd.ui_N_vec
                            return n_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var n_vec = []
                        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                            if(i+1 == number)
                                n_vec[i] = inputN.textFieldText
                            else
                                n_vec[i] = inputControllerWfafd.ui_N_vec[i]
                        }
                        if(!Number.isNaN(Number(inputN.textFieldText)) && parseInt(inputN.textFieldText) > 1) {
                            inputControllerWfafd.ui_N_vec = n_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
                        }
                        inputU.textFieldTextEdited()
                        inputV.textFieldTextEdited()
                    }
                }

                LabeledTextField {
                    id: inputG
                    text: Strings.gSub.arg(number) + Strings.colon
                    toolTipText: Strings.gTooltip
                    validator: IntValidator {bottom: 0; top: 500000;}
                    textFieldText: {
                        if(number != 0) {
                            var g_vec = inputControllerWfafd.ui_G_vec
                            return g_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var g_vec = []
                        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                            if(i+1 == number)
                                g_vec[i] = inputG.textFieldText
                            else
                                g_vec[i] = inputControllerWfafd.ui_G_vec[i]
                        }
                        if(!Number.isNaN(Number(inputG.textFieldText)) && parseInt(inputG.textFieldText) > 0) {
                            inputControllerWfafd.ui_G_vec = g_vec
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
                text: Strings.mutation + Strings.colon
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
                            return Strings.uSubScaled.arg(number) + Strings.colon
                        else
                            return Strings.uSub.arg(number) + Strings.colon
                    }
                    toolTipText: Strings.uTooltip
                    validator: DoubleValidator {bottom: 0;}
                    textFieldText: {
                        if(number != 0) {
                            var u_vec = inputControllerWfafd.ui_u_vec
                            return u_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var u_vec = []
                        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                            if(i+1 == number)
                                u_vec[i] = inputU.textFieldText
                            else
                                u_vec[i] = inputControllerWfafd.ui_u_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1) {
                                inputControllerWfafd.ui_u_vec = u_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfafd.ui_u_vec = u_vec
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
                            return Strings.vSubScaled.arg(number) + Strings.colon
                        else
                            return Strings.vSub.arg(number) + Strings.colon
                    }
                    toolTipText: Strings.vTooltip
                    validator: DoubleValidator {bottom: 0;}
                    textFieldText: {
                        if(number != 0) {
                            var v_vec = inputControllerWfafd.ui_v_vec
                            return v_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var v_vec = []
                        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                            if(i+1 == number)
                                v_vec[i] = inputV.textFieldText
                            else
                                v_vec[i] = inputControllerWfafd.ui_v_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1) {
                                inputControllerWfafd.ui_v_vec = v_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfafd.ui_v_vec = v_vec
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
                text: Strings.selection + Strings.colon
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
                            return Strings.sSubScaled.arg(number) + Strings.colon
                        else
                            return Strings.sSub.arg(number) + Strings.colon
                    }
                    toolTipText: Strings.sTooltip
                    validator: DoubleValidator {bottom: -1; top: 1;}
                    textFieldText: {
                        if(number != 0) {
                            var s_vec = inputControllerWfafd.ui_s_vec
                            return s_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var s_vec = []
                        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                            if(i+1 == number)
                                s_vec[i] = inputS.textFieldText
                            else
                                s_vec[i] = inputControllerWfafd.ui_s_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                inputControllerWfafd.ui_s_vec = s_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 && parseFloat(inputS.textFieldText) <= 1) {
                                inputControllerWfafd.ui_s_vec = s_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        }
                    }
                }

                LabeledTextField {
                    id: inputH
                    text: Strings.hSub.arg(number) + Strings.colon
                    toolTipText: Strings.hTooltip
                    validator: DoubleValidator {bottom: 0; top: 1;}
                    textFieldText: {
                        if(number != 0) {
                            var h_vec = inputControllerWfafd.ui_h_vec
                            return h_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var h_vec = []
                        for(var i = 0; i < inputControllerWfafd.ui_num_comp; i++) {
                            if(i+1 == number)
                                h_vec[i] = inputH.textFieldText
                            else
                                h_vec[i] = inputControllerWfafd.ui_h_vec[i]
                        }
                        if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= 0 && parseFloat(inputH.textFieldText) <= 1) {
                            inputControllerWfafd.ui_h_vec = h_vec
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
