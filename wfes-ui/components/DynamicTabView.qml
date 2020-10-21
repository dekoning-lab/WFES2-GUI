import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    property var widthTabView: 100
    property var heightTabView: 100
    color: "transparent"
    width: widthTabView
    height: heightTabView
    TabView {
        id:tb
        width: parent.width
        height: parent.height

        Tab {
            id:viewComp1
            title: "Tab 1"
            Rectangle{
                width: parent.width
                height: parent.height
                color:"black"
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
                    console.log(tb.count)
                    tb.insertTab(tb.count-2, ("Tab " + (tb.count - 1)), viewComp)
                    tb.currentIndex = tb.count-3
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
