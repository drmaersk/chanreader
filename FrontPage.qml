import QtQuick 2.0

Item {
    property variant threadData

    Column {
        id: threadContainer
        spacing: 2

        Repeater {
            id: threadContainerRepeater
            model: threadData
            delegate: Thread {
                postData: modelData.posts
            }
        }
    }
}

