/*
 * Nikolay Radaev
 * Simple chat server-client program in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 2222
#define BUFFERSIZE 99999


void handleSendRecv(int x, int clientSocket, int serverSocket) {
	char sendBuffer[BUFFERSIZE];
	char receiveBuffer[BUFFERSIZE];
	int bytesReceived;
	
	if (x == 0) {
		
		fgets(sendBuffer, BUFFERSIZE, stdin);
		
		while (strlen(sendBuffer) > 140) {
			printf("Error in input. Too many characters! Try type less than 140 characters again!\n");
			printf("You: ");
			fgets(sendBuffer, BUFFERSIZE, stdin);
		}
		
		if (strcmp(sendBuffer, "quit\n") == 0) {
			close(clientSocket);
			if (serverSocket != -1) {
				close(serverSocket);
			}
			exit(1);
			
		} else send(clientSocket, sendBuffer, strlen(sendBuffer), 0);
		
	} else {
		bytesReceived = recv(clientSocket, receiveBuffer, BUFFERSIZE, 0);
		receiveBuffer[bytesReceived] = '\0';
		printf("%s" , receiveBuffer);
		fflush(stdout);
	}
}

int acceptConnect(int serverSocket, struct sockaddr_in *clientAddr) {
	
	socklen_t addrLen;
	int clientfd;
	
	addrLen = sizeof(struct sockaddr_in);
	if((clientfd = accept(serverSocket, (struct sockaddr *)clientAddr, &addrLen)) == -1) {
		printf("Acccept error\n");
		exit(1);
	} else {
		printf("Found a friend! You receive first.\n");
	}
	return clientfd;
}

int main(int argc, char* argv[]) {
	int port; // for client code
	char servIP [255]; // for client code
	struct sockaddr_in servAddr;					/* Server address */
	struct sockaddr_in clientAddr;  				/* Client address */
	int clientSocket;

	
	if (argc == 1) { // run my server here NOW!
	
		int serverSocket;
			
		if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			printf("Error opening socket\n");
			exit(1);
		}

		memset(&servAddr, 0, sizeof(servAddr));			//zero out structure
		servAddr.sin_family = AF_INET;					/* Internet addr family */
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	/* Any incoming interface ServAddr. */
		servAddr.sin_port = htons(PORT);				/* Local port */
		
		int flag = 1;
		
		setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)); // trick to reuse socket and so we can close server socket
		
		if (bind(serverSocket, (struct sockaddr*) &servAddr, sizeof(struct sockaddr_in)) == -1) {
			printf("Error binding socket\n");
			exit(1);
		}
		
		if (listen(serverSocket, 10) == -1) {
			printf("Error listenning\n");
			exit(1);
		}
		
		char *ip;
		
		char hostname [255];
		gethostname(hostname, 255);
		
		struct hostent* h;
		h = gethostbyname(hostname);		
		
		ip = inet_ntoa(*(struct in_addr *)h->h_addr_list[0]);

		printf("Waiting for a connection on \n");
		printf("%s port %u\n", ip, PORT);
		
		//Now accept connection from a client
		
		clientSocket = acceptConnect(serverSocket, &clientAddr);
	
		while(clientSocket) {
			printf("Friend: ");
			handleSendRecv(1, clientSocket, serverSocket);
			printf("You: ");
			handleSendRecv(0, clientSocket, serverSocket);
		}
		
		close(clientSocket);
		close(serverSocket);
	}
	
	// run my client!
			
	if (argc == 5 && (strcmp(argv[1], "-s") == 0) && (strcmp(argv[3], "-p") == 0)) {
			port = atoi(argv[4]);
			strcpy(servIP, argv[2]);
		}
	else if (argc == 5 && (strcmp(argv[1], "-p") == 0) && (strcmp(argv[3], "-s") == 0)) {
			port = atoi(argv[2]);
			strcpy(servIP, argv[4]);
		}
	
	else if (argc == 2 && (strcmp(argv[1], "-h") == 0)) {
		printf("Help message. Exiting.\n");
		exit(1);
	}
	
	else {
			printf(argv[0]);
			printf("\n");
			printf(argv[1]);
			printf("\n");
			printf(argv[2]);
			printf("\n");
			printf(argv[3]);
			printf("\n");
			printf(argv[4]);
			printf("\n");
			printf("Check your arguments\n");
			exit(1);
		}
		
		// request connection
		
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Socket creating issue.\n");
		exit(1);
	}
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(port);
		servAddr.sin_addr.s_addr = inet_addr(servIP);
		memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));
	
	printf("Connecting to server...\n");
	
	if (connect(clientSocket, (struct sockaddr *) &servAddr, sizeof(struct sockaddr)) == -1) {
		printf("Connect issue.\n");
		exit(1);
	}
	
	printf("Connected!\n");
	printf("Connected to a friend! You send first.\n");
		
	while(clientSocket){
		printf("You: ");
		handleSendRecv(0, clientSocket, -1);
		printf("Friend: ");
		handleSendRecv(1, clientSocket, -1);
	}
		
	close(clientSocket);
	
	return 0;
}








	