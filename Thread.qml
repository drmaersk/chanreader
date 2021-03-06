import QtQuick 2.0
import QtQuick.Controls 1.4

ScrollView {
    id: baseThread

    property variant postData: [{no: "", name: "", com: "", ext: "", tim: "", trip: "", w: "", h: ""}]
    property string threadId
    onPostDataChanged: {
        threadId = postData[0].no
    }

    state: contentPanel.state

    width: contentPanel.width

    //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOn
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



       ListView {
        id: postContainerListView
        model: postData
        clip: true
        spacing: 3
        delegate: Post {
            no: modelData.no
            name: modelData.name ? modelData.name : ""
            com: modelData.com ? modelData.com : ""
            ext: modelData.ext ? modelData.ext : ""
            tim: modelData.tim ? modelData.tim : ""
            trip: modelData.trip ? modelData.trip : ""
            w: modelData.w ? modelData.w : ""
            h: modelData.h ? modelData.h : ""
        }
    }

    states: [
        State
        {
            name: "thread"
            PropertyChanges {
                target: viewThreadButton
                opacity: 0.0
                z: 0
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
