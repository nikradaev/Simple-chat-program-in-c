# Simple-chat-program-in-c

Simple chat program. by Nikolay Radaev

INSTRUCTIONS:

1. Chose any CS dept machine with given IP
2. Have Makefile in the same folder as chat.c
3. To compile, type 'make' in the command prompt, and enter

denver:~/chatprogram$ make
gcc -Wall chat.c -o chat

4. To run as server, type './chat' and hit enter. this will start in the server mode:

denver:~/chatprogram$ ./chat
Waiting for a connection on
129.82.44.141 port 11111

5. Have the server running. Copy those numbers, you will need them.
6. To run as client, open a new session. Go to the folder. Type './chat -s XXX.XX.XX.XXX -p XXXXX', where -s, -p are the flags for server and port, and XXs - are numbers from server socket info, see #4. After -s flag next is SERVER IP, and after -p flag there is PORT NUMBER. './chat -p XXXXX -s XXX.XX.XX.XXX' will also work, where port goes first, and server ip - the following.

denver:~/chatprogram$ ./chat -s 129.82.44.141 -p 11111
Connecting to server...
Connected!
Connected to a friend! You send first.
You:

7. Client session should type first, server will receive. Then it is the server's turn, and so on.

Server:
denver:~/chatprogram$ ./chat
Waiting for a connection on
129.82.44.141 port 11111
Found a friend! You receive first.
Friend: Hello!
You: How are you?

Client:
denver:~/chatprogram$ ./chat -s 129.82.44.141 -p 11111
Connecting to server...
Connected!
Connected to a friend! You send first.
You: Hello!
Friend: How are you?
You:

8. If you type over 140 characters. It will give a warning and ask for a new line.

You: dkjdjkdkj;kdjl;kfj;lkjfd;kjdfg;kjdfg;kjdfgokjdgfkl;jgdf;kljgdf;kdgjf;kdfgj;klfgdj;lkgfjd;lkfgdj;lkfgdj;klfjgd;lkfjgd;lkfjg;lkfjgd;fljk;f;lfj;kljfg;lkjgfd;lkjgfd;lkjgfd;lkjgfd;lkjgfd;lkjgdf;lfgkd;lkfjgd;lfjgkd
Error in input. Too many characters! Try type less than 140 characters again!
You:


9. Type 'quit' to properly quit the program and close the socket(s).

You: quit
denver:~/chatprogram$

This might take couple of prompts on the other session for quitting it too.

Friend: You: ssssssssssss
Friend: You: ssssssssssssssss
denver:~/chatprogram$

9. Ctrl + C to halt the sessions whether on client or a server.

You: ^C
denver:~/chatprogram$

This might take couple of prompts on the other session for quitting it too.

Friend: You: ssssssssssss
Friend: You: ssssssssssssssss
denver:~/chatprogram$

10. To clean, type 'make clean' and hit enter

denver:~/chatprogram$ make clean

rm chat

denver:~/chatprogram$


11. If, for some reason the binding soket error occurs, feel free to change a PORT NUMBER in chat.c file. Recompile and Run. However I tried my best so server will be closing its socket properly.
