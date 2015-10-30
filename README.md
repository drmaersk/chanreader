# chanreader

TODO: Structure

Main view contains 
ContentPanel.qml and ThreadStackPanel.qml
ContentPanel.qml contains
Either
Frontpage.qml
or
Thread.qml

The FrontPage.qml contains multiple threads.
Here you should be able to select a thread to show in it's entirety
You should also be able to start a new thread.


Thread.qml contains multiple Post.qml
Thread has two states: 
Preview - to be used when showing multiple threads on the frontpage

Full - for showing the thread in it's entirety
Here you should be able to browse the posts click on images and post (Also reply to other posts).

Post should contain (at least): Name, Number, Image and comment.

Post should be able to click url's and load them
url is both to other posts and external


ThreadStackPanel shows history of recently opened Threads as a stack.
Should be able to switch between threads here and also show 404 when a thread is dead.

UI the Post should be able to expand and shrink to content
The post should not expand more than current width of window
The Image needs to be handled in some way to support webm and gif
Image needs to also depend on the max width of window as it is inside the post.

Caching threads:
CRUD threads and structure:
Only thing that needs saved as files are the images:
Filestructure:
Board
|
|-Date
  |
  |-Thread
    |
    |-images
  
DataBase Structure:
Board - Thread
Thread PK(?) - Date
Post FK(Thread) -> PostInfo, Path to Image.
One Db per board?


FileDownloader should take a list of files (per thread)and download them, start thread for each http call
input should be the list of files (http urls), and the directory in which to put them.

User should be able to input where the root of the filestructure should be.
User should be able to import old filestructure to new installation.
User should be able to switch between different caching options.
1. Automatically save everything.
2. Only pre-fetch/cache images but delete them when closing app.
3. Manually save images only (No automatic saving).




