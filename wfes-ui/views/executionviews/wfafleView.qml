import QtQuick 2.0
import QtQuick.Controls 1.0
import components 1.0

ApplicationWindow{
    id:win
    height: 800
    width: 600
    title: qsTr("Tab with plus button demo.")

    color: Universal.chromeLowColor

    visible: true

    DynamicTabView {
        id: tb
        width: 500
        height: 500
    }

}
