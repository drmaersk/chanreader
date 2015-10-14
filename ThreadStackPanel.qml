import QtQuick 2.0
import QtQuick.Layouts 1.2
Item{
    id: stackPanel
    width: parent.width * 0.1
    property date currentDate: new Date()
    property variant tempThreadData: [{name: currentDate.getUTCMilliseconds().toLocaleString()},
        {name: currentDate.getUTCMilliseconds().toLocaleString()},
        {name: currentDate.getUTCMilliseconds().toLocaleString()},
        {name: currentDate.getUTCMilliseconds().toLocaleString()},
        {name: currentDate.getUTCMilliseconds().toLocaleString()},
        {name: currentDate.getUTCMilliseconds().toLocaleString()}]

    state: "closed"
    states: [
        State
        {
            name: "open"
            PropertyChanges {
                target: stackPanel
                width: parent.width * 0.1
            }
        },
        State
        {
            name: "closed"
            PropertyChanges {
                target: stackPanel
                width: parent.width * 0.0
            }
        }
    ]

    MouseArea {
        id: spacer
        width: 32
        height: 32
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.left
        Image {
            source: "img/forward32.png"
            anchors.fill: parent
        }
        onClicked: if (parent.state == "open")
                       parent.state = "closed"
                   else
                       parent.state = "open"
    }

    Column {
        id: threadNumberContainer
        Repeater {
            model: tempThreadData
            Text {
                width: stackPanel.width;
                text: modelData.name
            }
        }
    }

}

