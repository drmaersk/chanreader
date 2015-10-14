import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: postBase
    property string no:     ""
    //date
    property string name: ""
    property string com: ""
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
        id: nameText
        text: name
        anchors.rightMargin: 3
        anchors.leftMargin: 3
        anchors.bottomMargin: 3
        anchors.topMargin: 5
        anchors.top: parent.top
        anchors.left: noText.right
    }
    Label {
        id: comText
        text: com
        anchors.rightMargin: 3
        anchors.leftMargin: 3
        anchors.bottomMargin: 3
        anchors.topMargin: 5
        anchors.top: parent.top
        anchors.left: nameText.right
        anchors.right: parent.right
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        textFormat: Text.RichText
    }

    Component.onCompleted: {
        console.log("post.onComplete")
        var totalContentWidth = 9 + comText.contentWidth + nameText.contentWidth + noText.contentWidth;
        if(totalContentWidth < 1920)
            postBase.width = totalContentWidth + 10
    }

}

