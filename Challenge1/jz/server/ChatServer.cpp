#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <set>


#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "ChatServer.h"


// constructor
ChatServer::ChatServer(MessageQueue *mq) : base_listening_server() {
    this->mq = mq;
    buf_size = 1024;
    buf_size_w_padding = 1024 + 8;
}

// destructor
ChatServer::~ChatServer(){

}


void ChatServer::handleClient(SOCKET clientSocket, MessageQueue *mq){

    char recvBuffer[buf_size_w_padding];
    int recv_size;

    unique_lock<mutex> lock(clientsMutex); 
    clients.insert(clientSocket);
    lock.unlock();

    //format message
    messagePacket mp;
    mp.sock=clientSocket;
    char *c;
    while (true){

        int recv_size = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer)-1); //TODO:
        if (recv_size > 0) {
            recvBuffer[recv_size] = '\0';  // Null-terminate the string
            
            printCharArray(recvBuffer); // Currently this is the vulnerable function
        }
        if (recv_size == 0){
            unique_lock<mutex> lock(clientsMutex); 
            clients.erase(clientSocket); 
            lock.unlock();
            exit(0);

        } else if (recv_size == SOCKET_ERROR){
            unique_lock<mutex> lock(clientsMutex); 
            clients.erase(clientSocket); 
            lock.unlock();
        } else{
            if (!validateMsgHeader(recvBuffer)){
                continue;
            }
            c = new char[buf_size_w_padding];
            // copy data from buffer to here before putting into queue
            strncpy(c,recvBuffer,buf_size_w_padding);
            mp.message = c;
            mq->enqueue(mp); 
        }

    }
}


// it continually will poll and broadcast messages due to the while(True)
// jz : consider to do a if-else check to check if messageQueue is empty, else do the things, current might be very resource heavy
void ChatServer::broadcastMessage(MessageQueue *mq){
    messagePacket data;
    set<SOCKET>::iterator it;
    while (true){
        // consume message from the queue
        data = mq->dequeue();

        unique_lock<mutex> lock(clientsMutex);
        for (it= clients.begin(); it != clients.end(); ++it) {
            if (*it != data.sock){
                if (SendData(*it, data.message, strlen(data.message)) == 0) {
                    printf("Failed to send data to client\n");
                    clients.erase(*it);
                }
            }
        }
        lock.unlock();
        delete data.message;
    }
}


// this function will keep running in the main thread to accept new incoming connections.
// upon accepting a connection, it will create a thread of handleClient
void ChatServer::pollingClientConnections(){
    
    // while loop to allow the accept to be running in the background
    while (true){
        
        SOCKET clientSocket = AcceptConnection(&serverSocket);
        //printf("connection accepted!\n");

        if (clientSocket == INVALID_SOCKET) {
            continue;
        }
        else{
            thread t0(&ChatServer::handleClient,this,clientSocket,ref(mq));
            t0.detach();     
        }

        
    }

}