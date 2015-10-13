import QtQuick 2.0

Item {
    property variant threadData: [
        {postData:[
                //            {no: "234113423421", author: "Anonymous", comment: "The parts where the characters speak in Italian are insufferable. That&#039;s not good filmmaking."},
                {no: "132443211243", author: "Tripfag", comment: "The oeaueuoaeuouoea is the perfect mov1111111111aeuoeuoaoeueuaoeoaueuoeoaueuaeuueeuaaeuoeauoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooaeuoaueuaeaouuauaueoeuaeueauaeoueueuaaeueuaaeueauaeuoeuaaeoueaueueouaeuaouaeoeauooeua1111111111111111111111111111t."},
                {no: "431214343243", author: "Anonymous", comment: "<a href=\"#p61696160\" class=\"quotelink\">&gt;&gt;61696160<\/a><br><span class=\"quote\">&gt;Italian here, their use of Italian was completely broken.<\/span><br><br>That&#039;s because they&#039;re from Sicily. It&#039;s the Italian equivalent of ebonics."}
            ]},
        {postData:[
                {no: "234113423421", author: "Anonymous", comment: "aueouuaoeueeuaoue  ueuaeoauoeuae  u auueaoeuao oeuaoeuuoeeuaaeouuuaueuoa"},
                {no: "132443211243", author: "Tripfag", comment: "The Godfather is the perfect movie. The second is bretty good, masterpiece in its own right, but not perfect."},
                {no: "431214343243", author: "Anonymous", comment: "<a href=\"#p61696160\" class=\"quotelink\">&gt;&gt;61696160<\/a><br><span class=\"quote\">&gt;Italian here, their use of Italian was completely broken.<\/span><br><br>That&#039;s because they&#039;re from Sicily. It&#039;s the Italian equivalent of ebonics."}
            ]}
    ]

    Column {
        id: threadContainer
        spacing: 2

        Repeater {
            id: threadContainerRepeater
            model: threadData
            delegate: Thread {
                postData: modelData.postData
            }
        }
    }
}

