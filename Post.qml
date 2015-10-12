import QtQuick 2.0

Item {
    property string no:     ""
    //date
    property string author: ""
    property string comment: ""
    width: parent.width
    height: 50
    //picture
    Rectangle {
        color: "orange"
        anchors.fill: parent
    Text {
        id: noText
        text: no
        anchors.margins: 3
        anchors.left: parent.left
    }
    Text {
        id: authorText
        text: author
        anchors.margins: 3
        anchors.left: noText.right
    }
    Text {
        id: commentText
        text: comment
        anchors.margins: 3
        anchors.left: authorText.right
        wrapMode: Text.WrapAnywhere
    }
    }
}

