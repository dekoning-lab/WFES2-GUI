import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3

ApplicationWindow {
    id: root
    title: qsTr("WFES - Wright-Fisher Exact Solver")

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

        Rectangle {
            id: upperMenu
            width:parent.width
            height: childrenRect.height
            color: "lightgrey"

            RowLayout {
                height: childrenRect.height
                spacing: 0

                Button {
                    id: fileButton
                    text: "File"
                    onClicked: menu.open()

                    Menu {
                        id: menu
                        y: fileButton.height

                        MenuItem {
                            text: "New..."
                            onClicked: {
                                console.warn("WARNING: File->New... clicked - Not implemented yet.")
                            }
                        }
                        MenuItem {
                            text: "Open..."
                            onClicked: {
                                console.warn("WARNING: File->Open... clicked - Not implemented yet.")
                            }
                        }
                        MenuItem {
                            text: "Save..."
                            onClicked: {
                                console.warn("WARNING: File->Save... clicked - Not implemented yet.")
                            }
                        }
                    }
                }


                Button {
                    id: settingsButton
                    text: "Settings"
                    onClicked: menu2.open()

                    Menu {
                        id: menu2
                        y: settingsButton.height

                        MenuItem {
                            text: "New..."
                            onClicked: {
                                console.warn("WARNING: Settings->New... clicked - Not implemented yet.")
                            }
                        }
                        MenuItem {
                            text: "Open..."
                            onClicked: {
                                console.warn("WARNING: Help->Open... clicked - Not implemented yet.")
                            }
                        }
                        MenuItem {
                            text: "Save"
                            onClicked: {
                                console.warn("WARNING: Settings->Save... clicked - Not implemented yet.")
                            }
                        }
                    }
                }



                Button {
                    id: helpButton
                    text: "Help"
                    onClicked: menu3.open()

                    Menu {
                        id: menu3
                        y: helpButton.height

                        MenuItem {
                            text: "New..."
                            onClicked: {
                                console.warn("WARNING: Help->New... clicked - Not implemented yet.")
                            }
                        }
                        MenuItem {
                            text: "Open..."
                            onClicked: {
                                console.warn("WARNING: Help->Open... clicked - Not implemented yet.")
                            }
                        }
                        MenuItem {
                            text: "Save"
                            onClicked: {
                                console.warn("WARNING: Help->Save... clicked - Not implemented yet.")
                            }
                        }
                    }
                }
            }

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

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        id: labelN
                                        text: "N:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        focus: true
                                    }
                                }
                            }

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "a:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                        focus: true
                                    }
                                }
                            }

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "p:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        //TODO Top is N
                                        validator: DoubleValidator {bottom: 1; top: 50000;}
                                        focus: true
                                    }
                                }
                            }


                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "c:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 0; top: 1e-3;}
                                        focus: true
                                    }
                                }
                            }


                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "x:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        //TODO Top is N
                                        validator: DoubleValidator {bottom: 1; top: 50000;}
                                        focus: true
                                    }
                                }
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

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        id: labelu
                                        text: "u:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        focus: true
                                    }
                                }
                            }

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "v:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                        focus: true
                                    }
                                }
                            }


                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "m:"
                                    }
                                    CheckBox {
                                        checked: true
                                    }
                                }
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
                            columns: 2
                            anchors {
                                top: labelSelection.bottom
                                left: parent.left
                                margins: 10
                            }

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        id: labels
                                        text: "s:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 2; top: 50000;}
                                        focus: true
                                    }
                                }
                            }

                            Rectangle {
                                width: childrenRect.width
                                height: childrenRect.height
                                color: "transparent"
                                RowLayout {
                                    Label {
                                        Layout.preferredWidth: 20
                                        text: "h:"
                                    }
                                    TextField {
                                        Layout.preferredWidth: 100
                                        validator: DoubleValidator {bottom: 0; top: 2e-10;}
                                        focus: true
                                    }
                                }
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

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "Q:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "R:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "N:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }


                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "B:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "I:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "E:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "V:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "Res:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                                Rectangle {
                                    width: childrenRect.width
                                    height: childrenRect.height
                                    color: "transparent"
                                    Layout.row: 4
                                    Layout.column: 1
                                    RowLayout {
                                        Label {
                                            Layout.preferredWidth: 40
                                            text: "CSV:"
                                        }
                                        CheckBox {
                                            checked: true
                                        }
                                    }
                                }

                            }

                        }

                        Rectangle {
                            height: 1
                            width: outputSectionGrid.width
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

                                    Rectangle {
                                        width: childrenRect.width
                                        height: childrenRect.height
                                        color: "transparent"
                                        RowLayout {
                                            Label {
                                                Layout.preferredWidth: 40
                                                text: "Force:"
                                            }
                                            CheckBox {
                                                checked: true
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: childrenRect.width
                                        height: childrenRect.height
                                        color: "transparent"
                                        RowLayout {
                                            Label {
                                                Layout.preferredWidth: 20
                                                id: labelt
                                                text: "t:"
                                            }
                                            TextField {
                                                Layout.preferredWidth: 100
                                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                                focus: true
                                            }
                                        }
                                    }
                                }
                                GridLayout {
                                    width: childrenRect.width
                                    columns: 2

                                    Label {
                                        id: labelSolver
                                        text: "Solver:"
                                    }
                                    ComboBox {
                                        Layout.fillWidth: true
                                        model: [ "ViennaCL", "Pardiso" ]
                                    }

                                    Label {
                                        id: labelBackend
                                        text: "Backend:"
                                    }

                                    ComboBox {
                                        Layout.fillWidth: true
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

                        GridLayout {
                            width: childrenRect.width
                            columns: 2

                            anchors {
                                top: labelFinalOutput.bottom
                                left: parent.left
                                margins: 10
                            }
                            Label {
                                id: labelPext
                                text: "P. ext. :"
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelPfix
                                text: "P. fix. :"
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelPabs
                                text: "P. abs. :"
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelPAbsStd
                                text: "P. abs. std. :"
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelText
                                text: "T. ext."
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelTextstd
                                text: "T. ext. std."
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelNext
                                text: "N. ext."
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelTfix
                                text: "T. fix."
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }

                            Label {
                                id: labelTfixstd
                                text: "T. fix. std."
                            }

                            TextField {
                                Layout.preferredWidth: 100
                                validator: DoubleValidator {bottom: 2; top: 50000;}
                                focus: true
                            }
                        }
                    }
                }


            }
        }
    }

}
