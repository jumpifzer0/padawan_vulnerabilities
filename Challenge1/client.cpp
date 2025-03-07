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



class Client{
    public:
        void initialiseSocket(){
            // initialise socket
            if (!InitWinsock()) {
                printf("cannot initialise socket\n");
                return ;
            }   
        } ;

        void connectToServer(SOCKET clientSocket){
            if (!ConnectToServer(&clientSocket, SERVER_IP, SERVER_PORT)) {
                printf("cannot connect to server!\n");
                CleanupWinsock();
                return;
            }   
        };

        void cleanupSocket(SOCKET clientSocket){
            // Close the socket
            CloseSocket(clientSocket);

            // Cleanup Winsock
            CleanupWinsock();
        };

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
    
    };
    
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
    };
};



int main(){
    SOCKET clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    Client* client = new Client();
    client->initialiseSocket();
    // connect to server
    client->connectToServer(clientSocket);
    thread t1([client,clientSocket]{
        client->recvData(clientSocket);
    });
    client->sendData(clientSocket);
    t1.join();
    client->cleanupSocket(clientSocket);
    delete client;
    return 0;

}