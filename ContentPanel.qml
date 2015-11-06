import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: contentPanel
    FrontPage {
        id: frontPage
        anchors.fill: parent
    }
    Thread {
        id: mainThread
        anchors.fill: parent
    }
    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: true
    }

    state: "frontPageBusy"
    states: [
        State
        {
            name: "threadReady"
            PropertyChanges {
                target: mainThread
                opacity: 1.0
                z: 3
            }
            PropertyChanges {
                target: frontPage
                opacity: 0.0
                z: 0
            }
            PropertyChanges {
                target: busyIndicator
                opacity: 0.0
                z: 0
            }
        },
        State
        {
            name: "threadBusy"
            PropertyChanges {
                target: mainThread
                opacity: 0.0
                z: 0
            }
            PropertyChanges {
                target: frontPage
                opacity: 0.0
                z: 0
            }
            PropertyChanges {
                target: busyIndicator
                opacity: 1.0
                z: 3
            }
        },
        State
        {
            name: "frontPageReady"
            PropertyChanges {
                target: mainThread
                opacity: 0.0
                z: 0
            }
            PropertyChanges {
                target: frontPage
                opacity: 1.0
                z: 3
            }
            PropertyChanges {
                target: busyIndicator
                opacity: 0.0
                z: 0
            }
        },
        State
        {
            name: "frontPageBusy"
            PropertyChanges {
                target: mainThread
                opacity: 0.0
                z: 0
            }
            PropertyChanges {
                target: frontPage
                opacity: 0.0
                z: 0
            }
            PropertyChanges {
                target: busyIndicator
                opacity: 1.0
                z: 3
            }
        }
    ]

    onStateChanged: {
        if(state == "frontPageReady") {
            //todo:
            frontPage.threadData = controllerCpp.getFrontPageJson();
            console.log("frontPageReady")
        }
        else if(state == "frontPageBusy")
        {
            controllerCpp.downloadFrontPageJson();

        }
        else if(state == "threadReady")
        {
            mainThread.postData = controllerCpp.getThreadJson();
        }
        else if(state == "threadBusy")
        {
          //handled in function viewSingleThread(threadId)
        }
    }


    Connections {
        target: controllerCpp
        onFrontPageJsonDownloaded: {state = "frontPageReady";}
        onThreadJsonDownloaded:    {state = "threadReady";}
    }

    function switchState()
    {
        if(state == "threadReady")
            state = "frontPageBusy"
    }

    function viewSingleThread(threadId)
    {
        state = "threadBusy";
        controllerCpp.downloadThreadJson(threadId);
    }
}

