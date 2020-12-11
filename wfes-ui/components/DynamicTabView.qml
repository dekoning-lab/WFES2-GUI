import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: rect
    property var widthTabView: 100
    property var heightTabView: 100
    property var urlComponent
    property var tabNames: "Tab"
    property var onAdd: function(){}
    property var onDelete: function(){}
    property var onLoaded: function(){}
    property var changeBoxColor: function(){}
    color: "transparent"
    width: widthTabView
    height: heightTabView

    TabView {
        id:tb
        width: parent.width
        height: parent.height
        style: TabViewStyle {

        }

        function addTab() {
            onAdd()
            var component = Qt.createComponent(urlComponent)
            var object = component.createObject(tb, {})
            tb.insertTab(tb.count-2, (tabNames + " " + (tb.count - 1)), object)
            tb.currentIndex = tb.count-3
            tb.getTab(tb.count-3).children[0].number = tb.count-2
        }

        function deleteTab() {
            if(tb.count > 3) {
                if(this.visible) {
                    onDelete()
                    tb.currentIndex = tb.count-4
                    tb.removeTab(tb.count-3)
                }
            }else {
                tb.currentIndex = tb.count-3
            }
        }

        Tab {
            id:viewComp1
            title: tabNames + " 1"
            width: implicitWidth

            component: {
                var component = Qt.createComponent(urlComponent)
                var object = component.createObject(tb, {})
                return object
            }
            onLoaded: {
                this.children[0].number = 1
                rect.onLoaded();
            }
        }

        Tab {
            id: addTab
            title: "+"
            width: implicitWidth

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
                    changeBoxColor()
                }
            }
        }

        Tab {
            id:removeTab
            title: "-"
            width: implicitWidth

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
                        changeBoxColor()
                    }
                }else {
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
