import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: postBase
    property string no:     ""
    //date
    property string author: ""
    property string comment: ""
    width: baseThread.width -20
    height: 95
    //picture
    Rectangle {
        id: postBackGround
        border.color: "black"
        color: "orange"
        anchors.fill: parent
    }

    Label {
        id: noText
        text: no
        anchors.rightMargin: 3
        anchors.leftMargin: 3
        anchors.bottomMargin: 3
        anchors.topMargin: 5
        anchors.top: parent.top
        anchors.left: parent.left
    }
    Label {
        id: authorText
        text: author
        anchors.rightMargin: 3
        anchors.leftMargin: 3
        anchors.bottomMargin: 3
        anchors.topMargin: 5
        anchors.top: parent.top
        anchors.left: noText.right
    }
    Label {
        id: commentText
        text: comment
        anchors.rightMargin: 3
        anchors.leftMargin: 3
        anchors.bottomMargin: 3
        anchors.topMargin: 5
        anchors.top: parent.top
        anchors.left: authorText.right
        anchors.right: parent.right
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        textFormat: Text.RichText
    }

    Component.onCompleted: {
        var totalContentWidth = 9 + commentText.contentWidth + authorText.contentWidth + noText.contentWidth;
        if(totalContentWidth < 1920)
            postBase.width = totalContentWidth + 10
    }

}

