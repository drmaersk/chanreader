import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    minimumWidth: 800
    minimumHeight: 600
    Component.onCompleted: {
        console.log("Enter app")
    }


    Component.onDestruction: {
        console.log("Exit app")
    }

    menuBar: MenuBar
    {

    Menu {
        title: "File"
        MenuItem {text: "save"}
        MenuItem {text: "load"} //TODO: On open: Thread organizer, sort, delete and rate threads. Structure: First select board then a table of threads come up.
        MenuItem {text: "exit"
            onTriggered: window.close()}
    }
    Menu {
        title: "Settings"
        MenuItem {text: "menu2"} }
}

toolBar: ToolBar {
    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: "/tv/"
            onClicked: contentPanel.switchState(); //TODO: For testing remove
        }
        ToolButton {
            anchors.right: parent.right

            Image {
                source: "img/add2128.png"
                anchors.margins: 8
                anchors.fill: parent}
        }

    }
}

ContentPanel {
    id: contentPanel
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.margins: 3
}

}


