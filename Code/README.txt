Simple client-server programs. Only runs on a unix based machine (MacOS or Linux)
To compile and run server:

Link to short guide on how to install GCC on MacOS if you don't already have it:
https://discussions.apple.com/thread/8336714

----------

Using command line, start server first. Server will give two warnings that can be ignored:

To compile:
gcc server.c -o server

To run:
./server

----------

Start client second. Client will search for connections when launched. Client currently hits server once than disconnects.

To compile:
gcc client.c -o client

To run:
./client

Executable will be created and can also be run by double clicking the file.

----------

