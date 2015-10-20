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
        console.log("currentState: " + state)
        if(state == "frontPage") {
            //use webService
            ChanApi.request(function ()
            {
                console.log("httpRequest done")
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
        console.log("I wanna see " + threadId)
        state = "thread"
        ChanApi.requestThread(threadId, function ()
        {
            console.log("httpRequest get Single thread done")
            mainThread.postData = ChanApi.getSingleThread()

        }
        );
    }
}

