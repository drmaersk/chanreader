.pragma library
var _threads

function request(func) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
            print('HEADERS_RECEIVED');
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            print("DONE")
            var object = JSON.parse(xhr.responseText.toString());
//            var threadData = []
            _threads = object.threads
            func();
//            object.threads.forEach(function(thread) {
//                thread.posts.forEach(function(post) {
//                    console.log(JSON.stringify(post.no)+'\n');

//                })
//            })



            //console.log(JSON.stringify(obj.posts)+'\n'); });
            //print(JSON.stringify(object.threads));
        }
    }
    xhr.open("GET", "http://a.4cdn.org/tv/1.json");
    xhr.send();

//    var threadData = [ {"postData": [{"no" : "123","author":"anonymous","comment":"hej"}] } ]
//    return threadData
//        [
//            {postData:[
//                    {no: "132443211243", author: "Tripfag", comment: "The oeaueuoaeuouoea is the perfect mov1111111111aeuoeuoaoeueuaoeoaueuoeoaueuaeuueeuaaeuoeauoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooaeuoaueuaeaouuauaueoeuaeueauaeoueueuaaeueuaaeueauaeuoeuaaeoueaueueouaeuaouaeoeauooeua1111111111111111111111111111t."},
//                    {no: "431214343243", author: "Anonymous", comment: "<a href=\"#p61696160\" class=\"quotelink\">&gt;&gt;61696160<\/a><br><span class=\"quote\">&gt;Italian here, their use of Italian was completely broken.<\/span><br><br>That&#039;s because they&#039;re from Sicily. It&#039;s the Italian equivalent of ebonics."}
//                ]},
//            {postData:[
//                    {no: "234113423421", author: "Anonymous", comment: "aueouuaoeueeuaoue  ueuaeoauoeuae  u auueaoeuao oeuaoeuuoeeuaaeouuuaueuoa"},
//                    {no: "132443211243", author: "Tripfag", comment: "The Godfather is the perfect movie. The second is bretty good, masterpiece in its own right, but not perfect."},
//                    {no: "431214343243", author: "Anonymous", comment: "<a href=\"#p61696160\" class=\"quotelink\">&gt;&gt;61696160<\/a><br><span class=\"quote\">&gt;Italian here, their use of Italian was completely broken.<\/span><br><br>That&#039;s because they&#039;re from Sicily. It&#039;s the Italian equivalent of ebonics."}
//                ]}
//        ]
}

function getThreads()
{
    return _threads
}
