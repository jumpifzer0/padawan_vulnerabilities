#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <thread>

#include "ChatClient.h"

ChatClient::ChatClient() : base_client() {
        bufsize = 1024;
        bufsize_w_padding = 1024 + 8;
}


void ChatClient::pollingSend(){
    char inputBuffer[bufsize];
    char formatMsgBuffer[bufsize_w_padding];
    while(true){

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != nullptr) {
            // Remove the trailing newline character (if any)
            inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
        }

        // Send data to the server
        formatMsg(inputBuffer,formatMsgBuffer);
        if (SendData(clientSocket, formatMsgBuffer, strlen(formatMsgBuffer)) == 0) {
            printf("Failed to send data\n");
        }
    }
}


void ChatClient::pollingRecv(){
    char recvBuffer[bufsize_w_padding];
    char parsedBuffer[bufsize];
    while (true){
        // Receive data from the server
        int bytesReceived = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer) - 1);
        if (bytesReceived > 0) {

            recvBuffer[bytesReceived] = '\0';  // Null-terminate the string
            parseMsg(recvBuffer,parsedBuffer);
            printf("Received from server: %s\n", parsedBuffer);

        } else if (bytesReceived < 0) {
            printf("received failed!\n Exitting......");
            exit(0);
        } else {
            printf("received 0 bytes!\n");
        }
    }   
}


// consider using condition_variable to trigger the thread to cout, rather than the current print when recv
void ChatClient::pollingDisplay(){
    
}