import QtQuick 2.0
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

    state: "frontPage"
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
        }
    ]
    onStateChanged: {
        if(state == "frontPage") {
            ChanApi.request(function ()
            {
                frontPage.threadData = ChanApi.getThreads();
            }
            );
        }
    }

    function switchState()
    {
        if(state == "frontPage")
            state = "thread"
        else
            state = "frontPage"
    }

    function viewSingleThread(threadId)
    {
        state = "thread"
        ChanApi.requestThread(threadId, function ()
        {
            mainThread.postData = ChanApi.getSingleThread()

        }
        );
    }
}

