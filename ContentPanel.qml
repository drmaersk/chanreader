import QtQuick 2.0
import QtQuick.Controls 1.4
import "frontPageApi.js" as ChanApi

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
            name: "thread"
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
            name: "frontPage"
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
        if(state == "frontPage") {
            //todo:
        }
        else if(state == "frontPageBusy")
        {
                ChanApi.requestPage(function ()
                {
                    frontPage.threadData = ChanApi.getThreads();
                    fileDownloaderCpp.postList = ChanApi.getThreads();
                }
            );
        }
    }

    Connections {
        target: fileDownloaderCpp
        onFilesDownloaded: switchState()
    }

    function switchState()
    {
        if(state == "frontPageBusy")
            state = "frontPage"
        else if(state == "threadBusy")
            state = "thread"
    }

    function viewSingleThread(threadId)
    {
        state = "threadBusy"
        ChanApi.requestThread(threadId, function ()
        {
            mainThread.postData = ChanApi.getSingleThread()
            fileDownloaderCpp.thread = ChanApi.getSingleThread()
        }
        );
    }
}

