pragma Singleton
import QtQuick 2.9

Item {
    readonly property int tooltipDelay: 500
    readonly property int tooltipTimeout: 5000

    property alias fontAwesome: fontAwesomeLoader.name
    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fonts/font-awesome.ttf"
    }
}
