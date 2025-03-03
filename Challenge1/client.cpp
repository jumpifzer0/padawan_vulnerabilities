#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include "padawan.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080


int main(){
    SOCKET clientSocket;
    char sendMessage[] = "Hello, Server!";
    char recvBuffer[1024];
    // initialise socket
    if (!InitWinsock()) {
        return 1;
    }    

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // connect to server
    if (!ConnectToServer(&clientSocket, SERVER_IP, SERVER_PORT)) {
        CleanupWinsock();
        return 1;
    }    
    printf("reached here\n");
    //TODO:create thread

    // send and receive --- once received print to console

    // Send data to the server
    if (SendData(clientSocket, sendMessage, strlen(sendMessage)) == 0) {
        printf("Failed to send data\n");
        CloseSocket(clientSocket);
        CleanupWinsock();
        return 1;
    }

    // Receive data from the server
    int bytesReceived = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer) - 1);
    if (bytesReceived > 0) {
        recvBuffer[bytesReceived] = '\0';  // Null-terminate the string
        printf("Received from server: %s\n", recvBuffer);
    }

    // Close the socket
    CloseSocket(clientSocket);

    // Cleanup Winsock
    CleanupWinsock();

    return 0;

}