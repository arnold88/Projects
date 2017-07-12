Arnold Lee
CS 441 Program #1

The New Age Event Reservation System

Read Me file

************************************

How to compile:

1.) run these commands in the UNIX command prompt, one line at a time:

javac proj1server.java
javac proj1client.java
javac proj1manager.java

2.)If no error message appears, you have succesfully complie the file. Check the directory to make sure 
these 3 files exist:

proj1server.class
proj1client.class
proj1manager.class

************************************

How to run:

3.) To run this program properly, you will need to start the server program FIRST. Type the following:

java proj1server

That should bring up the server prompt. You do not need to take any other action in this session.

4.) Open or "fork" another UNIX command prompt. Type either one to start the appropriate session:

java proj1client (for client prompt)
java proj1manager (for manager prompt)

You can start any one of them in either order. You can start multiple copies of them.

*************************************

Specifications and Instructions:

The server uses port 31337 for the manager program and port 23888 for the client program.

As this program still in beta the database in only stored in memory for that session. If you restart the server
everything will be lost.

The server can hold at most 100 records at one time.

The following commands are allowed on the client program:
view (view event description)
reserve (reserve an event)
delete (Delete a reservation)
exit (Exit the client)

The following commands are allowed on the server program:
add (add an event)
remove (Remove and event)
detail (display details of an event including # of reservations as well as names)
everything that the client program does

In addition, the manager client will receive regular on-screen updates about new reservations.
