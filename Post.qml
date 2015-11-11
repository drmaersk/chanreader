import QtQuick 2.0
import QtQuick.Controls 1.4

Flickable {
    id: postBase
    property string no
    //date
    property string name
    property string com
    property string ext
    property string tim
    property string trip
    property string w
    property string h

    width: baseThread.width -20
    height: 95
    //picture
    Rectangle {
        id: postBackGround
        border.color: "black"
        color: "orange"
        anchors.fill: parent


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
        Image { //State: hidden, preview, full
            id: previewImage
            fillMode: Image.PreserveAspectFit
            source: ""
            anchors.rightMargin: 3
            anchors.leftMargin: 3
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.top: noText.bottom
            anchors.left: parent.left
            onStatusChanged: {
                if(previewImage.status == Image.Ready)
                {
                    redrawPost();
                }
            }

            state: "hidden"
            states: [
                State {
                    name: "hidden"
                    PropertyChanges {
                        target: previewImage
                        width: 0
                        height: 0
                    }
                },
                State {
                    name: "preview"
                    PropertyChanges {
                        target: previewImage
                        width: 128
                        height: 128
                    }

                },
                State {
                    name: "full"
                    PropertyChanges {
                        target: previewImage
                        width: postBase.w
                        height: postBase.h
                    }
                }

            ]
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(parent.state == "preview"){
                        parent.state = "full"
                        redrawPost()
                    }
                    else if(parent.state == "full"){
                        parent.state = "preview"
                        redrawPost()
                    }
                }

            }

            Component.onCompleted: {
                if(postBase.ext.length > 0){
                    if(postBase.ext.trim() != ".webm"){
                        previewImage.state = "preview"
//                        previewImage.source = controllerCpp.imageUrl()+tim+ext; TODO: FIX THIS TO GET IMAGE
                    }
                }
            }
        }
        Label {
            id: comText
            text: com
            anchors.rightMargin: 3
            anchors.leftMargin: 3
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.top: noText.bottom
            anchors.left: previewImage.right
            textFormat: Text.RichText
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere

        }
    }


    Component.onCompleted: {
        redrawPost();
    }

    function redrawPost()
    {
        var totalContentWidth = 9 + comText.contentWidth + nameText.contentWidth + noText.contentWidth + previewImage.width;
        var totalTextContentHeight = 9 + comText.contentHeight + nameText.contentHeight + 9
        var totalImageContentHeight = 9 + previewImage.height + nameText.contentHeight + 9

//        if(totalContentWidth < 1920) {
            postBase.width = Math.max(300,totalContentWidth + 30)

//        }
//        else{
//            postBase.width = 900
//        }
        //comText.width = postBase.width - 30 - previewImage.width//TODO: testing

        if(totalTextContentHeight > postBase.height || totalImageContentHeight > postBase.height || totalImageContentHeight > 92){
            postBase.height = Math.max(totalTextContentHeight, totalImageContentHeight)
        }
        else{
            postBase.height = 92
        }

        postBackGround.update();
    }

}

