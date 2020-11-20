pragma Singleton
import QtQuick 2.9

Item {
    property alias fontAwesome: fontAwesomeLoader.name

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fonts/font-awesome.ttf"
    }
}
