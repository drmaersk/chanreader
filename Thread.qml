import QtQuick 2.0
import QtQuick.Controls 1.4

ScrollView {
    id: baseThread

    property variant postData: [{no: "", name: "", com: "", ext: "", tim: "", trip: ""}]
    property string threadId
    onPostDataChanged: {
        threadId = postData[0].no
    }

    state: contentPanel.state
    width: contentPanel.width

    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Rectangle {
        id: threadBackGroundColor
        color: "#FFB84D"
        anchors.fill: parent
        Button {
            id: viewThreadButton
            width: 50
            height: 20
            text: "View"
            anchors.right : parent.right
            anchors.bottom : parent.bottom
            anchors.rightMargin: 10
            anchors.bottomMargin: 10
            onClicked: {
                contentPanel.viewSingleThread(baseThread.threadId)
            }
        }

    }

    Column {
        id: postContainer
        spacing: 5
        Repeater {
            id: postContainerRepeater
            model: postData
            delegate: Post {
                no: modelData.no
                name: modelData.name ? modelData.name : ""
                com: modelData.com ? modelData.com : ""
                ext: modelData.ext ? modelData.ext : ""
                tim: modelData.tim ? modelData.tim : ""
                trip: modelData.trip ? modelData.trip : ""
            }
        }
    }

    states: [
        State
        {
            name: "thread"
            PropertyChanges {
                target: viewThreadButton
                opacity: 0.0
                z: -1
            }
            PropertyChanges {
                target: baseThread
                height: 900
            }
        },
        State
        {
            name: "frontPage"
            PropertyChanges {
                target: viewThreadButton
                opacity: 1.0
                z: 1
            }
            PropertyChanges {
                target: baseThread
                height: 300
            }
        }
    ]

    Component.onCompleted: {
        height = 300//Math.min(300,(postContainer.children.length -1) * 100)

    }



}

