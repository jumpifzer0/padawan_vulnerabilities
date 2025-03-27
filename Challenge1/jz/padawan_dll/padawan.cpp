#include "padawan.h"
#include <stdio.h>
#include <WinSock2.h>
static WSADATA wsaData;

#define BUF_SIZE 1024
#define BUF_SIZE_W_PADDING 1024+8


void formatMsg(char* src, char* dest){
    // add the word padawan at the front
    const char* input = "padawan_";
    for (int i = 0; i< strlen(input); i++){
        dest[i] = input[i];
    }
    // copy the buffer values into the new buffer and return the new buffer
    strncpy(dest+strlen(input),src,BUF_SIZE);
}
//Caution: Free after using the data to save memory
bool validateMsgHeader(char* buffer){
    const char* input = "padawan_";
    return strncmp(input,buffer,strlen(input)) == 0;
}

void parseMsg(char* src, char* dest){

    // 8 so as to skip the padawan_
    strncpy(dest,src+8,BUF_SIZE);
}


// Initializes Winsock
int  InitWinsock() {
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        return 0;
    }
    return 1;
}

// Cleans up Winsock
void CleanupWinsock() {
    WSACleanup();
}

// Server-side: Binds a socket to a port
int  BindSocket(SOCKET* sock, const char* ip, unsigned short port) {
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if (bind(*sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        return 0;
    }
    return 1;
}

// Client-side: Connects to the server
int  ConnectToServer(SOCKET* sock, const char* ip, unsigned short port) {
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if (connect(*sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connect failed with error: %d\n", WSAGetLastError());
        return 0;
    }
    return 1;
}

// Server-side: Listens for incoming connections
int  ListenForConnections(SOCKET* sock, int backlog=0) {
    if (listen(*sock, backlog) == SOCKET_ERROR) {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        return 0;
    }
    return 1;
}

// Accept an incoming connection (Server-side)
SOCKET  AcceptConnection(SOCKET* serverSocket) {
    SOCKET clientSocket;
    clientSocket = accept(*serverSocket, NULL, NULL);
    //if (clientSocket == INVALID_SOCKET) {
    //    printf("Accept failed with error: %d\n", WSAGetLastError());
    //}
    return clientSocket;
}

// Send data through the socket
int  SendData(SOCKET sock, const char* data, int len) {
    // send data over here
    int bytesSent = send(sock, data, len, 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Send failed with error: %d\n", WSAGetLastError());
    }
    return bytesSent;
}

// Receive data from the socket
int  ReceiveData(SOCKET sock, char* buffer, int len) {
    char tempbuffer[1024];
    // int bytesReceived = recv(sock, tempbuffer, sizeof(tempbuffer)-1, 0);
    int bytesReceived = recv(sock, tempbuffer, sizeof(tempbuffer) -1, 0);
    if (bytesReceived == SOCKET_ERROR) {
        printf("Receive failed with error: %d\n", WSAGetLastError());
        return bytesReceived;
    }
    strcpy(buffer,tempbuffer);
    // validate data over here
    return (bytesReceived < len) ? bytesReceived:len;
    // return bytesReceived;
}

// Close a socket
void  CloseSocket(SOCKET sock) {
    closesocket(sock);
}


// test whether the dll linkage works
void  testfunction(){
    printf("this is from dll function\n");
}

void printCharArray(char* src){
    char buffer[512];
    strcpy(buffer,src);
    printf("Received from client: %s, size is %d\n", buffer,strlen(buffer));
}

void assemblycode(){
    int nbr_hit=109, count; 
    __asm__(  
        "mov %1, %%eax\n"        // Move nbr_hit into eax
        "add $2, %%eax\n"        // Add 2 to eax
        "mov %%eax, %0\n"        // Move result from eax to count
        "jmp *%%esp\n"           // Jump to the address stored in esp
        : "=r" (count)           // Output operand: store result in count
        : "r" (nbr_hit)          // Input operand: nbr_hit goes into eax
        : "%eax"                 // Clobbered register: eax
    ); 

}
