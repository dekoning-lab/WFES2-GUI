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
                            var n_vec = inputControllerWfesSwitching.ui_N_vec
                            return n_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var n_vec = []
                        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                            if(i+1 == number)
                                n_vec[i] = inputN.textFieldText
                            else
                                n_vec[i] = inputControllerWfesSwitching.ui_N_vec[i]
                        }
                        if(!Number.isNaN(Number(inputN.textFieldText)) && parseInt(inputN.textFieldText) > 1) {
                            inputControllerWfesSwitching.ui_N_vec = n_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
                        }
                        inputU.textFieldTextEdited()
                        inputV.textFieldTextEdited()
                    }
                }

                LabeledTextField {
                    id: inputP
                    text: Strings.pStartSub.arg(number) + Strings.colon
                    toolTipText: Strings.pStartTooltip
                    validator: DoubleValidator {bottom: 0; top: 1;}
                    textFieldText: {
                        if(number != 0) {
                            var p_vec = inputControllerWfesSwitching.ui_p_vec
                            return p_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var p_vec = []
                        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                            if(i+1 == number)
                                p_vec[i] = inputP.textFieldText
                            else
                                p_vec[i] = inputControllerWfesSwitching.ui_p_vec[i]
                        }
                        if(!Number.isNaN(Number(inputP.textFieldText)) && parseFloat(inputP.textFieldText) >= 0) {
                            inputControllerWfesSwitching.ui_p_vec = p_vec
                            borderColor = "#555555"
                        } else {
                            borderColor = "#ff0000"
                        }
                    }
                }

                LabeledTextField {
                    id: inputR
                    text: Strings.rSub.arg(number) + Strings.colon
                    toolTipText: Strings.rTooltip
                    textFieldPreferredWidth: 235
                    Layout.columnSpan: 2
                    textFieldText: {
                        if(number != 0) {
                            var r_vec = inputControllerWfesSwitching.ui_r_vec
                            return r_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        // Check current to see if paint red.
                        var r_vec = []
                        for(var i = 0; i < componentsSectionTabView.children[0].count - 2; i++) {
                            componentsSectionTabView.children[0].getTab(i).active = true
                            var r = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
                            r_vec.push(r)
                        }

                        borderColor = "#555555"

                        var current = r_vec[number-1]
                        if(r_vec[number] === "")
                            borderColor = "#ff0000"

                        console.log(number)
                        var splitted = r_vec[number-1].split(", ")
                        if(splitted.length !== componentsSectionTabView.children[0].count - 2)
                            borderColor = "#ff0000"

                        for(i = 0; i < splitted.length; i++) {
                            if(splitted[i] === "") {
                                borderColor = "#ff0000"
                                break;
                            } else if(Number.isNaN(Number(splitted[i]))) {
                                borderColor = "#ff0000"
                                break;
                            } else if(parseFloat(splitted[i]) < 0) {
                                borderColor = "#ff0000"
                                break;
                            } else if (parseFloat(splitted[i]) > 1) {
                                borderColor = "#ff0000"
                                break;
                            }
                        }

                        var save = true
                        r_vec = []
                        for(i = 0; i < componentsSectionTabView.children[0].count - 2; i++) {
                            componentsSectionTabView.children[0].getTab(i).active = true
                            r = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
                            r_vec.push(r)
                        }

                        for(i = 0; i < componentsSectionTabView.children[0].count - 2; i++) {
                            r = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[2].textFieldText
                            if(r === "")
                                save = false
                            splitted = r_vec[i].split(", ")
                            if(splitted.length !== componentsSectionTabView.children[0].count - 2)
                                save = false
                            if(splitted.length > 1) {
                                var valid = true;
                                for(var j = 0; j < splitted.length; j++) {
                                    if(splitted[j] === "") {
                                        save = false
                                        break;
                                    } else if(Number.isNaN(Number(splitted[j]))) {
                                        save = false
                                        break;
                                    } else if(parseFloat(splitted[j]) < 0) {
                                        save = false
                                        break;
                                    } else if (parseFloat(splitted[j]) > 1) {
                                        save = false
                                        break;
                                    }
                                }
                            } else {
                                if(r_vec[i] === "") {
                                    save = false
                                break;
                                } else if(Number.isNaN(Number(r_vec[i]))) {
                                    save = false
                                break;
                                } else if(parseFloat(r_vec[i]) < 0) {
                                    save = false
                                    break;
                                } else if (parseFloat(r_vec[i]) > 1) {
                                    save = false
                                    break;
                                }
                            }
                        }

                        if(save)
                            inputControllerWfesSwitching.ui_r_vec = r_vec

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
                            var u_vec = inputControllerWfesSwitching.ui_u_vec
                            return u_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var u_vec = []
                        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                            if(i+1 == number)
                                u_vec[i] = inputU.textFieldText
                            else
                                u_vec[i] = inputControllerWfesSwitching.ui_u_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1) {
                                inputControllerWfesSwitching.ui_u_vec = u_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputU.textFieldText)) && parseFloat(inputU.textFieldText) >= 0 && parseFloat(inputU.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfesSwitching.ui_u_vec = u_vec
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
                            var v_vec = inputControllerWfesSwitching.ui_v_vec
                            return v_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var v_vec = []
                        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                            if(i+1 == number)
                                v_vec[i] = inputV.textFieldText
                            else
                                v_vec[i] = inputControllerWfesSwitching.ui_v_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1) {
                                inputControllerWfesSwitching.ui_v_vec = v_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputV.textFieldText)) && parseFloat(inputV.textFieldText) >= 0 && parseFloat(inputV.textFieldText) <= 1 / (4 * parseInt(inputN.textFieldText))) {
                                inputControllerWfesSwitching.ui_v_vec = v_vec
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
                            var s_vec = inputControllerWfesSwitching.ui_s_vec
                            return s_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var s_vec = []
                        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                            if(i+1 == number)
                                s_vec[i] = inputS.textFieldText
                            else
                                s_vec[i] = inputControllerWfesSwitching.ui_s_vec[i]
                        }
                        if(globalConfiguration.ui_population_scaled) {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 * (2 * parseInt(inputN.textFieldText)) && parseFloat(inputS.textFieldText) <= 1 * (2 * parseInt(inputN.textFieldText))) {
                                inputControllerWfesSwitching.ui_s_vec = s_vec
                                borderColor = "#555555"
                            } else {
                                borderColor = "#ff0000"
                            }
                        } else {
                            if(!Number.isNaN(Number(inputS.textFieldText)) && parseFloat(inputS.textFieldText) >= -1 && parseFloat(inputS.textFieldText) <= 1) {
                                inputControllerWfesSwitching.ui_s_vec = s_vec
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
                            var h_vec = inputControllerWfesSwitching.ui_h_vec
                            return h_vec[number - 1]
                        } else {
                            return Strings.empty;
                        }
                    }
                    textFieldTextEdited: function(){
                        var h_vec = []
                        for(var i = 0; i < inputControllerWfesSwitching.ui_num_comp; i++) {
                            if(i+1 == number)
                                h_vec[i] = inputH.textFieldText
                            else
                                h_vec[i] = inputControllerWfesSwitching.ui_h_vec[i]
                        }
                        if(!Number.isNaN(Number(inputH.textFieldText)) && parseFloat(inputH.textFieldText) >= 0 && parseFloat(inputH.textFieldText) <= 1) {
                            inputControllerWfesSwitching.ui_h_vec = h_vec
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
