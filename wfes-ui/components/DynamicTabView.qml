import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    property var widthTabView: 100
    property var heightTabView: 100
    property var urlComponent
    property var tabNames: "Tab"
    property var onAdd: function(){}
    property var onDelete: function(){}
    color: "transparent"
    width: widthTabView
    height: heightTabView

    TabView {
        id:tb
        width: parent.width
        height: parent.height

        Tab {
            id:viewComp1
            title: tabNames + " 1"
            component: {
                var component = Qt.createComponent(urlComponent)
                var object = component.createObject(tb, {})
                return object
            }
            onLoaded: {
                console.log(this.children[0].number)
                this.children[0].number = 1
            }
        }

        Tab {
            id: addTab
            title: "+"
            Rectangle {
                width: parent.width
                height: parent.height
                color:"black"
            }
            onVisibleChanged: {
                if(this.visible) {
                    onAdd()
                    var component = Qt.createComponent(urlComponent)
                    var object = component.createObject(tb, {})
                    tb.insertTab(tb.count-2, (tabNames + " " + (tb.count - 1)), object)
                    tb.currentIndex = tb.count-3
                    tb.getTab(tb.count-3).children[0].number = tb.count-2
                }
            }
        }

        Tab {
            id:removeTab
            title: "-"
            Rectangle{
                width: parent.width
                height: parent.height
                color:"black"
            }
            onVisibleChanged: {
                if(tb.count > 3) {
                    if(this.visible) {
                        onDelete()
                        tb.currentIndex = tb.count-4
                        tb.removeTab(tb.count-3)
                    }
                }else {
                    console.log("Cannot remove last Tab!")
                    tb.currentIndex = tb.count-3
                }
            }
        }

        Component{
            id:viewComp
            Rectangle{
                width: parent.width
                height: parent.height
                color:"black"
            }
        }
    }
}
