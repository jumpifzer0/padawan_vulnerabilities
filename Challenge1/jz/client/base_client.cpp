#include "base_client.h"
#include "../padawan_dll/padawan.h"


base_client::base_client(){
    initializeSocket();
    createSocket();
}


base_client::~base_client(){
    cleanupSocket();
}


void base_client::connectToServer(char * server_ip, unsigned short server_port){
    if (!ConnectToServer(&clientSocket, server_ip, server_port)) {
        printf("cannot connect to server!\n");
        CleanupWinsock();
        exit(0);
    }   
}


void base_client::initializeSocket(){
    // initialise socket
    if (!InitWinsock()) {
        printf("cannot initialise socket\n");
        return ;
    }   
}


void base_client::createSocket(){
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}


void base_client::cleanupSocket(){
    CloseSocket(clientSocket);
    CleanupWinsock();
}
