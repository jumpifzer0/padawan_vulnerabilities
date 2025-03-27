#include "base_listening_server.h"
#include "../padawan_dll/padawan.h"

#include <string>
#include <winsock2.h>


// constructor
base_listening_server::base_listening_server(){
    server_ip = "127.0.0.1";
    server_port = 8079;
    backlog = 5;

    initialiseSocket();
}


// destructor
base_listening_server::~base_listening_server(){
    // Close the server socket
    CloseSocket(serverSocket);

    // Cleanup Winsock
    CleanupWinsock();
}


void base_listening_server::initialiseSocket(){
    // Initialize Winsock
    if (!InitWinsock()) {
        return;
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        CleanupWinsock();
        return;
    }

    // Bind the socket to the address and port
    if (!BindSocket(&serverSocket, server_ip.c_str(), server_port)) {
        CleanupWinsock();
        return;
    }

    // Listen for incoming connections
    if (!ListenForConnections(&serverSocket, backlog)) {
        CleanupWinsock();
        return;
    }

}