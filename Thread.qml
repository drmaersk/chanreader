import QtQuick 2.0
import QtQuick.Controls 1.4

ScrollView {
    id: baseThread
    property variant postData: [{no: "", name: "", com: ""}]

    width: contentPanel.width

    Rectangle {
        id: threadBackGroundColor
        color: "#FFB84D"
        anchors.fill: parent

    }

    Column {
        id: postContainer
        spacing: 5
        Repeater {
            id: postContainerRepeater
            model: postData
            delegate: Post {
                no: modelData.no
                name: modelData.name
                com: modelData.com
            }
        }
    }
    Component.onCompleted: {
        height = Math.min(300,(postContainer.children.length -1) * 100)
    }
}

