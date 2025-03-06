#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#include "padawan.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUF_SIZE 1024
#define BUF_SIZE_W_PADDING 1024+8
using namespace std;

bool debug = false;
void sendData(SOCKET clientSocket){
    char inputBuffer[BUF_SIZE];
    char* formatMsgBuffer;
    while(true){

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != nullptr) {
            // Remove the trailing newline character (if any)
            inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
        }

        // Send data to the server
        formatMsgBuffer = formatMsg(inputBuffer);
        if (SendData(clientSocket, formatMsgBuffer, strlen(formatMsgBuffer)) == 0) {
            printf("Failed to send data\n");
        }
        formatMsgBuffer = NULL;
        delete formatMsgBuffer;
    }

}

void recvData(SOCKET clientSocket){
    char recvBuffer[BUF_SIZE_W_PADDING];
    char* parseMsgBuffer;
    while (true){
        // Receive data from the server
        int bytesReceived = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer) - 1);
        if (debug) printf("client received message! %d\n",bytesReceived);
        if (bytesReceived > 0) {

            recvBuffer[bytesReceived] = '\0';  // Null-terminate the string
            if (debug) printf("Message received in recvBuffer! %s\n",recvBuffer);
            parseMsgBuffer = parseMsg(recvBuffer);
            
            printf("Received from server: %s\n", parseMsgBuffer);
            delete parseMsgBuffer;
            parseMsgBuffer = NULL;
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

    thread t1(recvData,clientSocket);
    sendData(clientSocket);
    t1.join();
    
    // Close the socket
    CloseSocket(clientSocket);

    // Cleanup Winsock
    CleanupWinsock();

    return 0;

}