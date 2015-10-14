import QtQuick 2.0
import "frontPageApi.js" as ChanApi

Item {
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
                z: -1
            }
            PropertyChanges {
                target: frontPage
                opacity: 0.0
                z: 1
            }
        },
        State
        {
            name: "frontPage"
            PropertyChanges {
                target: mainThread
                opacity: 0.0
                z: 1
            }
            PropertyChanges {
                target: frontPage
                opacity: 1.0
                z: -1
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

    function loadingDone()
    {

    }

    function switchState()
    {
        if(state == "frontPage")
            state = "thread"
        else
            state = "frontPage"
    }
}

