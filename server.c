#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 9003

int main(void) {

	// Variable Declaration Section
	int    serverSocket;
	int    clientSocket;
	int    closeServer_status;
	char   serverMessage[256];
	char   clientMessage[256];
	struct sockaddr_in serverAddress;

	// Server Message
	strcpy(serverMessage, "<message received>\n");

	// Create a Socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an Address for the Socket
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Bind Socket to IP ADDRESS and PORT
	bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	listen(serverSocket, 5);
	clientSocket = accept(serverSocket, NULL, NULL);

	while (1) {
		send(clientSocket, serverMessage, sizeof(serverMessage), 0);
		recv(clientSocket, &clientMessage, sizeof(clientMessage), 0);
		printf("Client message: %s\n", clientMessage);

        // If the client typed "exit", the server will shut itself down.
        closeServer_status = strncmp("exit", clientMessage, 4);
        if (closeServer_status == 0) {
            printf("\n");
            printf("OK, server is shutting down...\n");
            printf("\n");
            break;
        }
	}

	// This will be reached upon exit
	close(clientSocket);
	close(serverSocket);

	return 0;
}
