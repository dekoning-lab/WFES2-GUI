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
                    validator: IntValidator {bottom: LimitValues.nMinLimitWfesSequentialValidator; top: LimitValues.nMaxLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var n_vec = inputControllerWfesSequential.ui_N_vec
                            return n_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var n_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                n_vec[i] = inputN.textFieldText
                            else
                                n_vec[i] = inputControllerWfesSequential.ui_N_vec[i]
                        }
                        if(!Number.isNaN(Number(inputN.textFieldText)) && parseInt(inputN.textFieldText) > LimitValues.nMinLimitWfesSequentialValidator) {
                            inputControllerWfesSequential.ui_N_vec = n_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
                        }
                        inputU.textFieldTextEdited()
                        inputV.textFieldTextEdited()
                    }
                }

                LabeledTextField {
                    id: inputT
                    text: Strings.timeSub.arg(number) + Strings.colon
                    toolTipText: Strings.timeTooltip
                    validator: IntValidator {bottom: LimitValues.tExpextedMinLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var t_vec = inputControllerWfesSequential.ui_t_vec
                            return t_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var t_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                t_vec[i] = inputT.textFieldText
                            else
                                t_vec[i] = inputControllerWfesSequential.ui_t_vec[i]
                        }
                        if(!Number.isNaN(Number(inputT.textFieldText)) && parseInt(inputT.textFieldText) > LimitValues.tExpextedMinLimitWfesSequentialValidator) {
                            inputControllerWfesSequential.ui_t_vec = t_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
                        }
                    }
                }

                LabeledTextField {
                    id: inputP
                    text: Strings.pStartSub.arg(number) + Strings.colon
                    toolTipText: Strings.pStartTooltip
                    validator: DoubleValidator {bottom: LimitValues.pMinLimitWfesSequentialValidator; top: LimitValues.pMaxLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var p_vec = inputControllerWfesSequential.ui_p_vec
                            return p_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var p_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                p_vec[i] = inputP.textFieldText
                            else
                                p_vec[i] = inputControllerWfesSequential.ui_p_vec[i]
                        }
                        if(!Number.isNaN(Number(inputP.textFieldText)) && parseFloat(inputP.textFieldText) >= LimitValues.pMinLimitWfesSequentialValidator && parseFloat(inputP.textFieldText) <= LimitValues.pMaxLimitWfesSequentialValidator) {
                            inputControllerWfesSequential.ui_p_vec = p_vec
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
                    validator: DoubleValidator {bottom: LimitValues.uMinLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var u_vec = inputControllerWfesSequential.ui_u_vec
                            return u_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var u_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                u_vec[i] = inputU.textFieldText
                            else
                                u_vec[i] = inputControllerWfesSequential.ui_u_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= LimitValues.uMinLimitWfesSequentialValidator && parseFloat(inputU.textFieldText) <= LimitValues.uMaxLimitWfesSequentialValidator) {
                                inputControllerWfesSequential.ui_u_vec = u_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= LimitValues.uMinLimitWfesSequentialValidator && parseFloat(inputU.textFieldText) <= LimitValues.uMaxLimitWfesSequentialValidator / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfesSequential.ui_u_vec = u_vec
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
                    validator: DoubleValidator {bottom: LimitValues.vMinLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var v_vec = inputControllerWfesSequential.ui_v_vec
                            return v_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var v_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                v_vec[i] = inputV.textFieldText
                            else
                                v_vec[i] = inputControllerWfesSequential.ui_v_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= LimitValues.vMinLimitWfesSequentialValidator && parseFloat(inputV.textFieldText) <= LimitValues.vMaxLimitWfesSequentialValidator) {
                                inputControllerWfesSequential.ui_v_vec = v_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= LimitValues.vMinLimitWfesSequentialValidator && parseFloat(inputV.textFieldText) <= LimitValues.vMaxLimitWfesSequentialValidator / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfesSequential.ui_v_vec = v_vec
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
                    validator: DoubleValidator {bottom: LimitValues.sMinLimitWfesSequentialValidator; top: LimitValues.sMaxLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var s_vec = inputControllerWfesSequential.ui_s_vec
                            return s_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var s_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                s_vec[i] = inputS.textFieldText
                            else
                                s_vec[i] = inputControllerWfesSequential.ui_s_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= LimitValues.sMinLimitWfesSequentialValidator * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= LimitValues.sMaxLimitWfesSequentialValidator * (2 * parseInt(inputN.textFieldText))) {
                                inputControllerWfesSequential.ui_s_vec = s_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= LimitValues.sMinLimitWfesSequentialValidator && parseFloat(inputS.textFieldText) <= LimitValues.sMaxLimitWfesSequentialValidator) {
                                inputControllerWfesSequential.ui_s_vec = s_vec
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
                    validator: DoubleValidator {bottom: LimitValues.hMinLimitWfesSequentialValidator; top: LimitValues.hMaxLimitWfesSequentialValidator;}
                    textFieldText: {
                        if(number != 0) {
                            var h_vec = inputControllerWfesSequential.ui_h_vec
                            return h_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var h_vec = []
                        for(var i = 0; i < inputControllerWfesSequential.ui_num_comp; i++) {
                            if(i+1 == number)
                                h_vec[i] = inputH.textFieldText
                            else
                                h_vec[i] = inputControllerWfesSequential.ui_h_vec[i]
                        }
                        if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= LimitValues.hMinLimitWfesSequentialValidator && parseFloat(inputH.textFieldText) <= LimitValues.hMaxLimitWfesSequentialValidator) {
                            inputControllerWfesSequential.ui_h_vec = h_vec
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
