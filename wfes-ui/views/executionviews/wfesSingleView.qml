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
    minimumWidth: 500
    height: 500
    minimumHeight: 500

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
                width: childrenRect.width
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
            id: modeSection
            color: "transparent"
            height: childrenRect.height
            width: childrenRect.width
            anchors {
                top: upperMenu.bottom
                left: parent.left
                margins: 10
            }

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

            Rectangle {
                height: 1
                width: modeSectionGrid.width
                color: Universal.baseHighColor
                anchors {
                    topMargin: 5
                    left: parent.left
                    top: modeSectionGrid.bottom
                }
            }
        }



        Rectangle {
            id: populationSection
            width: modeSection.width
            height: childrenRect.height

            color: "transparent"
            anchors {
                top: modeSection.bottom
                left: parent.left
                margins: 10
            }

            Label {
                id: labelPopulation
                text: "Population:"
            }

            GridLayout {
                id: populationSectionGrid
                columns: 2
                width: parent.width
                anchors {
                    top: labelPopulation.bottom
                    left: parent.left
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

            Rectangle {
                height: 1
                width: parent.width
                color: Universal.baseHighColor
                anchors {
                    topMargin: 5
                    left: parent.left
                    top: populationSectionGrid.bottom
                }
            }
        }
    }

}
