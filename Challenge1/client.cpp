#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#include "padawan.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUF_SIZE 1024
using namespace std;

bool debug = false;
void sendData(SOCKET clientSocket){
    char sendBuffer[BUF_SIZE];
    while(true){

        if (fgets(sendBuffer, sizeof(sendBuffer), stdin) != nullptr) {
            // Remove the trailing newline character (if any)
            sendBuffer[strcspn(sendBuffer, "\n")] = '\0';
        }

        // Send data to the server
        if (SendData(clientSocket, sendBuffer, strlen(sendBuffer)) == 0) {
            printf("Failed to send data\n");
            continue;
        }
    }

}

void recvData(SOCKET clientSocket){
    char recvBuffer[BUF_SIZE];
    
    while (true){
        // Receive data from the server
        int bytesReceived = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer) - 1);
        if (debug) printf("client received message!\n");
        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0';  // Null-terminate the string
            printf("Received from server: %s\n", recvBuffer);
        } else if (bytesReceived < 0) {
            printf("received failed!\n Exitting......");
            exit(0);
        } else {
            if (debug) printf("received 0 bytes!\n");
        }
    }
}


int main(){
    SOCKET clientSocket;
    char sendMessage[] = "Hello, Server!";
    char recvBuffer[BUF_SIZE];
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

    thread t1(recvData,clientSocket);
    sendData(clientSocket);
    t1.join();
    
    // Close the socket
    CloseSocket(clientSocket);

    // Cleanup Winsock
    CleanupWinsock();

    return 0;

}