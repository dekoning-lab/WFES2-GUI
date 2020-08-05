import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import components 1.0


ApplicationWindow {
    id: root
    title: qsTr("WFES - Wright-Fisher Exact Solver (wfes_single)")

    color: Universal.chromeLowColor

    visible: true

    width: 800
    minimumWidth: 800
    height: 500
    minimumHeight: 500
    maximumWidth: 800
    maximumHeight: 500

    // Select theme for the application.
    Universal.theme: Universal.Light

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
            height: parent.height
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
                        id: modeSection
                        color: "transparent"
                        height: childrenRect.height
                        width: childrenRect.width

                        Label {
                            id: labelModel
                            text: "Mode:"
                        }

                        GridLayout {
                            id: modeSectionGrid
                            columns: 2
                            anchors {
                                top: labelModel.bottom
                                left: parent.left
                                margins: 10
                            }

                            RadioButton {
                                checked: true
                                text: qsTr("Absorption")
                            }
                            RadioButton {
                                text: qsTr("Fixation")
                            }
                            RadioButton {
                                text: qsTr("Fundamental")
                            }
                            RadioButton {
                                text: qsTr("Equilibrium")
                            }
                            RadioButton {
                                text: qsTr("Allele Age")
                            }

                        }

                    }

                    Rectangle {
                        height: 1
                        width: modeSectionGrid.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: populationSection
                        width: modeSection.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelPopulation
                            text: "Population:"
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
                                text: "N: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                text: "a: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                            }

                            LabeledTextField {
                                text: "p: "
                                //TODO Top is N
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                            }

                            LabeledTextField {
                                text: "c: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                            }

                            LabeledTextField {
                                text: "x: "
                                //TODO Top is N
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                            }
                        }

                    }

                    Rectangle {
                        height: 1
                        width: populationSectionGrid.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: mutationSection
                        width: populationSection.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelMutation
                            text: "Mutation:"
                        }

                        GridLayout {
                            id: mutationSectionGrid
                            columns: 2
                            anchors {
                                top: labelMutation.bottom
                                left: parent.left
                                margins: 10
                            }


                            LabeledTextField {
                                text: "u: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                text: "v: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
                            }

                            LabeledCheckBox {
                                text: "m: "
                                checked: true
                            }
                        }
                    }

                    Rectangle {
                        height: 1
                        width: mutationSectionGrid.width
                        color: Universal.baseHighColor
                    }

                    Rectangle {
                        id: selectionSection
                        width: mutationSection.width
                        height: childrenRect.height

                        color: "transparent"

                        Label {
                            id: labelSelection
                            text: "Selection:"
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
                                text: "s: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                text: "h: "
                                validator: DoubleValidator {bottom: 0; top: 2e-10;}
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
                    Layout.preferredHeight: parent.height

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
                                    text: "Q: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    text: "R: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    text: "N: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    text: "B: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    text: "I: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    text: "E: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    text: "V: "
                                    checked: true
                                }


                                LabeledCheckBox {
                                    text: "Res: "
                                    checked: true
                                }

                                LabeledCheckBox {
                                    Layout.row: 4
                                    Layout.column: 1
                                    text: "CSV: "
                                    checked: true
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
                                        text: "Force: "
                                        checked: true
                                    }

                                    LabeledTextField {
                                        text: "t: "
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                    }
                                }

                                ColumnLayout {
                                    width: childrenRect.width

                                    LabeledComboBox {
                                        text: "Solver:"
                                        model: [ "ViennaCL", "Pardiso" ]
                                    }

                                    LabeledComboBox {
                                        text: "Backend:"
                                        model: [ "1 Threaded", "OpenMP", "OpenCL", "CUDA" ]
                                    }
                                }

                            }
                        }

                    }

                    Button {
                        Layout.margins: 10
                        Layout.alignment: Qt.AlignRight
                        text: "Execute"
                        onClicked: masterController.ui_execute
                    }
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
                    width: childrenRect.width
                    height: childrenRect.height

                    Layout.margins: 10
                    Layout.alignment: Qt.AlignTop

                    Rectangle {
                        id: finalOutputSection
                        color: "transparent"
                        height: childrenRect.height
                        width: childrenRect.width

                        Label {
                            id: labelFinalOutput
                            text: "Output:"
                        }

                        ColumnLayout {

                            anchors {
                                top: labelFinalOutput.bottom
                                left: parent.left
                                margins: 10
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "P. ext. : "
                                textFieldText: masterController.ui_results
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "P. fix. : "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "P. abs. : "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "P. abs. std.: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "T. ext.: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "T. ext. std.: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "N. ext.: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "T. fix.: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }

                            LabeledTextField {
                                labelPreferredWidth: 75
                                text: "T. fix. std.: "
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                            }
                        }
                    }
                }
            }
        }
    }

}
