.pragma library
var _threads
var _singleThread

function requestPage(httpRequestDoneCallback) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            var object = JSON.parse(xhr.responseText.toString());
            _threads = object.threads
            httpRequestDoneCallback();
        }
    }
    xhr.open("GET", "http://a.4cdn.org/tv/1.json");
    xhr.send();
}


function requestThread(threadId, httpRequestDoneCallback ) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            print("DONE")
            var object = JSON.parse(xhr.responseText.toString());
            _singleThread = object.posts
            httpRequestDoneCallback();
        }
    }
    xhr.open("GET", "http://a.4cdn.org/tv/thread/"+threadId+".json");
    xhr.send();
}

function getThreads()
{
    return _threads
}

function getSingleThread()
{
    return _singleThread
}


