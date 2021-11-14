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
	int    networkSocket;
	int    closeServer_status;
	char   serverResponse[256];
	char   clientMessage[256];
	struct sockaddr_in serverAddress;
	static char userInput[20];

	// Create a Socket
	networkSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an Address for the Socket
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Connect to Server
	connect(networkSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

	while (1) {

		// Prompt the user for a message to send to the server
		puts("");
		fputs(": ", stdout);
		fgets(userInput, sizeof(userInput), stdin);

		// Strip off the newline character
		userInput[strcspn(userInput, "\n")] = 0;

		strcpy(clientMessage, userInput);
		send(networkSocket, clientMessage, sizeof(clientMessage), 0);

		// Receive Data from the Server
		recv(networkSocket, &serverResponse, sizeof(serverResponse), 0);

		// Display whatever message the server has sent
		printf("Server message: %s\n", serverResponse);

		// If we type "exit", the server will shut itself down,
		// therefore we will close down the client side as well.
		closeServer_status = strncmp("exit", clientMessage, 4);
		if (closeServer_status == 0) {
			break;
		}
	}

	close(networkSocket);

	return 0;
}
