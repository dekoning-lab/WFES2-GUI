import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.3
import assets 1.0
import components 1.0


Rectangle{
    id:displayImage
    property alias source: imageQ.source
    width:parent.width
    height:parent.height
    color: "transparent"
    Image {
        id: imageQ
        sourceSize.width: parent.width
        sourceSize.height: parent.width
        source: ""
        asynchronous: true
        
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
    }
    
    MouseArea{
        width: parent.width
        height: parent.height
        
        drag.target: displayImage
        
        anchors.centerIn: displayImage
        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier) {
                displayImage.rotation += wheel.angleDelta.y / 120 * 5;
                if (Math.abs(displayImage.rotation) < 4)
                    parent.rotation = 0;
            } else {
                displayImage.rotation += wheel.angleDelta.x / 120;
                if (Math.abs(displayImage.rotation) < 0.6)
                    displayImage.rotation = 0;
                var scaleBefore = parent.scale;
                var incrementScale = displayImage.scale * wheel.angleDelta.y / 120 / 10
                if(displayImage.scale + incrementScale < 2.5 && displayImage.scale + incrementScale > 0.8)
                    displayImage.scale += displayImage.scale * wheel.angleDelta.y / 120 / 10
            }
        }
    }
}
