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
ApplicationWindow {
    id: rootWfafle
    title: qsTr("WFES - Wright-Fisher Exact Solver (WFAFLE)")

    color: Universal.chromeLowColor

    visible: true

    width: 890
    minimumWidth: 890
    maximumWidth: 890
    height: 425
    minimumHeight: 425
    maximumHeight: 425

    // Select theme for the application.
    Universal.theme: Universal.Light

    onClosing: {
        rootWfafle.destroy();
        root.visible = true;
    }

    // Center window in screen.
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        UpperMenu {
            id: upperMenu
        }

        Rectangle {
            id: content
            height: childrenRect.height
            width: parent.width
            color: "transparent"

            anchors {
                top: upperMenu.bottom
                left: parent.left
            }

            RowLayout {
                id: mainGrid
                Layout.fillHeight: true

                ColumnLayout {
                    id: column1
                    width: childrenRect.width
                    height: childrenRect.height

                    Layout.margins: 10
                    Layout.alignment: Qt.AlignTop

                    Rectangle {
                        id: componentsSection
                        width: commonSection.width + 10
                        height: childrenRect.height

                        color: "transparent"

                        Layout.alignment: Qt.AlignTop

                        DynamicTabView {
                            id: componentsSectionTabView
                            width: commonSection.width + 10
                            height: 270
                            tabNames: "Comp."
                            urlComponent: "qrc:/views/executionviews/tabcomponents/tabWfafleComponent.qml"
                            onAdd: function(){
                                var num_comps = inputControllerWfafle.ui_num_comp
                                inputControllerWfafle.ui_num_comp = parseInt(num_comps) + 1

                                var vector = inputControllerWfafle.ui_N_vec
                                vector[num_comps] = inputControllerWfafle.ui_N_vec[num_comps-1]
                                inputControllerWfafle.ui_N_vec = vector

                                vector = inputControllerWfafle.ui_G_vec
                                vector[num_comps] = inputControllerWfafle.ui_G_vec[num_comps-1]
                                inputControllerWfafle.ui_G_vec = vector

                                vector = inputControllerWfafle.ui_s_vec
                                vector[num_comps] = inputControllerWfafle.ui_s_vec[num_comps-1]
                                inputControllerWfafle.ui_s_vec = vector

                                vector = inputControllerWfafle.ui_h_vec
                                vector[num_comps] = inputControllerWfafle.ui_h_vec[num_comps-1]
                                inputControllerWfafle.ui_h_vec = vector

                                vector = inputControllerWfafle.ui_u_vec
                                vector[num_comps] = inputControllerWfafle.ui_u_vec[num_comps-1]
                                inputControllerWfafle.ui_u_vec = vector

                                vector = inputControllerWfafle.ui_v_vec
                                vector[num_comps] = inputControllerWfafle.ui_v_vec[num_comps-1]
                                inputControllerWfafle.ui_v_vec = vector
                            }
                            onDelete: function(){
                                var num_comps = inputControllerWfafle.ui_num_comp
                                inputControllerWfafle.ui_num_comp = parseInt(num_comps) - 1
                            }
                        }

                    }

                    Rectangle {
                        height: 1
                        width: componentsSectionTabView.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: commonSection
                        width: childrenRect.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelCommonParameters
                            text: "Common Parameters"
                        }

                        GridLayout {
                            id: commonSectionGrid
                            columns: 2
                            anchors {
                                top: labelCommonParameters.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                id: inputA
                                text: "a: "
                                toolTipText: "Tail truncation weight."
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                textFieldText: inputControllerWfafle.ui_a
                            }

                            LabeledTextField {
                                id: inputP
                                text: "p: "
                                toolTipText: "Initial allele count."
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                textFieldText: inputControllerWfafle.ui_p
                            }

                        }
                    }

                }

                Rectangle {
                    id: separator1
                    width: 1
                    Layout.fillHeight: true
                    color: Universal.baseHighColor
                    Layout.topMargin: 10
                    Layout.bottomMargin:10
                }

                ColumnLayout {
                    id: column2
                    height: parent.height

                    ColumnLayout {
                        Layout.alignment: Qt.AlignTop
                        Layout.margins: 10

                        Rectangle {
                            id: outputSection
                            color: "transparent"
                            height: childrenRect.height
                            width: childrenRect.width

                            Label {
                                id: labelOutput
                                text: "Output Options:"
                            }

                            GridLayout {
                                id: outputSectionGrid
                                width: childrenRect.width
                                columns: 2
                                anchors {
                                    top: labelOutput.bottom
                                    left: parent.left
                                    margins: 10
                                }

                                LabeledCheckBox {
                                    id: inputWriteDist
                                    text: "Dist: "
                                    toolTipText: "Output Allele freq. dist. as CSV file."
                                    checked: inputControllerWfafle.ui_output_Dist
                                }

                            }

                        }

                        Rectangle {
                            height: 1
                            width: Math.max(executionSection.width, outputSection.width)
                            color: Universal.baseHighColor
                        }

                        Rectangle {
                            id: executionSection
                            color: "transparent"
                            height: childrenRect.height
                            width: childrenRect.width

                            Label {
                                id: labelExecution
                                text: "Execution:"
                            }


                            ColumnLayout {

                                width: childrenRect.width
                                anchors {
                                    top: labelExecution.bottom
                                    left: parent.left
                                    margins: 10
                                }
                                RowLayout {
                                    width: childrenRect.width

                                    LabeledCheckBox {
                                        id: inputForce
                                        toolTipText: "Do not perform parameter checks."
                                        text: "Force: "
                                        checked: inputControllerWfafle.ui_force
                                    }

                                    LabeledTextField {
                                        id: inputT
                                        text: "t: "
                                        labelPreferredWidth: 10
                                        toolTipText: "Number of threads for OpenMP."
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        textFieldText: inputControllerWfafle.ui_t
                                    }
                                }

                                ColumnLayout {
                                    width: childrenRect.width

                                    LabeledComboBox {
                                        id: comboBoxLibrary
                                        text: "Library:"
                                        model: ["Pardiso", "ViennaCL"]
                                        toolTipText: "Library used for solving matrix systems."
                                        onTextChanged: {
                                            if(comboBoxLibrary.currentText === "Pardiso") {
                                                comboBoxBackend.enabled = false
                                                comboBoxSolver.enabled = false
                                            }else if (comboBoxLibrary.currentText === "ViennaCL"){
                                                comboBoxBackend.enabled = true
                                                comboBoxSolver.enabled = true
                                            }
                                        }
                                    }

                                    LabeledComboBox {
                                        id: comboBoxSolver
                                        text: "Solver:"
                                        toolTipText: "Solver used by viennacl."
                                        model: ["GMRes", "BicGStab"]
                                        enabled: (comboBoxLibrary.currentText === "ViennaCL")
                                    }

                                    LabeledTextField {
                                        id: inputI
                                        text: "I. Dist.: "
                                        toolTipText: "Path to initial probability distribution CSV file."
                                        labelPreferredWidth: 75
                                        textFieldPreferredWidth: 185
                                        textFieldText: inputControllerWfafle.ui_initial_distribution
                                    }

                                    Button{
                                        text: "Search"
                                        onClicked: fileDialog.open()
                                    }


                                    FileDialog {
                                        id: fileDialog
                                        title: "Please choose a csv file"
                                        nameFilters: [ "csv files (*.csv)" ]
                                        onAccepted: {
                                            var path = fileDialog.fileUrl.toString()
                                            path = path.replace(/^(file:\/{2})/,"");
                                            inputI.textFieldText = path
                                        }
                                    }

                                }

                            }
                        }

                    }

                    RowLayout {
                        id: row2
                        Layout.preferredWidth: parent.width

                        Button {
                            id: stopButton
                            Layout.margins: 10
                            Layout.alignment: Qt.AlignRight
                            text: "Stop"

                            Binding {
                                target: stopButton
                                property: "enabled"
                                value: !outputControllerWfafle.ui_get_not_exec

                            }

                            onClicked: {
                                outputControllerWfafle.ui_stop
                                stopButton.enabled = false
                                executeButton.enabled = true
                            }
                        }

                        Button {
                            id: executeButton
                            Layout.margins: 10
                            Layout.alignment: Qt.AlignRight
                            text: "Execute"

                            Binding {
                                target: executeButton
                                property: "enabled"
                                value: outputControllerWfafle.ui_get_not_exec

                            }

                            // All changes made in backend from GUI are done here.
                            onClicked: {
                                bottomMenu.visibleProgressBar = true

                                inputControllerWfafle.ui_a = inputA.textFieldText
                                inputControllerWfafle.ui_p - inputP.textFieldText
                                var N_vec = []
                                var G_vec = []
                                var u_vec = []
                                var v_vec = []
                                var s_vec = []
                                var h_vec = []
                                for(var i = 0; i < inputControllerWfafle.ui_num_comp; i++) {
                                    componentsSectionTabView.children[0].getTab(i).active = true
                                    var N = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[0].textFieldText
                                    var G = componentsSectionTabView.children[0].getTab(i).item.children[0].children[1].children[1].textFieldText
                                    var u = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[0].textFieldText
                                    var v = componentsSectionTabView.children[0].getTab(i).item.children[1].children[1].children[1].textFieldText
                                    var s = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[0].textFieldText
                                    var h = componentsSectionTabView.children[0].getTab(i).item.children[2].children[1].children[1].textFieldText
                                    N_vec.push(N)
                                    G_vec.push(G)
                                    u_vec.push(u)
                                    v_vec.push(v)
                                    s_vec.push(s)
                                    h_vec.push(h)
                                }
                                inputControllerWfafle.ui_N_vec = N_vec
                                inputControllerWfafle.ui_G_vec = G_vec
                                inputControllerWfafle.ui_u_vec = u_vec
                                inputControllerWfafle.ui_v_vec = v_vec
                                inputControllerWfafle.ui_s_vec = s_vec
                                inputControllerWfafle.ui_h_vec = h_vec

                                inputControllerWfafle.ui_output_Dist = inputWriteDist.checked
                                inputControllerWfafle.ui_t = inputT.textFieldText
                                inputControllerWfafle.ui_force = inputForce.checked

                                inputControllerWfafle.ui_initial_distribution = inputI.textFieldText

                                inputControllerWfafle.ui_library = comboBoxLibrary.currentText;
                                inputControllerWfafle.ui_solver = comboBoxSolver.currentText;

                                console.log(outputControllerWfafle.ui_get_error_message)
                                if(outputControllerWfafle.ui_get_error_message === "") {
                                    executeButton.enabled = false
                                    stopButton.enabled = true
                                    outputControllerWfafle.ui_execute
                                } else {
                                    messageDialog.text = outputControllerWfafle.ui_get_error_message
                                    messageDialog.open()
                                }
                                outputControllerWfafle.ui_reset_error
                            }

                        }

                    }
                }

                MessageDialog {
                    id: messageDialog
                    title: "Warning"
                    text: ""
                    icon: StandardIcon.Warning
                }

                Rectangle {
                    id: separator2
                    width: 1
                    Layout.fillHeight: true
                    color: Universal.baseHighColor
                    Layout.topMargin: 10
                    Layout.bottomMargin:10
                }

                ColumnLayout {
                    id: column3
                    Layout.margins: 10
                    Layout.alignment: Qt.AlignTop

                    Label {
                        id: labelMoments
                        text: "Output:"
                        font.bold: true
                    }

                    Label {
                        id: labelMoments2
                        text: "Allele freq. dist.:"
                    }

                    Rectangle {
                        width: labelMoments.width * 4
                        height: childrenRect.height + 1
                        color: "transparent"
                        border.width: 1

                        Layout.alignment: Qt.AlignTop
                        Layout.margins: 10

                        ScrollView {
                            width: parent.width - 1
                            height: 200
                            clip: true
                            topPadding: 1
                            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                            contentHeight: 200
                            contentWidth: parent.width
                            ListView {
                                id: listViewMoments
                                model: outputControllerWfafle.ui_probs
                                delegate: ItemDelegate {
                                  width: parent.width
                                  height: 25
                                  Text {
                                      text: modelData;
                                      width: parent.width;
                                      height: parent.height;
                                  }
                                }
                            }
                        }

                    }


                }
            }
        }

        Rectangle {
            id: separatorBottomBar
            height: 1
            width: parent.width
            color: Universal.baseHighColor
            anchors {
                top: content.bottom
                left: parent.left
            }
        }

        Binding {
            target: bottomMenu
            property: "visibleProgressBar"
            value: !outputControllerWfafle.ui_get_not_exec

        }

        BottomMenuExecutionView {
            id: bottomMenu
            width: parent.width
            executionProgress: outputControllerWfafle.ui_progress

            executionTime: {
                outputControllerWfafle.ui_get_time == "" ? "" : outputControllerWfafle.ui_get_time + "s"
            }
            anchors {
                top: separatorBottomBar.bottom
                left: parent.left
            }
        }


    }

}
