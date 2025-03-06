#include <stdio.h>

#include <string.h>
#include "padawan.h"  // Include the functions from your code
#include <winsock2.h>
#include <ws2tcpip.h>

#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <set>

#define SERVER_IP "127.0.0.1"  // Localhost
#define SERVER_PORT 8080
#define BACKLOG 5  // Max pending connections
#define BUF_SIZE 1024
#define BUF_SIZE_W_PADDING 1024+8

using namespace std;

bool debug = false;
set<SOCKET> clients; 
mutex clients_mutex; 

typedef struct {
    SOCKET sock;
    char* message;
} message_packet;

class MessageQueue {
public:
    queue<message_packet> message_queue;
    mutex message_mutex;
    condition_variable message_cv;


    void enqueue(message_packet& message){
        if (debug) printf("enqueue message!\n");
        unique_lock<mutex> lock(message_mutex);
        message_queue.push(message);
        lock.unlock();
        message_cv.notify_one();
    };
    
    message_packet dequeue(){
        unique_lock<mutex> lock(message_mutex);
        message_cv.wait(lock,[this]{return !message_queue.empty();});
        message_packet msg = message_queue.front();
        message_queue.pop();
        if (debug) printf("dequeued message\n");
        return msg;
    };
};

void handle_client(SOCKET client_socket, MessageQueue *mq){
    if (debug) printf("client thread created!\n");
    char recvBuffer[BUF_SIZE_W_PADDING];
    int recv_size;
    if (debug) printf("going to lock the set for client input!\n");
    unique_lock<mutex> lock(clients_mutex); 
    if (debug) printf("going to insert client socket into set!\n");
    clients.insert(client_socket);
    lock.unlock();
    if (debug) printf("client socket placed into set!\n");
    //format message
    message_packet mp;
    mp.sock=client_socket;
    char *c;
    while (true){
        if (debug) printf("trying to receive data from cient!\n");
        int recv_size = ReceiveData(client_socket, recvBuffer, sizeof(recvBuffer) - 1);
        if (recv_size > 0) {
            recvBuffer[recv_size] = '\0';  // Null-terminate the string
            
            printf("Received from client: %s\n", recvBuffer);
        }
        if (recv_size == 0){
            unique_lock<mutex> lock(clients_mutex); 
            clients.erase(client_socket); 
            lock.unlock();

        } else if (recv_size == SOCKET_ERROR){
            // remove client from set if client is not connected anymore
            unique_lock<mutex> lock(clients_mutex); 
            clients.erase(client_socket); 
            lock.unlock();
        } else{
            // check if it is in the correct format:
            if (!validateMsg(recvBuffer)){
                continue;
            }
            c = new char[BUF_SIZE_W_PADDING];
            // copy data from buffer to here before putting into queue
            strncpy(c,recvBuffer,BUF_SIZE_W_PADDING);
            mp.message = c;
            mq->enqueue(mp); 
        }

    }

}

void handle_messages(MessageQueue* mq){
    if (debug) printf("handling messages thread created!\n");
    message_packet data;
    set<SOCKET>::iterator it;
    while (true){
        // consume message from the queue
        data = mq->dequeue();
        if (debug) printf("This is what is received in data! %s\n",data.message);
        unique_lock<mutex> lock(clients_mutex);
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


int main() {

    MessageQueue *mq = new MessageQueue();
    SOCKET serverSocket, clientSocket;
    char recvBuffer[BUF_SIZE];
    const char* sendMessage = "Hello, Client!";

    // Initialize Winsock
    if (!InitWinsock()) {
        return 1;
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        CleanupWinsock();
        return 1;
    }

    // Bind the socket to the address and port //TODO:check this
    if (!BindSocket(&serverSocket, SERVER_IP, SERVER_PORT)) {
        CleanupWinsock();
        return 1;
    }

    // Listen for incoming connections
    if (!ListenForConnections(&serverSocket, BACKLOG)) {
        CleanupWinsock();
        return 1;
    }

    printf("Server is listening on %s:%d...\n", SERVER_IP, SERVER_PORT);

    thread t0(handle_messages,mq);
    while (true){
        // Accept a connection from a client
        clientSocket = AcceptConnection(&serverSocket);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }
        thread t1(handle_client,clientSocket,mq);
        t1.detach();
    }
    t0.join();

    // Close the client socket
    CloseSocket(clientSocket);

    // Cleanup Winsock
    CleanupWinsock();

    delete mq;

    return 0;
}
