import QtQuick 2.0

Item {
    property variant postData: [
        {no: "234113423421", author: "Anonymous", comment: "The parts where the characters speak in Italian are insufferable. How does anyone consider that not obnoxious? That&#039;s not good filmmaking."},
        {no: "132443211243", author: "Tripfag", comment: "The Godfather is the perfect movie. The second is bretty good, masterpiece in its own right, but not perfect."},
        {no: "431214343243", author: "Anonymous", comment: "<a href=\"#p61696160\" class=\"quotelink\">&gt;&gt;61696160<\/a><br><span class=\"quote\">&gt;Italian here, their use of Italian was completely broken.<\/span><br><br>That&#039;s because they&#039;re from Sicily. It&#039;s the Italian equivalent of ebonics."}
    ]

    Column {
        id: postContainer
        anchors.fill: parent
        spacing: 3
        Repeater {
            model: postData
            delegate: Post {
                no: modelData.no
                author: modelData.author
                comment: modelData.comment
            }

        }
    }
}

