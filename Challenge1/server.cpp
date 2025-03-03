#include <stdio.h>

#include <string.h>
#include "padawan.h"  // Include the functions from your code
#include <winsock2.h>
#include <ws2tcpip.h>

#define SERVER_IP "127.0.0.1"  // Localhost
#define SERVER_PORT 8080
#define BACKLOG 5  // Max pending connections

int main() {
    SOCKET serverSocket, clientSocket;
    char recvBuffer[1024];
    const char* sendMessage = "Hello, Client!";

    // Initialize Winsock
    if (!InitWinsock()) {
        return 1;
    }

    // Create a socket
    // serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        CleanupWinsock();
        return 1;
    }

    // Bind the socket to the address and port //TODO:check this
    if (!BindSocket(&serverSocket, SERVER_IP, SERVER_PORT)) {
        CleanupWinsock();
        return 1;
    }

    // Listen for incoming connections
    if (!ListenForConnections(&serverSocket, BACKLOG)) {
        CleanupWinsock();
        return 1;
    }

    printf("Server is listening on %s:%d...\n", SERVER_IP, SERVER_PORT);

    // Accept a connection from a client
    clientSocket = AcceptConnection(&serverSocket);
    if (clientSocket == INVALID_SOCKET) {
        CleanupWinsock();
        return 1;
    }

    printf("Client connected\n");

    // Receive data from the client
    int bytesReceived = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer) - 1);
    if (bytesReceived > 0) {
        recvBuffer[bytesReceived] = '\0';  // Null-terminate the string
        printf("Received from client: %s\n", recvBuffer);
    }

    // Send data to the client
    if (SendData(clientSocket, sendMessage, strlen(sendMessage)) == 0) {
        printf("Failed to send data\n");
    }

    // Close the client socket
    CloseSocket(clientSocket);

    // Cleanup Winsock
    CleanupWinsock();

    return 0;
}
