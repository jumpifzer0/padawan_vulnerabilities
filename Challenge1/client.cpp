#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#include "padawan.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8079
#define BUF_SIZE 512
#define BUF_SIZE_W_PADDING 1024+8
using namespace std;

bool debug = false;



class Client{

    SOCKET clientSocket;
    
    public:
        Client(){
            
        }
        void initialiseSocket(){
            // initialise socket
            if (!InitWinsock()) {
                printf("cannot initialise socket\n");
                return ;
            }   
            
        } ;

        void createSocket(){
            clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        }

        void connectToServer(){
            if (!ConnectToServer(&clientSocket, SERVER_IP, SERVER_PORT)) {
                printf("cannot connect to server!\n");
                CleanupWinsock();
                exit(0);
            }   
        };

        void cleanupSocket(){
            // Close the socket
            CloseSocket(clientSocket);

            // Cleanup Winsock
            CleanupWinsock();
        };

    void sendData(){
        char inputBuffer[BUF_SIZE];
        char formatMsgBuffer[BUF_SIZE_W_PADDING];
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
    
    };
    
    void recvData(){
        char recvBuffer[BUF_SIZE_W_PADDING];
        char parsedBuffer[BUF_SIZE];
        while (true){
            // Receive data from the server
            int bytesReceived = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer) - 1);
            if (debug) printf("client received message! %d\n",bytesReceived);
            if (bytesReceived > 0) {
    
                recvBuffer[bytesReceived] = '\0';  // Null-terminate the string
                if (debug) printf("Message received in recvBuffer! %s\n",recvBuffer);
                parseMsg(recvBuffer,parsedBuffer);
                
                printf("Received from server: %s\n", parsedBuffer);
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
    
    Client* client = new Client();
    client->initialiseSocket();
    client->createSocket();
    // connect to server
    client->connectToServer();

    // Another thread to handle incoming data.
    thread t1([client]{
        client->recvData();
    });

    // This continues as a while loop in the main thread
    client->sendData();
    
    t1.join();
    client->cleanupSocket();
    delete client;
    return 0;

}